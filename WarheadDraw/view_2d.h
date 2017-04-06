#pragma once
#include <QtWidgets>

namespace Ui { class View2D; }
class WarheadModel;
class WarheadSection;
class WarheadLayer;
class WarheadFirePoint;
class Scene2D;
class WarheadNode;
class WarheadEndCap;
class ScaleView2D;
class WarheadDrawBase;

enum NodeType
{
	kNTModel,
	kNTSection,
	kNTLayer,
	kNTEndCap,
	kNTFirePoint,
	kNTCS,
};

struct Node
{
	NodeType type;
	WarheadNode* node;
};

class WarheadModelWrap;
class View2D : public QMainWindow
{
	Q_OBJECT
public:
	View2D(QWidget* parent=0);
	~View2D();
	void set_model_wrap(WarheadModelWrap* model_wrap);
	WarheadModel* get_model() { return model_; }
	QList<QAction*> get_actions() const;
	void SaveStructure(const QString& name);
	void SetViewMode() { only_view_ = true; }
	WarheadDrawBase* GetPainter2D();
public slots:
	void on_add_section();
	void on_delete_section();
	void on_add_layer();
	void on_delete_layer();
	void on_add_end_cap();
	void on_delete_end_cap();
	void on_add_fire_point();
	void on_delete_fire_point();
	void on_view_property();
	void on_current_node_changed(WarheadNode* node);
	void on_current_node_changed(const Node& node);

	void on_view_node_property(WarheadNode* node);
	void on_view_radio_changed(const QString& text);
	void on_view_scal_changed(double s);
	void on_cs_changed();
	void on_cs_edited();
signals:
	void sig_add_section(WarheadSection* section);
	void sig_delete_section(WarheadSection* section);
	void sig_add_layer(WarheadSection* section, WarheadLayer* layer);
	void sig_delete_layer(WarheadSection* section, WarheadLayer* layer);
	void sig_add_end_cap(WarheadEndCap* end_cap);
	void sig_delete_end_cap(WarheadEndCap* end_cap);
	void sig_add_fire_point(WarheadFirePoint* fire_point);
	void sig_delete_fire_point(WarheadFirePoint* fire_point);
	void sig_warhead_node_changed(WarheadNode* node);
	void sig_layer_type_changed(WarheadSection* section, WarheadLayer* old_layer, WarheadLayer* new_layer);
	void sig_model_name_changed();
private:

	ScaleView2D* view_;
	Scene2D* scene_;
	Ui::View2D* ui_;
	WarheadModel* model_;
	WarheadModelWrap* model_wrap_;

	QAction* add_section_action_;
	QAction* delete_section_action_;
	QAction* add_layer_action_;
	QAction* delete_layer_action_;
	QAction* add_end_cap_action_;
	QAction* delete_end_cap_action_;
	QAction* add_fire_point_action_;
	QAction* delete_fire_point_action_;
	QAction* view_property_action_;

	Node current_node_;

	QComboBox* comboBox_radio_;
	bool only_view_;
private:
	void Reset();
	QAction* CreateAction(const QString& text, const QString& icon, const char* slot);

};