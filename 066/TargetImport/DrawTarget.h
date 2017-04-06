//***************************************
//	创建时间:	2015:11:6   17:36
//	文件名称: 	DrawTarget.h
//	文件作者:	岳群磊
//	
//	功能说明:	定义绘制部件类
//***************************************

#pragma once
#include "targetInfo.h"
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <map>

using namespace TIMP;
class DrawTarget
{
public:
	DrawTarget();
	osg::Geode* Draw(TargetDrawInfo* drawInfo);
	void Reset();
	osg::Node* GetTarget()
	{
		return _geode;
	}
	void ShowGridAndFace(const std::string& partName);
	void ShowGrid(const std::string& partName , bool show = true);
	void ShowPart(const std::string& partName, bool show);
	void ShowWireframe();
	void ShowFace();
	void ShowWireframeAndFace();
	void ShowBoundBox();
	void SetPartFaceColor(const std::string& partName, const osg::Vec4& color = osg::Vec4(180/255.0, 180/255.0, 180/255.0, 0.7));
	void SetPartFaceColor(const std::string& partName, const std::vector<int>& facesIndex, const osg::Vec4& color);
	void UpdatePartName(const std::string& oldName, const std::string& newName)
	{
		if(oldName == newName)
			return ;
		std::map<std::string, PartGeometry>::iterator iter = _showCtrl.find(oldName);
		if(iter != _showCtrl.end())
		{
			_showCtrl.insert(std::make_pair(newName, iter->second));
			_showCtrl.erase(iter);
		}
	}
private:
	osg::ref_ptr<osg::Geode> _geode;
	struct PartGeometry
	{
		//bool _bShow;
		osg::ref_ptr<osg::Geometry> _face;
		osg::ref_ptr<osg::Geometry> _line;
		osg::ref_ptr<osg::ShapeDrawable> _box;
		osg::Vec4 _faceColor;
		osg::Vec4 _lineColor;
		osg::Vec4 _boxColor;
		PartGeometry()
			: _face(new osg::Geometry), _line(new osg::Geometry), _box(new osg::ShapeDrawable),
			 _faceColor(180/255.0, 180/255.0, 180/255.0, 0.7), _lineColor(0.2, 0.1, 0.8, 0.9), _boxColor(0.0, 1.0, 0.0, 0.0)
		{}
	};
	std::map<std::string, PartGeometry> _showCtrl;
	TargetDrawInfo* _partsDrawInfo;
};

