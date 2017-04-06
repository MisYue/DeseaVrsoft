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
		kErrorViewType,		//��������
		kPerspective,		//͸��ͼ
		kTopView,			//����ͼ
		kBottomView,		//����ͼ
		kFrontView,			//ǰ��ͼ
		kBackView,			//����ͼ
		kLeftView,			//����ͼ
		kRightView,			//����ͼ
	};
	enum RenderType
	{
		kErrorRenderType,	//��������
		kPoint = 0,			//��
		kWireFrame,			//�߿�
		kFace,				//��
		kEdgeAndFace,		//����
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
	QLineEdit* edit_hint_;	//����������ʾ��
	QDoubleSpinBox* box_mouse_pos_x_;	//���λ��X������ʾ��
	QDoubleSpinBox* box_mouse_pos_y_;	//���λ��Y������ʾ��
	QDoubleSpinBox* box_mouse_pos_z_;	//���λ��Z������ʾ��
	QDoubleSpinBox* box_grid_;	//դ�������
	QPushButton* btn_scene_background_color_;	//����������ɫѡ��ť
	QPushButton* btn_view_type_;
	QPushButton* btn_render_type_;
private:
	QWidget* CreateLabelWidget(const QString& text, QWidget* widget);
	void SetMousePoint();
	void SetBtnSceneBackgroundColor(const QColor& color);
	void CreateViewAndRenderTypeButtons();
};

