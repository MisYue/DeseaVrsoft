
#include <QtCore/QCoreApplication>
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osg/Group>
#include <osgUtil/Optimizer>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group;
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("mymap.earth");
	root->addChild(node);
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root);
	viewer->setSceneData(root);
	viewer->realize();
	viewer->run();
	return a.exec();
}
