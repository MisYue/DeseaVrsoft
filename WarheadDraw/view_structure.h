#pragma once
#include <QtWidgets>

class WarheadSection;
class WarheadLayer;
class WarheadFirePoint;
class WarheadNode;
class WarheadEndCap;
class WarheadModel;
class View2D;

class ViewStructure : public QMainWindow
{
	Q_OBJECT
public:
	ViewStructure(QWidget* parent=0);
	~ViewStructure();
	void set_view_2d(View2D* view_2d);
	void Reset();
public slots:
	void on_add_section(WarheadSection* section);
	void on_delete_section(WarheadSection* section);
	void on_add_layer(WarheadSection* section, WarheadLayer* layer);
	void on_delete_layer(WarheadSection* section, WarheadLayer* layer);
	void on_add_end_cap(WarheadEndCap* end_cap);
	void on_delete_end_cap(WarheadEndCap* end_cap);
	void on_add_fire_point(WarheadFirePoint* fire_point);
	void on_delete_fire_point(WarheadFirePoint* fire_point);
	void on_warhead_node_changed(WarheadNode* node);
	void on_item_clicked(QTreeWidgetItem* item, int column);
	void on_item_changed();
	void on_model_name_changed();
private:
	QTreeWidget* struture_tree_;
	View2D* view_2d_;
private:
	QTreeWidgetItem* AddItem(const QString& text, QTreeWidgetItem* parent = 0);
	QMap<QTreeWidgetItem*, WarheadNode*> item_2_layer_;
	QTreeWidgetItem* coord_item_;
};