#include "scene_view.h"
#include "ViewerWidget.h"
#include "osg_tool.h"
#include "compass_hud.h"
#include "global_config.h"
#include "pick_handler.h"
#include "UIEventCallback.h"
#include <osgViewer/Viewer>
#include <osgText/Text>
#include <osgQt/QWidgetImage>
#include <osg/Group>
#include <tool/tool.h>

SceneView::StaticMembers SceneView::s_sm_;

SceneView::StaticMembers::StaticMembers()
{
	render_type_names_map_[GBK2Unicode("点")] = SceneView::kPoint;
	render_type_names_map_[GBK2Unicode("线框")] = SceneView::kWireFrame;
	render_type_names_map_[GBK2Unicode("面")] = SceneView::kFace;
	render_type_names_map_[GBK2Unicode("边面")] = SceneView::kEdgeAndFace;

	view_type_names_map_[GBK2Unicode("透视图")] = SceneView::kPerspective;
	view_type_names_map_[GBK2Unicode("顶视图")] = SceneView::kTopView;
	view_type_names_map_[GBK2Unicode("底视图")] = SceneView::kBottomView;
	view_type_names_map_[GBK2Unicode("前视图")] = SceneView::kFrontView;
	view_type_names_map_[GBK2Unicode("后视图")] = SceneView::kBackView;
	view_type_names_map_[GBK2Unicode("左视图")] = SceneView::kLeftView;
	view_type_names_map_[GBK2Unicode("右视图")] = SceneView::kRightView;

}

SceneView::SceneView(QWidget* parent)
: QMainWindow(parent)
{
	ViewerWidget* viewer_widget = new ViewerWidget((osg::Node*)0);
	viewer_ = dynamic_cast<osgViewer::Viewer*>(viewer_widget->getViewer());
	scene_root_ = new osg::Group;
	grid_ = MakeGrid(kXY, 40, 1, osg::Vec4(0.83f, 0.83f, 0.83f, 0.5f), osg::Vec4(0.0f, 0.0f, 0.0f,0.5f));
	scene_root_->addChild(grid_);
	viewer_->setSceneData(scene_root_);
	osgGA::GUIEventHandler* pick_handler = new PickHandler(PickHandler::kVertex);
	viewer_->addEventHandler(pick_handler);
	CompassHud* compass_hud = new CompassHud(viewer_);
	scene_root_->addChild(compass_hud->CreateAxisHud(0, 0, 1000, 800));
	//osg::Geode* geode = CreateLables(osg::Vec3(100, 100, 0), 10, osg::Vec4(1.0, 0.0, 0.0, 1.0), "透视图");
	//scene_root_->addChild(geode);
	//view_type_ = dynamic_cast<osgText::Text*>(geode->getDrawable(0));
	//geode = CreateLables(osg::Vec3(100, 100, 0), 10, osg::Vec4(1.0, 0.0, 0.0, 1.0), "面");
	//scene_root_->addChild(geode);
	//render_type_ = dynamic_cast<osgText::Text*>(geode->getDrawable(0));

	QStatusBar* status_bar = new QStatusBar(this);
	status_bar->layout()->setSpacing(20);
	edit_hint_ = new QLineEdit(status_bar);
	edit_hint_->setReadOnly(true);
	edit_hint_->setText(GBK2Unicode("未选中任何对象"));
	status_bar->addWidget(edit_hint_, 1);
	QDoubleSpinBox** boxes[4] = {&box_mouse_pos_x_, &box_mouse_pos_y_, &box_mouse_pos_z_, &box_grid_};
	QString texts[4] = {"X", "Y", "Z", GBK2Unicode("栅格")};
	float stretches[4] = {0.2, 0.2, 0.2, 0.2};
	for(int i=0; i<4; ++i)
	{
		(*boxes[i]) = new QDoubleSpinBox(status_bar);
		(*boxes[i])->setReadOnly(true);
		(*boxes[i])->setSuffix(GlobalConfig::instance().get_length_unit());
		status_bar->addWidget(CreateLabelWidget(texts[i], *boxes[i]), stretches[i]);
	}
	box_grid_->setReadOnly(false);
	box_grid_->setValue(1);
	btn_scene_background_color_ = new QPushButton(status_bar);
	btn_scene_background_color_->setObjectName("bkc");
	status_bar->addWidget(CreateLabelWidget(GBK2Unicode("场景背景"), btn_scene_background_color_), 0.1);

	setCentralWidget(viewer_widget);
	setStatusBar(status_bar);

	//设置创建背景颜色按钮
	osg::Vec4 current_color = viewer_->getCamera()->getClearColor();
	QColor qt_color(current_color[0]*255, current_color[1]*255, current_color[2]*255, current_color[3]*255);
	SetBtnSceneBackgroundColor(qt_color);

	connect(box_grid_, SIGNAL(valueChanged(double)), this, SLOT(on_grid_changed(double)));
	connect(btn_scene_background_color_, SIGNAL(clicked()), this, SLOT(on_set_scene_background_color()));

	CreateViewAndRenderTypeButtons();


}

QWidget* SceneView::CreateLabelWidget(const QString& text, QWidget* widget)
{
	QWidget* result = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout(result);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(new QLabel(text, result));
	layout->addWidget(widget);
	return result;
}
void SceneView::on_set_scene_background_color()
{
	osg::Vec4 current_color = viewer_->getCamera()->getClearColor();
	QColor qt_color(current_color[0]*255, current_color[1]*255, current_color[2]*255, current_color[3]*255);
	qt_color = QColorDialog::getColor(qt_color, this);
	SetBtnSceneBackgroundColor(qt_color);
	current_color[0] = qt_color.redF();
	current_color[1] = qt_color.greenF();
	current_color[2] = qt_color.blueF();
	current_color[3] = qt_color.alphaF();
	viewer_->getCamera()->setClearColor(current_color);
}
void SceneView::on_grid_changed(double value)
{
	osg::Geode* grid = MakeGrid(kXY, 40, value, osg::Vec4(0.83f, 0.83f, 0.83f, 0.5f), osg::Vec4(0.0f, 0.0f, 0.0f,0.5f));
	scene_root_->replaceChild(grid_, grid);
	grid_ = grid;
}
void SceneView::on_view_type_changed()
{
	QMessageBox::warning(this, "X", "XX");

}
void SceneView::on_render_type_changed()
{

	QMessageBox::warning(this, "X", "XX");
}
void SceneView::on_image_mouse_push(QWidget* widget, const QPoint& pos)
{
	if(widget == btn_view_type_)
	{
		view_type_menu_->move(pos + mapToGlobal(this->pos()));
		view_type_menu_->exec();
	}
	else if(widget == btn_render_type_)
	{
		render_type_menu_->move(pos + mapToGlobal(this->pos()));
		render_type_menu_->exec();
	}
}
void SceneView::on_image_mouse_in(QWidget* widget)
{

}
void SceneView::on_image_mouse_out()
{

}
void SceneView::SetBtnSceneBackgroundColor(const QColor& color)
{
	QString style = QString("background:rgb(%1,%2,%3); border: 0px, flat").arg(color.red()).arg(color.green()).arg(color.blue());
	btn_scene_background_color_->setStyleSheet(style);
}

#include <osg/BlendFunc>
void SceneView::CreateViewAndRenderTypeButtons()
{
	QComboBox* widget = new QComboBox(this);
	widget->addItems(QStringList() << "XX" << "YY");
	widget->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
	widget->move(100, 100);
	widget->show();
	widget->setStyleSheet("background: transparent; border: 1px;");
	widget->setAutoFillBackground(false);
	QPalette pal;
	pal.setColor(QPalette::Background, QColor(225, 238, 245, 15));
	widget->setPalette(pal);
	//widget->setGeometry(10, 10, 80, 20);
	////widget->setFixedSize(QSize(145, 20));
	//QHBoxLayout* layout = new QHBoxLayout(widget);
	//layout->setContentsMargins(0, 0, 0, 0);
	//layout->setSpacing(0);
	//btn_view_type_ = new QPushButton(GBK2Unicode("透视图"));
	//layout->addWidget(btn_view_type_);
	//btn_view_type_->setFixedSize(QSize(25, 20));

	//btn_render_type_ = new QPushButton(GBK2Unicode("面"));
	//layout->addWidget(btn_render_type_);

	//view_type_menu_ = new QMenu(this);
	//QStringList view_types = GetViewTypeNames();
	//foreach(const QString& type, view_types)
	//{
	//	QAction* action = new QAction(type, widget);
	//	view_type_menu_->addAction(action);
	//	connect(action, SIGNAL(triggered()), this, SLOT(on_view_type_changed()));
	//}
	//render_type_menu_ = new QMenu(this);
	//QPalette pal;
	//pal.setColor(QPalette::Background, QColor(225, 238, 245, 125));
	//render_type_menu_->setPalette(pal);
	//QStringList render_types = GetRenderTypeNames();
	//foreach(const QString& type, render_types)
	//{
	//	QAction* action = new QAction(type, widget);
	//	render_type_menu_->addAction(action);
	//	connect(action, SIGNAL(triggered()), this, SLOT(on_render_type_changed()));
	//}

	//osg::ref_ptr<osgQt::QWidgetImage> widgetImage = new osgQt::QWidgetImage(widget);
	//widgetImage->getQWidget()->setAttribute(Qt::WA_TranslucentBackground);
	//widgetImage->getQGraphicsViewAdapter()->setBackgroundColor(QColor(0, 0, 0, 0));

	//osg::Texture2D* texture = new osg::Texture2D(widgetImage.get());
	//texture->setResizeNonPowerOfTwoHint(false);
	//texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR);
	//texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
	//texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);

	//osg::Geometry* quad = osg::createTexturedQuadGeometry(osg::Vec3(0,0,0), osg::Vec3(1,0,0), osg::Vec3(0,1,0), 1, 1);
	//osg::Geode* geode = new osg::Geode;
	//geode->addDrawable(quad);
	//quad->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
	//osg::BlendFunc* blf = new osg::BlendFunc;
	//blf->setFunction(osg::BlendFunc::ONE, osg::BlendFunc::ZERO);
	////quad->getOrCreateStateSet()->setAttributeAndModes(blf, osg::StateAttribute::ON);

	//osg::Camera* camera = new osg::Camera;
	//scene_root_->addChild(camera);
	//camera->addChild(geode);
	//camera->setProjectionResizePolicy(osg::Camera::FIXED);
	//camera->setProjectionMatrix(osg::Matrix::ortho2D(0, 1, 0, 1));
	//camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	//camera->setRenderOrder(osg::Camera::POST_RENDER);
	//camera->setClearMask(GL_DEPTH_BUFFER_BIT);
	//camera->setViewport(0, 0, widget->width(), widget->height());
	//osg::StateSet* ss = camera->getOrCreateStateSet();
	//ss->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	//ss->setMode(GL_BLEND, osg::StateAttribute::ON);
	//ss->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	//ss->setAttribute(new osg::Program);


	//UIEventCallback* handler = new UIEventCallback(widgetImage, texture, camera);
	//quad->setCullCallback(handler);
	//quad->setEventCallback(handler);
	//connect(handler, SIGNAL(sig_mouse_push(QWidget*, const QPoint&)), this, SLOT(on_image_mouse_push(QWidget*, const QPoint&)));
	//connect(handler, SIGNAL(sig_mouse_in(QWidget*)), this, SLOT(on_image_mouse_in(QWidget*)));
	//connect(handler, SIGNAL(sig_mouse_out()), this, SLOT(on_image_mouse_out()));

}
