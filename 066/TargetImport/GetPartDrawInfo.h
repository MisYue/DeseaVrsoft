#pragma once
#include "GetVertex.h"
#include "GetWorldCoordinateOfNodeVisitor.h"
#include "targetInfo.h"
#include <osg/TriangleFunctor>
#include <osg/Drawable>
#include <osg/Geode>
#include <map>
#include <string>
#include <list>
#include <QTextCodec>

QString  GBK2Unicode(const char* str)
{
	QTextCodec* gbk = QTextCodec::codecForName("GBK");
	return gbk->toUnicode(str);
}

using TIMP::PartDrawInfo;

class PartAttributeFunctor : public osg::Drawable::AttributeFunctor
{
public:
	typedef osg::Drawable::AttributeType AttributeType;
	virtual void apply(AttributeType type, unsigned int size, osg::Vec3* front)
	{
		if(osg::Drawable::NORMALS)
			for(int i=0; i<size; ++i)
				_normals->push_back(front[i]);
	}
	virtual void apply(AttributeType type, unsigned int size, osg::Vec4* front)
	{
		if(type == osg::Drawable::COLORS)
			for(int i=0; i<size; ++i)
				_colors->push_back(front[i]);
	}
	static void getAttribute(osg::Vec3Array* normals, osg::Vec4Array* colors, osg::Drawable& drawable)
	{
		PartAttributeFunctor functor;
		functor._colors = colors;
		functor._normals = normals;
		drawable.accept(functor);
	}
	osg::Vec3Array* _normals;
	osg::Vec4Array* _colors;
};
class FindDrawInfo : public osg::NodeVisitor
{
public:
	FindDrawInfo(PartDrawInfo& drawInfo) : _drawInfo(drawInfo), osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN){}
	virtual void apply(osg::Geode& node)
	{
		//获取世界坐标
		osg::Matrixd mat = *GetWorldCoordinateOfNodeVisitor::getWorldCoords(&node);
		PartDrawInfo& drawInfo = _drawInfo;
		for(int i=0; i<node.getNumDrawables(); ++i)
		{
			osg::Drawable* drawable = node.getDrawable(i);
			if(!drawable) continue;
			GetVertex::getTriangles(drawInfo._vertexes, *drawable);
		}
		for(int i=0; i<drawInfo._vertexes->size(); ++i)
		{
			osg::Vec3& v = drawInfo._vertexes->at(i);
			v = v * mat;
		}
		for(int i=0; i<drawInfo._vertexes->size()/3; ++i)
		{
			osg::Vec3& v1 = drawInfo._vertexes->at(i*3);
			osg::Vec3& v2 = drawInfo._vertexes->at(i*3+1);
			osg::Vec3& v3 = drawInfo._vertexes->at(i*3+2);
			osg::Vec3 normal = (v2-v1)^(v3-v2);
			normal.normalize();
			drawInfo._normals->push_back(normal);
		}
	}
private:
	PartDrawInfo& _drawInfo;
};
class FindPartVisitor : public osg::NodeVisitor
{
public:
	FindPartVisitor(std::map<std::string, PartDrawInfo>& parts)
		: _parts(parts),
		  osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN){}
	virtual void apply(osg::Node& node)
	{
		std::string name = node.getName();
		std::string substr;
		if(name.size() > 3)
		{
			substr = name.substr(name.size()-2);
		}
		if(name.size() < 3 ||  (substr != "/p" && substr != "_p"))
		{
			traverse(node);
		}
		else
		{
			std::string name = node.getName();
			name = name.substr(0, name.size()-2);
			std::pair<std::map<std::string, PartDrawInfo>::iterator, bool> ret = _parts.insert(std::make_pair(name, PartDrawInfo()));
			if(ret.second)
			{
				PartDrawInfo& drawInfo = ret.first->second;
				drawInfo._name = name;
				FindDrawInfo findDrawInfo(drawInfo);
				node.accept(findDrawInfo);
			}
		}
	}
private:
	std::map<std::string, PartDrawInfo>& _parts;
};


class FindGeometryVisitor : public osg::NodeVisitor
{
public:
	FindGeometryVisitor(std::map<std::string, PartDrawInfo>& parts) 
		:	_parts(parts),
		osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
	{}
	virtual void apply(osg::Node& node)
	{
		traverse(node);
	}

	virtual void apply(osg::Geode& node)
	{
		std::string name = QString::fromUtf8(node.getName().c_str()).toLocal8Bit().data();
		unsigned pos = name.find_last_of(':');
		if(pos != std::string::npos)
		{
			//name = name.substr(pos+1);
		}
		std::pair<std::map<std::string, PartDrawInfo>::iterator, bool> ret = _parts.insert(std::make_pair(name, PartDrawInfo()));
		if(ret.second)
		{
			//获取世界坐标
			osg::Matrixd mat = *GetWorldCoordinateOfNodeVisitor::getWorldCoords(&node);
			PartDrawInfo& drawInfo = ret.first->second;
			drawInfo._name = ret.first->first;
			for(int i=0; i<node.getNumDrawables(); ++i)
			{
				osg::Drawable* drawable = node.getDrawable(i);
				if(!drawable) continue;
				//PartAttributeFunctor::getAttribute(drawInfo._normals, drawInfo._colors, *drawable);
				GetVertex::getTriangles(drawInfo._vertexes, *drawable);
			}
			for(int i=0; i<drawInfo._vertexes->size(); ++i)
			{
				osg::Vec3& v = drawInfo._vertexes->at(i);
				v = v * mat;
			}
			for(int i=0; i<drawInfo._vertexes->size()/3; ++i)
			{
				osg::Vec3& v1 = drawInfo._vertexes->at(i*3);
				osg::Vec3& v2 = drawInfo._vertexes->at(i*3+1);
				osg::Vec3& v3 = drawInfo._vertexes->at(i*3+2);
				osg::Vec3 normal = (v2-v1)^(v3-v2);
				normal.normalize();
				drawInfo._normals->push_back(normal);
			}
		}
	}
private:
	std::map<std::string, PartDrawInfo>& _parts;
};