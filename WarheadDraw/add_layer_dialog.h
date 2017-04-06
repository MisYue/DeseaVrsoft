#pragma once
#include <QtWidgets>
#include <WarheadModelData/warhead_layer.h>

namespace Ui { class AddLayer; }
class WarheadSection;
class WarheadModelWrap;
class AddLayerDialog : public QDialog
{
	Q_OBJECT
public:
	AddLayerDialog(WarheadModelWrap* model_wrap, WarheadSection* section, WarheadLayer* layer = 0, QWidget* parent = 0);
	virtual ~AddLayerDialog();
	WarheadLayer* get_new_layer() { return new_layer_; }
private slots:
	void on_layer_type_changed(int index);
	void on_layer_pos_changed(bool checked);
	virtual void accept();
protected:
	Ui::AddLayer* ui_;
	WarheadLayer* current_layer_;
	WarheadLayer* new_layer_;
	WarheadSection* section_;
	WarheadModelWrap* model_wrap_;
	QMap<QString, QString> material_guid_2_name_;
	QMap<int, WarheadLayerType> int_2_layer_type_;
	QWidget* CreateShapeParamWidget(WarheadLayerType layer_type);
	QDoubleSpinBox* CreateDoubleSpinBox(double mm_value, QWidget* parent);
	WarheadLayer* GetLayer();
};

class EditLayerDialog : public AddLayerDialog
{
	Q_OBJECT
public:
	EditLayerDialog(WarheadModelWrap* model_wrap, WarheadSection* section, WarheadLayer* layer = 0, QWidget* parent = 0);
	~EditLayerDialog();
	bool IsTypeOrThicknessChanged() const { return is_type_or_thickness_changed_; }
	bool IsTypeChanged() { return is_type_changed_; }
	WarheadLayer* get_new_type_layer() { return new_type_layer_; }
private slots:
	virtual void accept();
protected:
	bool is_type_or_thickness_changed_;
	bool is_type_changed_;
	WarheadLayer* new_type_layer_;
	void UpdateShapeParamWidget();
};