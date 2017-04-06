//***************************************
//	����ʱ��:	2015:11:22   17:49
//	�ļ�����: 	TargetVisual.h
//	�ļ�����:	��Ⱥ��
//	
//	����˵��:	ʵ��Ŀ����ӻ���
//***************************************

#pragma once
#include "TargetImportGlobal.h"
#include <OsgTool/ViewerWidget.h>
#include <map>
#include <list>
#include <string>

class DrawTarget;
class QuadModel;
namespace osg
{
	class Node;
	class Geode;
	class Group;
	class PrimitiveSet;
	class Geometry;

}
//֧�����ָ�ʽ
//.dat(Ƥ��ʦ) .fbx(����ʦ��Ҳ֧������osg֧�ֵĸ�ʽ) .vrs(��˾�ĸ�ʽ)
namespace TIMP
{
	class TargetInfo;

class TARGETIMPORT_API TargetVisual : public ViewerWidget
{
	Q_OBJECT
public:
	TargetVisual();
	~TargetVisual(void);
	bool LoadFile(const std::string& fileName, TargetInfo* targetInfo);
	void SetPartColor(const std::string& name, const osg::Vec4d& color);
	void SetPartDefaultColor(const std::string& name);
	void ShowPartGrid(const std::string& name, bool show=true);
	void ShowPart(const std::string& name, bool show);
	void Reset();
	osg::Group* GetRoot()
	{
		return m_scene;
	}
	osg::Node* GetTarget()
	{
		return m_target;
	}
public slots:
	void ShowWireframe();
	void ShowWireframeAndFace();
	void ShowFace();
	void ShowBoundBox();
	void UpdatePartName(const std::string& oldName, const std::string& newName);
private:
	DrawTarget* m_drawTarget;
	osg::ref_ptr<osg::Group> m_scene;
	osg::ref_ptr<osg::Node> m_target;
	osg::ref_ptr<osg::Node> m_grid;
	std::map<std::string, osg::Geometry*> m_parts;
	void DrawPiFormat(const std::string& fileName);
	void ParseGeode(osg::Geode* geode);
	bool PraseQuadModel(QString fileName, QuadModel *quadModel);
	bool PraseVrsModel(QString fileName, QuadModel *quadModel);
};

}
