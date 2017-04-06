#pragma once
#include <WarheadDraw/warhead_draw_global.h>
#include <WarheadDraw/WarheadDrawBase.h>
#include <WarheadModelData/WarheadModelWrap.h>
#include <QtWidgets>

class ViewStructure;
class View2D;
class View3D;
class WarheadModel;

class WARHEADDRAW_EXPORT WarheadDrawWnd : public QMainWindow
{
	Q_OBJECT
public:
	enum Mode
	{
		kView,
		kEdit,  
	};
	WarheadDrawWnd(WarheadModelWrap* model_wrap=0, Mode mode = kEdit, QWidget* parent=0);
	void set_model(WarheadModelWrap* model_wrap);
	void update_cs();
	void SaveStructure(const QString& name);
	WarheadDrawBase* GetPainter2D();
	WarheadDrawBase* GetPainter3D();
private:
	ViewStructure* view_structure_;
	View2D* view_2d_;
	View3D* view_3d_;
	WarheadModelWrap* model_wrap_;
	WarheadModel* model_;
	Mode mode_;
};