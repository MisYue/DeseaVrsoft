//******************************************
//	����ʱ��:	2015:11:3   17:03
//	�ļ�����: 	GetVertex.h
//	�ļ�����:	��Ⱥ��
//	
//	����˵��:	�����ȡ�����嶥����
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
