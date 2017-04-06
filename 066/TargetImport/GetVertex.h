//******************************************
//	创建时间:	2015:11:3   17:03
//	文件名称: 	GetVertex.h
//	文件作者:	岳群磊
//	
//	功能说明:	定义获取绘制体顶点类
//*****************************************
#pragma once
#include <osg/Drawable>
#include <osg/TriangleFunctor>

struct GetVertex
{
	void operator() (const osg::Vec3& v1,const osg::Vec3& v2,const osg::Vec3& v3, bool) const
	{
		_vertexList->push_back(v1);
		_vertexList->push_back(v2);
		_vertexList->push_back(v3);
	}
	osg::Vec3Array* _vertexList;

	static void getTriangles(osg::Vec3Array* vertexList, const osg::Drawable& drawable)
	{
		osg::TriangleFunctor<GetVertex> tf;
		tf._vertexList = vertexList;
		drawable.accept(tf);
	}
};
