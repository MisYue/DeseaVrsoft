#ifndef VIEW_3D_H
#define VIEW_3D_H
#include "WarheadDrawBase.h"
#include <QtWidgets>

class ViewerWidget;
class WarheadNode;
class WarheadModel;
namespace osg { 
	class Group; 
	class Geode;
}
namespace osgViewer { class Viewer; }

class View3D : public QMainWindow, public WarheadDrawBase
{
public:
	View3D(QWidget* parent = 0);
	~View3D();
	// Ð´ÈëÎÄ¼þ
	virtual bool Write(const QString& file_name);

private:
	ViewerWidget* viewer_widget_;
	osgViewer::Viewer* viewer_;
	osg::Group* model_group_;
	osg::Group* model_outer_shell_;
	osg::Group* scene_root_;
	osg::Geode* grid_;
protected:
	virtual void showEvent(QShowEvent * event);
	void DrawModel();
	void UpdateGrid();
	void DrawOuterShell();

};

#endif // VIEW_3D_H
