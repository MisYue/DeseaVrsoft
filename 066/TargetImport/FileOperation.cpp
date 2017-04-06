//***************************************
//	创建时间:	2015:10:29   17:15
//	文件名称: 	FileOperation.cpp
//	文件作者:	岳群磊
//	
//	功能说明:	实现文件操作类
//***************************************

#include "FileOperation.h"
#include "GetPartDrawInfo.h"
#include "ui_PartRecognitionMethod.h"
#include "PreProcessModel.h"
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <QApplication>

void FileOperation::ParseModel(const std::string& fileName, TIMP::TargetInfo& targetInfo)
{
	if(fileName.find(".dat") == fileName.size()-4)
		ParsePiModel(fileName, targetInfo);
	else if(fileName.find(".vrs") == fileName.size()-4)
		ParseVrsModel(fileName, targetInfo);
	else
		ParseLiModel(fileName, targetInfo);
} 
void FileOperation::SaveModel(const std::string& fileName, const TIMP::TargetInfo& targetInfo)
{
}
void FileOperation::ParseLiModel(const std::string& fileName, TIMP::TargetInfo& targetInfo)
{
	targetInfo.Reset();

	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(fileName);
	osg::ref_ptr<osg::MatrixTransform> mat = new osg::MatrixTransform;
	mat->addChild(node);

	PreProcessModel dlg(mat);
	if(QDialog::Accepted == dlg.exec())
	{
		if(PreProcessModel::REG_NODE == dlg.getPartRecognitionMethod())
		{
			FindGeometryVisitor fgv(targetInfo.GetPartDrawInfo());
			mat->accept(fgv);
		}
		if(PreProcessModel::REG_NAME == dlg.getPartRecognitionMethod())
		{
			FindPartVisitor fgv(targetInfo.GetPartDrawInfo());
			mat->accept(fgv);
		}
		targetInfo.UpdateExtraInfo();
	}
}	 
void FileOperation::ParsePiModel(const std::string& fileName, TIMP::TargetInfo& targetInfo)
{
	targetInfo.Reset();
}	 
void FileOperation::ParseVrsModel(const std::string& fileName, TIMP::TargetInfo& targetInfo)
{
	targetInfo.Reset();
	targetInfo.OpenTarget(fileName);
}