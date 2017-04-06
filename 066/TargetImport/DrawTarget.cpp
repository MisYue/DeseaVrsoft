//***************************************
//	创建时间:	2015:11:6   17:36
//	文件名称: 	DrawTarget.cpp
//	文件作者:	岳群磊
//	
//	功能说明:	实现绘制目标类
//***************************************

#include "DrawTarget.h"
#include <osg/Geometry>
#include <osg/PolygonOffset>
#include <osg/BlendFunc>
#include <osgUtil/SmoothingVisitor>
DrawTarget::DrawTarget()
	: _geode(new osg::Geode)
{
	//开启透明
	osg::StateSet* stateSet = _geode->getOrCreateStateSet();
	stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
	osg::ref_ptr<osg::BlendFunc> bfn = new osg::BlendFunc;
	bfn->setFunction(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
	stateSet->setAttributeAndModes(bfn, osg::StateAttribute::ON);
	stateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::ON);
}
void DrawTarget::Reset()
{
	_geode->removeDrawables(0, _geode->getNumDrawables());
	_showCtrl.clear();
}

osg::Geode* DrawTarget::Draw(TargetDrawInfo* drawInfo)
{
	_partsDrawInfo = drawInfo;
	_geode->removeDrawables(0, _geode->getNumDrawables());
	_showCtrl.clear();
	_geode->getOrCreateStateSet()->setMode(GL_LINE_SMOOTH,osg::StateAttribute::ON);
	_geode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	osg::ref_ptr<osg::BlendFunc> bfn = new osg::BlendFunc;
	bfn->setFunction(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
	_geode->getOrCreateStateSet()->setAttributeAndModes(bfn, osg::StateAttribute::ON);
	for(TargetDrawInfo::iterator beg = _partsDrawInfo->begin(); beg != _partsDrawInfo->end(); ++beg)
	{
		PartDrawInfo& partDrawInfo = beg->second;
		osg::Vec4Array* colorsFace = new osg::Vec4Array;
		osg::Vec4Array* colorsLine = new osg::Vec4Array;
		PartGeometry partGeometry;
		_geode->addDrawable(partGeometry._face);
		_geode->addDrawable(partGeometry._line);
		_geode->addDrawable(partGeometry._box);
		for(int i=0; i<partDrawInfo._vertexes->size()/3; ++i)
		{
			osg::DrawArrays* face = new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, i*3, 3);
			osg::DrawArrays* line = new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, i*3, 3);
			partGeometry._line->addPrimitiveSet(line);
			partGeometry._face->addPrimitiveSet(face);
			colorsFace->push_back(partGeometry._faceColor);
			colorsLine->push_back(partGeometry._lineColor);
		}
		partGeometry._face->setVertexArray(partDrawInfo._vertexes);
		partGeometry._face->setColorArray(colorsFace);
		partGeometry._face->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
		partGeometry._face->setNormalArray(partDrawInfo._normals);
		partGeometry._face->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
		partGeometry._face->setUseVertexBufferObjects(true);
		partGeometry._line->setVertexArray(NULL);
		partGeometry._line->setColorArray(colorsLine);
		partGeometry._line->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
		partGeometry._line->setNormalArray(partDrawInfo._normals);
		partGeometry._line->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
		partGeometry._line->setUseVertexBufferObjects(true);

		_showCtrl.insert(std::make_pair(partDrawInfo._name, partGeometry));
		const osg::BoundingBox& box = partGeometry._face->getBound();
		float lengthX = box.xMax() - box.xMin();
		float lengthY = box.yMax() - box.yMin();
		float lengthZ = box.zMax() - box.zMin();
		beg->second._centerBox = box.center();
		beg->second._sizeBox = osg::Vec3(lengthX, lengthY, lengthZ);
		lengthX += lengthX/100;
		lengthY += lengthY/100;
		lengthZ += lengthZ/100;
		partGeometry._box->setShape(new osg::Box(box.center(), lengthX, lengthY, lengthZ));
		partGeometry._box->setColor(partGeometry._boxColor);
	}

	return _geode;
}
void DrawTarget::ShowGrid(const std::string& partName, bool show)
{
	TargetDrawInfo::iterator iter = _partsDrawInfo->find(partName);
	if(iter != _partsDrawInfo->end())
	{
		std::map<std::string, PartGeometry>::iterator iter2 = _showCtrl.find(partName);
		if(iter2 != _showCtrl.end())
		{
			if(show)
				iter2->second._line->setVertexArray(iter->second._vertexes);
			else
				iter2->second._line->setVertexArray(NULL);
		}
	}
}
void DrawTarget::ShowPart(const std::string& partName, bool show)
{
	if(show)
	{
		SetPartFaceColor(partName);
	}
	else
	{
		SetPartFaceColor(partName, osg::Vec4d(0, 0, 0, 0));
	}
}
void DrawTarget::ShowWireframe()
{
	for(TargetDrawInfo::iterator beg = _partsDrawInfo->begin(); beg != _partsDrawInfo->end(); ++beg)
	{
		std::map<std::string, PartGeometry>::iterator iter2 = _showCtrl.find(beg->first);
		if(iter2 != _showCtrl.end())
		{
			iter2->second._line->setVertexArray(beg->second._vertexes);
			iter2->second._face->setVertexArray(NULL);
			iter2->second._box->setColor(iter2->second._boxColor);
		}
	}
}
void DrawTarget::ShowFace()
{
	for(TargetDrawInfo::iterator beg = _partsDrawInfo->begin(); beg != _partsDrawInfo->end(); ++beg)
	{
		std::map<std::string, PartGeometry>::iterator iter2 = _showCtrl.find(beg->first);
		if(iter2 != _showCtrl.end())
		{
			iter2->second._line->setVertexArray(NULL);
			iter2->second._face->setVertexArray(beg->second._vertexes);
			iter2->second._box->setColor(iter2->second._boxColor);
		}
	}
}
void DrawTarget::ShowWireframeAndFace()
{
	for(TargetDrawInfo::iterator beg = _partsDrawInfo->begin(); beg != _partsDrawInfo->end(); ++beg)
	{
		std::map<std::string, PartGeometry>::iterator iter2 = _showCtrl.find(beg->first);
		if(iter2 != _showCtrl.end())
		{
			iter2->second._line->setVertexArray(beg->second._vertexes);
			iter2->second._face->setVertexArray(beg->second._vertexes);
			iter2->second._box->setColor(iter2->second._boxColor);
		}
	}
}
void DrawTarget::ShowBoundBox()
{
	for(TargetDrawInfo::iterator beg = _partsDrawInfo->begin(); beg != _partsDrawInfo->end(); ++beg)
	{
		std::map<std::string, PartGeometry>::iterator iter2 = _showCtrl.find(beg->first);
		if(iter2 != _showCtrl.end())
		{
			iter2->second._line->setVertexArray(NULL);
			iter2->second._face->setVertexArray(NULL);
			osg::Vec4 color = iter2->second._boxColor;
			color[3] = 0.9;
			iter2->second._box->setColor(color);
		}
	}
}
void DrawTarget::SetPartFaceColor(const std::string& partName, const osg::Vec4& color)
{
	std::map<std::string, PartGeometry>::iterator iter = _showCtrl.find(partName);
	if(iter != _showCtrl.end())
	{
		osg::Geometry* geom = iter->second._face;
		osg::Vec4Array* colors = dynamic_cast<osg::Vec4Array*>(geom->getColorArray());
		for(int i=0; i<colors->size(); ++i)
		{
			colors->at(i) = color;
		}
		colors->dirty();
	}
}
void DrawTarget::SetPartFaceColor(const std::string& partName, const std::vector<int>& facesIndex, const osg::Vec4& color)
{
	std::map<std::string, PartGeometry>::iterator iter = _showCtrl.find(partName);
	if(iter != _showCtrl.end())
	{
		osg::Geometry* geom = iter->second._face;
		osg::Vec4Array* colors = dynamic_cast<osg::Vec4Array*>(geom->getColorArray());
		for(int i=0; i<facesIndex.size(); ++i)
		{
			colors->at(i) = color;
		}
		colors->dirty();
	}
}


