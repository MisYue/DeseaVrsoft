//***************************************
//	创建时间:	2015:11:10   17:39
//	文件名称: 	PreProcessModel.h
//	文件作者:	岳群磊
//	
//	功能说明:	定义模型预处理类
//***************************************

#pragma once
#include <QDialog>
#include <osg/MatrixTransform>
#include <osg/Group>
#include <osg/Node>
#include <osgFx/Scribe>
#include <osgViewer/Viewer>
#include <map>
#include <string>
#include <QMap>

class QListWidgetItem;
namespace Ui{ class PreProcessModel; }
class PreProcessModel : public QDialog
{
	Q_OBJECT
public:
	PreProcessModel(osg::MatrixTransform* node, QWidget* parent = NULL);
	~PreProcessModel();
	int getPartRecognitionMethod();
	enum PartRegMethod
	{
		REG_NAME,
		REG_NODE,
	};
public slots:
	void onModelUnitChanged(const QString & text);
	void onMatrixChanged(double);
	void onPartRecognitionMethodChanged(bool);
	void onPartItemClicked(QListWidgetItem* item);
	void onGridChanged(double value);
private:
	Ui::PreProcessModel* _ui;
	osg::ref_ptr<osg::MatrixTransform> _node;
	osg::ref_ptr<osg::MatrixTransform> _grid;
	osg::ref_ptr<osg::Group> _scene;
	osg::ref_ptr<osgViewer::Viewer> _viewer;
	double _unitFactor;
	std::map<std::string, osg::Node*> _parts;
	osg::ref_ptr<osgFX::Scribe> _scribe;
	QMap<QString, double> _unitFactorMap;
};
