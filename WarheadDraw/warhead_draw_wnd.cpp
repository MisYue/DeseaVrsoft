#include "warhead_draw_wnd.h"
#include "view_structure.h"
#include "view_2d.h"
#include "view_3d.h"
#include <BasicTool/expandqtcore.h>
#include <WarheadModelData/warhead_model.h>

WarheadDrawWnd::WarheadDrawWnd(WarheadModelWrap* model_wrap, Mode mode, QWidget* parent)
	: QMainWindow(parent)
	, view_2d_(new View2D(this))
	, view_3d_(new View3D(this))
	, view_structure_(new ViewStructure(this))
	, model_wrap_(model_wrap)
	, model_(model_wrap->get_structure())
	, mode_(mode)
{
	view_structure_->set_view_2d(view_2d_);

	QDockWidget* dock = new QDockWidget(ExpandQtCore::fromGBK("模型结构"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea);
	dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
	dock->setWidget(view_structure_);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
	if(mode_ == kView)
	{
		dock->hide();
	}
	QTabWidget* tab_widget = new QTabWidget(this);
	tab_widget->setTabPosition(QTabWidget::North);
	tab_widget->addTab(view_2d_, ExpandQtCore::fromGBK("二维"));
	tab_widget->addTab(view_3d_, ExpandQtCore::fromGBK("三维"));

	setCentralWidget(tab_widget);

	set_model(model_wrap_);
}

void WarheadDrawWnd::set_model(WarheadModelWrap* model_wrap)
{
	model_wrap_ = model_wrap;
	model_ = model_wrap_->get_structure();
	view_2d_->set_model_wrap(model_wrap_);
	view_3d_->set_model(model_);
	view_structure_->Reset();
}

void WarheadDrawWnd::update_cs()
{
	view_2d_->on_cs_changed();
}
void WarheadDrawWnd::SaveStructure(const QString& name)
{
	view_2d_->SaveStructure(name);
	view_3d_->Write(name);
}

WarheadDrawBase* WarheadDrawWnd::GetPainter2D()
{
	return view_2d_->GetPainter2D();
}
WarheadDrawBase* WarheadDrawWnd::GetPainter3D()
{
	return view_3d_;
}