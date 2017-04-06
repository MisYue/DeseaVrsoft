#pragma once

#include <QtGui>

namespace osg { 
	class Group; 
	class Geode;
}
namespace osgViewer { class Viewer; }
namespace osgText { class Text; }
class SceneView : public QMainWindow
{
	Q_OBJECT
public:
	enum ViewType
	{
		kErrorViewType,		//错误类型
		kPerspective,		//透视图
		kTopView,			//顶视图
		kBottomView,		//底视图
		kFrontView,			//前视图
		kBackView,			//后视图
		kLeftView,			//左视图
		kRightView,			//右视图
	};
	enum RenderType
	{
		kErrorRenderType,	//错误类型
		kPoint = 0,			//点
		kWireFrame,			//线框
		kFace,				//面
		kEdgeAndFace,		//边面
	};
	SceneView(QWidget* parent = 0);
	static QStringList GetViewTypeNames() { return s_sm_.view_type_names_map_.keys(); }
	static QStringList GetRenderTypeNames() { return s_sm_.render_type_names_map_.keys(); }
	static ViewType GetViewType(const QString& type) { return s_sm_.view_type_names_map_.value(type, kErrorViewType); }
	static QString GetViewType(ViewType type) { return s_sm_.view_type_names_map_.key(type, QString()); }
	static RenderType GeRenderType(const QString& type) { return s_sm_.render_type_names_map_.value(type, kErrorRenderType); }
	static QString GetRenderType(RenderType type) { return s_sm_.render_type_names_map_.key(type, QString()); }

private slots:
	void on_set_scene_background_color();
	void on_grid_changed(double value);
	void on_view_type_changed();
	void on_render_type_changed();
	void on_image_mouse_push(QWidget* widget, const QPoint& pos);
	void on_image_mouse_in(QWidget* widget);
	void on_image_mouse_out();

private:
	struct StaticMembers
	{
		StaticMembers();
		QMap<QString, ViewType> view_type_names_map_;
		QMap<QString, RenderType> render_type_names_map_;
	};
	static StaticMembers s_sm_;
	osg::Group* scene_root_;
	osg::Geode* grid_;
	osgText::Text* view_type_;
	osgText::Text* render_type_;
	osgViewer::Viewer* viewer_;
	QMenu* view_type_menu_;
	QMenu* render_type_menu_;
	QLineEdit* edit_hint_;	//场景操作提示框
	QDoubleSpinBox* box_mouse_pos_x_;	//鼠标位置X坐标显示框
	QDoubleSpinBox* box_mouse_pos_y_;	//鼠标位置Y坐标显示框
	QDoubleSpinBox* box_mouse_pos_z_;	//鼠标位置Z坐标显示框
	QDoubleSpinBox* box_grid_;	//栅格输入框
	QPushButton* btn_scene_background_color_;	//场景背景颜色选择按钮
	QPushButton* btn_view_type_;
	QPushButton* btn_render_type_;
private:
	QWidget* CreateLabelWidget(const QString& text, QWidget* widget);
	void SetMousePoint();
	void SetBtnSceneBackgroundColor(const QColor& color);
	void CreateViewAndRenderTypeButtons();
};

