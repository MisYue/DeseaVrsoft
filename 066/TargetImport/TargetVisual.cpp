//***************************************
//	创建时间:	2015:11:22   17:49
//	文件名称: 	TargetVisual.cpp
//	文件作者:	岳群磊
//	
//	功能说明:	实现目标可视化类
//***************************************

#include "TargetVisual.h"
#include "DrawTarget.h"
#include "targetInfo.h"
#include "UserTool.h"
#include "osgBase.h"
#include "FileOperation.h"
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/Material>
#include <osg/PolygonOffset>
#include <osg/BlendFunc>
#include <osg/Group>
#include <osg/Node>
#include <osg/Geode>
#include <osg/LineWidth>
#include <osg/StateSet>
#include <QTextStream>
#include <QFile>
#include <QStringList>
#include <QMessageBox>
#include <iostream>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

namespace TIMP
{
	TargetVisual::TargetVisual() : m_drawTarget(new DrawTarget)
	{
		m_scene = new osg::Group;
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(getViewer());
		viewer->setSceneData(m_scene);
		//坐标轴
		CompassHUD *pCompassHUD = new CompassHUD(viewer);
		m_scene->addChild( pCompassHUD->createCamera(0, 0, 1000, 800) );
		m_target = m_drawTarget->GetTarget();
		m_scene->addChild(m_target);
		//网格
		m_grid = MakeGrid("X-Y", 10, 1);
		m_scene->addChild(m_grid);
		osgGA::TrackballManipulator* manipulator = dynamic_cast<osgGA::TrackballManipulator*>(viewer->getCameraManipulator());
		const osg::BoundingSphere& box = m_scene->getBound();
		manipulator->setDistance(box.radius()*2);
		osg::Quat rotation(
			osg::DegreesToRadians(90.0f), osg::Vec3f(1.0f, 0.0f, 0.0f),
			osg::DegreesToRadians(90.0f), osg::Vec3f(0.0f, 0.0f, 1.0f),
			osg::DegreesToRadians(-30.0f), osg::Vec3f(0.0f, 1.0f, 0.0f)
			);
		manipulator->setRotation(rotation);
	}
	TargetVisual::~TargetVisual(void)
	{
	}

	void TargetVisual::Reset()
	{
		m_drawTarget->Reset();
	}
	bool TargetVisual::LoadFile(const std::string& fileName, TargetInfo* targetInfo)
	{
		FileOperation::ParseModel(fileName, *targetInfo);
		m_drawTarget->Draw(&targetInfo->GetPartDrawInfo());
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(getViewer());
		osgGA::TrackballManipulator* manipulator = dynamic_cast<osgGA::TrackballManipulator*>(viewer->getCameraManipulator());
		osg::BoundingSphere box = m_drawTarget->GetTarget()->getBound();
		if(box.radius() < 1)
			box = m_scene->getBound();
		manipulator->setDistance(box.radius()*2);
		osg::Node* grid = MakeGrid("X-Y", 10, box.radius()/10);
		m_scene->replaceChild(m_grid, grid);
		m_grid = grid;

		return true;
	}
	void TargetVisual::DrawPiFormat(const std::string& fileName)
	{

	}

	bool TargetVisual::PraseVrsModel(QString fileName, QuadModel *quadModel)
	{
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly))
		{
			QMessageBox::warning(this, "",
				QString::fromLocal8Bit("无法打开文件 %1！\n 原因:%2")
				.arg(fileName)
				.arg(file.errorString()));

			return false;
		}

		QTextStream inStream( &file );

		QString str;

		inStream>>str;
		int nCountComponent = str.toInt();

		inStream>>str;
		int nCountPoint = str.toInt();

		inStream>>str;
		quadModel->posCenterLine.x = str.toDouble();

		inStream>>str;
		quadModel->posCenterLine.y = str.toDouble();

		inStream>>str;
		quadModel->posCenterLine.z = str.toDouble();

		quadModel->nComponentNum = nCountComponent;
		quadModel->nPointNum = nCountPoint;

		int nGeomCount = 0;

		for (int nI=0; nI<nCountComponent; nI++)
		{
			Component *pComponent = new Component;

			inStream>>str;
			pComponent->strCode = str;

			inStream>>str;
			pComponent->strName = str;

			inStream>>str;
			pComponent->nCount = str.toInt();

			inStream>>str;
			pComponent->nMaterialID = str.toInt();

			inStream>>str;
			pComponent->lfThickness = str.toDouble();

			pComponent->nIndexStart = nGeomCount;

			nGeomCount += pComponent->nCount;

			for (int nJ=0; nJ<pComponent->nCount; nJ++)
			{
				PointIndexSum *indexSun = new PointIndexSum;

				if (fileName.endsWith(".txt"))
				{
					for (int nK=0; nK<pComponent->nMaterialID; nK++)
					{
						inStream>>str;
						int nID = str.toInt();

						indexSun->pointIndexList.push_back(nID);
					}

					pComponent->pointSumList.push_back(indexSun);
				}
				else
				{
					for (int nK=0; nK<3; nK++)
					{
						inStream>>str;
						int nID = str.toInt();

						indexSun->pointIndexList.push_back(nID);
					}

					pComponent->pointSumList.push_back(indexSun);
				}

			}

			quadModel->componentList.push_back(pComponent);
		}

		for (int nI=0; nI<nCountPoint; nI++)
		{
			PointValue pointValue;

			inStream>>str;
			pointValue.x = str.toDouble();

			inStream>>str;
			pointValue.y = str.toDouble();

			inStream>>str;
			pointValue.z = str.toDouble();

			quadModel->pointSum.pointList.push_back(pointValue);
		}
		file.close();
		return true;
	}

	bool TargetVisual::PraseQuadModel(QString fileName, QuadModel *quadModel)
	{
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly))
		{
			QMessageBox::warning(this, "",
				QString::fromLocal8Bit("无法打开文件 %1！\n 原因:%2")
				.arg(fileName)
				.arg(file.errorString()));

			return false;
		}
		QTextStream inStream( &file );
		QString str;
		inStream>>str;
		int nCountComponent = str.toInt();
		inStream>>str;
		int nCountPoint = str.toInt();
		inStream>>str;
		quadModel->posCenterLine.x = str.toDouble();
		inStream>>str;
		quadModel->posCenterLine.y = str.toDouble();
		inStream>>str;
		quadModel->posCenterLine.z = str.toDouble();
		quadModel->nComponentNum = nCountComponent;
		quadModel->nPointNum = nCountPoint;
		int nGeomCount = 0;
		for (int nI=0; nI<nCountComponent; nI++)
		{
			Component *pComponent = new Component;

			inStream>>str;
			pComponent->strCode = str;

			inStream>>str;
			pComponent->strName = str;

			inStream>>str;
			pComponent->nCount = str.toInt();

			inStream>>str;
			pComponent->nMaterialID = str.toInt();

			inStream>>str;
			pComponent->lfThickness = str.toDouble();

			pComponent->nIndexStart = nGeomCount;

			nGeomCount += pComponent->nCount;

			for (int nJ=0; nJ<pComponent->nCount; nJ++)
			{
				PointIndexSum *indexSun = new PointIndexSum;

				if (fileName.endsWith(".txt"))
				{
					for (int nK=0; nK<pComponent->nMaterialID; nK++)
					{
						inStream>>str;
						int nID = str.toInt();

						indexSun->pointIndexList.push_back(nID);
					}

					pComponent->pointSumList.push_back(indexSun);
				}
				else
				{
					for (int nK=0; nK<4; nK++)
					{
						inStream>>str;
						int nID = str.toInt();

						indexSun->pointIndexList.push_back(nID);
					}

					pComponent->pointSumList.push_back(indexSun);
				}

			}

			quadModel->componentList.push_back(pComponent);
		}

		for (int nI=0; nI<nCountPoint; nI++)
		{
			PointValue pointValue;

			inStream>>str;
			pointValue.x = str.toDouble();

			inStream>>str;
			pointValue.y = str.toDouble();

			inStream>>str;
			pointValue.z = str.toDouble();

			quadModel->pointSum.pointList.push_back(pointValue);
		}
		file.close();
		return true;
	}
	void TargetVisual::ShowPartGrid(const std::string& name, bool show)
	{
		m_drawTarget->ShowGrid(name, show);
	}
	void TargetVisual::ShowPart(const std::string& name, bool show)
	{
		m_drawTarget->ShowPart(name, show);
	}

	void TargetVisual::ShowWireframe()
	{
		m_drawTarget->ShowWireframe();
	}
	void TargetVisual::ShowWireframeAndFace()
	{
		m_drawTarget->ShowWireframeAndFace();
	}
	void TargetVisual::ShowFace()
	{
		m_drawTarget->ShowFace();
	}
	void TargetVisual::ShowBoundBox()
	{
		m_drawTarget->ShowBoundBox();
	}
	void TargetVisual::SetPartColor(const std::string& name, const osg::Vec4d& color)
	{
		m_drawTarget->SetPartFaceColor(name, color);
	}
	void TargetVisual::SetPartDefaultColor(const std::string& name)
	{
		m_drawTarget->SetPartFaceColor(name);
	}
	void TargetVisual::UpdatePartName(const std::string& oldName, const std::string& newName)
	{
		m_drawTarget->UpdatePartName(oldName, newName);
	}
}