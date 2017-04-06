//***************************************
//	创建时间:	2015:11:10   17:39
//	文件名称: 	ProPrecessModel.cpp
//	文件作者:	岳群磊
//	
//	功能说明:	实现模型预处理类
//***************************************
#include <OsgTool/ViewerWidget.h>
#include "PreProcessModel.h"
#include "ui_PreProcessModel.h"
#include "UserTool.h"
#include "osgBase.h"
#include <QHBoxLayout>
#include <osg/ComputeBoundsVisitor>
#include <osg/NodeVisitor>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <QMap>
#include <map>
#include <iostream>

class PartVisitor : public osg::NodeVisitor
{
public:
	PartVisitor(std::map<std::string, osg::Node*>& parts, int method)
		: _parts(parts), _method(method),
		  osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN){}
	virtual void apply(osg::Node& node)
	{
		std::string name = QString::fromUtf8(node.getName().c_str()).toLocal8Bit().data();

		if(PreProcessModel::REG_NODE == _method)
		{
			if(node.asGeode())
			{
				_parts.insert(std::make_pair(name, &node));
			}
			else
			{
				traverse(node);
			}
		}
		else
		{
			std::string substr;
			if(name.size() > 3)
			{
				substr = name.substr(name.size()-2);
			}
			if(name.size() < 3 || (substr != "/p" && substr != "_p"))
			{
				traverse(node);
			}
			else
			{
				name = name.substr(0, name.size()-2);
				_parts.insert(std::make_pair(name, &node));
			}		
		}
	}
private:
	std::map<std::string, osg::Node*>& _parts;
	int _method;
};

PreProcessModel::PreProcessModel(osg::MatrixTransform* node, QWidget* parent)
	: _node(node), QDialog(parent), _ui(new Ui::PreProcessModel)
{
	_unitFactorMap[QString::fromLocal8Bit("米")] = 1;
	_unitFactorMap[QString::fromLocal8Bit("厘米")] = 0.01;
	_unitFactorMap[QString::fromLocal8Bit("毫米")] = 0.001;

	_ui->setupUi(this);
	_scene = new osg::Group;
	_scene->addChild(_node);
	ViewerWidget* viewerWidget = new TIMP::ViewerWidget(_scene);
	_viewer = dynamic_cast<osgViewer::Viewer*>(viewerWidget->getViewer());
	QHBoxLayout* layout =new QHBoxLayout;
	_ui->widget->setLayout(layout);
	layout->addWidget(viewerWidget);

	QString sysUnit = _ui->comboBox_sys_unit->currentText();
	_ui->doubleSpinBox_size_x->setSuffix(sysUnit);
	_ui->doubleSpinBox_size_y->setSuffix(sysUnit);
	_ui->doubleSpinBox_size_z->setSuffix(sysUnit);
	
	connect(_ui->comboBox_model_unit, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onModelUnitChanged(const QString&)));
	connect(_ui->doubleSpinBox_scale_x, SIGNAL(valueChanged(double)), this, SLOT(onMatrixChanged(double)));
	connect(_ui->doubleSpinBox_scale_y, SIGNAL(valueChanged(double)), this, SLOT(onMatrixChanged(double)));
	connect(_ui->doubleSpinBox_scale_z, SIGNAL(valueChanged(double)), this, SLOT(onMatrixChanged(double)));
	connect(_ui->doubleSpinBox_rotate_x, SIGNAL(valueChanged(double)), this, SLOT(onMatrixChanged(double)));
	connect(_ui->doubleSpinBox_rotate_y, SIGNAL(valueChanged(double)), this, SLOT(onMatrixChanged(double)));
	connect(_ui->doubleSpinBox_rotate_z, SIGNAL(valueChanged(double)), this, SLOT(onMatrixChanged(double)));
	connect(_ui->doubleSpinBox_grid, SIGNAL(valueChanged(double)), this, SLOT(onGridChanged(double)));
	connect(_ui->radioButton_node, SIGNAL(toggled(bool)), this, SLOT(onPartRecognitionMethodChanged(bool)));
	connect(_ui->radioButton_name, SIGNAL(toggled(bool)), this, SLOT(onPartRecognitionMethodChanged(bool)));
	connect(_ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onPartItemClicked(QListWidgetItem*)));

	_grid = new osg::MatrixTransform;
	_scene->addChild(_grid);
	//坐标轴
	CompassHUD *pCompassHUD = new CompassHUD(_viewer);
	_scene->addChild( pCompassHUD->createCamera(0, 0, 1000, 800) );

	QString modelUnit = _ui->comboBox_model_unit->currentText();
	onModelUnitChanged(modelUnit);

	osgGA::TrackballManipulator* manipulator = dynamic_cast<osgGA::TrackballManipulator*>(_viewer->getCameraManipulator());
	const osg::BoundingSphere& box = _node->getBound();
	manipulator->setDistance(box.radius()*2);

	_scribe = new osgFX::Scribe;
	_scribe->setWireframeColor(osg::Vec4(71/255.0, 160/255.0, 156/255.0, 0.9));

	PartVisitor visitor(_parts, getPartRecognitionMethod());
	_node->accept(visitor);

//	_node->setMatrix(osg::Matrix::rotate(osg::Vec3(0, 0, -1), osg::Vec3(1, 0, 0)) );
}
PreProcessModel::~PreProcessModel()
{
	if(_ui)
		delete _ui;
}
int PreProcessModel::getPartRecognitionMethod()
{
	int method = REG_NAME;
	if(_ui->radioButton_node->isChecked())
		method = REG_NODE;
	return method;
}
void PreProcessModel::onModelUnitChanged(const QString& text)
{
	_unitFactor = _unitFactorMap[text] / _unitFactorMap[_ui->comboBox_sys_unit->currentText()];
	onMatrixChanged(double());
}
void PreProcessModel::onMatrixChanged(double)
{
	double scaleX = _ui->doubleSpinBox_scale_x->value()*_unitFactor;
	double scaleY = _ui->doubleSpinBox_scale_y->value()*_unitFactor;
	double scaleZ = _ui->doubleSpinBox_scale_z->value()*_unitFactor;
	double rotateX = osg::DegreesToRadians(_ui->doubleSpinBox_rotate_x->value());
	double rotateY = osg::DegreesToRadians(_ui->doubleSpinBox_rotate_y->value());
	double rotateZ = osg::DegreesToRadians(_ui->doubleSpinBox_rotate_z->value());

	osg::Quat rotation(
		rotateX, osg::Vec3f(1.0f, 0.0f, 0.0f),
		rotateY, osg::Vec3f(0.0f, 1.0f, 0.0f),
		rotateZ, osg::Vec3f(0.0f, 0.0f, 1.0f)
		);
	//double x = sin(rotateY / 2) * sin(rotateZ / 2) * cos(rotateX / 2) + cos(rotateY / 2) * cos(rotateZ / 2) * sin(rotateX / 2);
	//double y = sin(rotateY / 2) * cos(rotateZ / 2) * cos(rotateX / 2) + cos(rotateY / 2) * sin(rotateZ / 2) * sin(rotateX / 2);
	//double z = cos(rotateY / 2) * sin(rotateZ / 2) * cos(rotateX / 2) + sin(rotateY / 2) * cos(rotateZ / 2) * sin(rotateX / 2);
	//double w = cos(rotateY / 2) * cos(rotateZ / 2) * cos(rotateX / 2) + sin(rotateY / 2) * sin(rotateZ / 2) * sin(rotateX / 2);
	//osg::Quat rotation(x, y, z, w);
	osg::Matrix mt;
	rotation.get(mt);
	_node->setMatrix(mt*osg::Matrix::scale(osg::Vec3(scaleX, scaleY, scaleZ)));
	//osg::Vec4d v4 = rotation.asVec4();
	double angle;
	osg::Vec3d v3;
	rotation.getRotate(angle, v3);
	std::cout << angle << " " << v3[0] << " " << v3[1] << " " << v3[2] << std::endl;
	//std::cout << w << " " << x << " " << y << " " << z << std::endl;

	QDoubleSpinBox* doubleBox = qobject_cast<QDoubleSpinBox*>(sender());
	double grid = _node->getBound().radius()/10;
	onGridChanged(grid);
	_ui->doubleSpinBox_grid->setValue(grid);
	osgGA::TrackballManipulator* manipulator = dynamic_cast<osgGA::TrackballManipulator*>(_viewer->getCameraManipulator());
	const osg::BoundingSphere& box = _node->getBound();
	manipulator->setDistance(box.radius()*2);
	manipulator->setCenter(box.center());
	osg::ComputeBoundsVisitor boundvisitor;
	_node->accept(boundvisitor);
	osg::BoundingBox bb = boundvisitor.getBoundingBox();
	double sizeX = bb.xMax() - bb.xMin();
	double sizeY = bb.yMax() - bb.yMin();
	double sizeZ = bb.zMax() - bb.zMin();
	QString modelUnit = _ui->comboBox_model_unit->currentText();
	_ui->doubleSpinBox_size_x->setValue(sizeX);
	_ui->doubleSpinBox_size_y->setValue(sizeY);
	_ui->doubleSpinBox_size_z->setValue(sizeZ);
}

void PreProcessModel::onPartRecognitionMethodChanged(bool)
{
	_parts.clear();
	PartVisitor visitor(_parts, getPartRecognitionMethod());
	_node->accept(visitor);
	_ui->listWidget->clear();
	QStringList labels;
	for(std::map<std::string, osg::Node*>::iterator beg = _parts.begin(); beg != _parts.end(); ++beg)
	{
		labels.push_back(QString::fromLocal8Bit(beg->first.c_str()));
	}
	_ui->listWidget->addItems(labels);
}
void PreProcessModel::onPartItemClicked(QListWidgetItem* item)
{
	if(_scribe->getNumChildren()>0)
	{
		osg::ref_ptr<osg::Node> node = _scribe->getChild(0);
		_scribe->removeChild(node);
		_scribe->getParent(0)->replaceChild(_scribe, node);
	}
	std::map<std::string, osg::Node*>::iterator iter = _parts.find(item->text().toLocal8Bit().data());
	if(iter != _parts.end())
	{
		osg::ref_ptr<osg::Node> node = iter->second;
		_scribe->addChild(node);
		node->getParent(0)->replaceChild(node, _scribe);			
	}
}
void PreProcessModel::onGridChanged(double value)
{
	osg::MatrixTransform* grid = MakeGrid("X-Y", 10, value);
	_scene->replaceChild(_grid, grid);
	_grid = grid;
}