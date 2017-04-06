#pragma once

#include <QtWidgets>
#include <WarheadModelData/warhead_layer.h>

namespace Ui { class AddSection; }
class WarheadSection;
class WarheadModel;
class WarheadModelWrap;
class AddSectionDialog : public QDialog
{
	Q_OBJECT
public:
	AddSectionDialog(WarheadModelWrap* model_wrap, WarheadSection* section = 0, QWidget* parent = 0);
	virtual ~AddSectionDialog();
	WarheadSection* get_new_section() { return new_section_; }
public slots:
	virtual void accept();
private slots:
	void on_shape_type_changed(int index);
	virtual void on_auto_align_changed(bool checked);
	void on_add_pos_changed(bool checked);
protected:
	Ui::AddSection* ui_;
	WarheadSection* current_section_;
	WarheadSection* new_section_;
	QMap<int, ShapeType> int_2_layer_shape_type_;
	QStringList layer_shape_types_;
	WarheadModel* model_;
	WarheadModelWrap* model_wrap_;
	QMap<QString, QString> material_guid_2_name_;
	QWidget* CreateShapeParamWidget(ShapeType shape_type);
	ShapeDescribe* GetShape();
	QDoubleSpinBox* CreateDoubleSpinBox(double mm_value, QWidget* parent, double mm_min = 1);
};


class EditSectionDialog : public AddSectionDialog
{
	Q_OBJECT
public:
	EditSectionDialog(WarheadModelWrap* model_wrap, WarheadSection* section = 0, QWidget* parent = 0);
	virtual ~EditSectionDialog();
	bool IsShapeChanged() const { return is_shape_changed_; }
public slots:
		virtual void accept();
		void on_auto_align_section_changed(bool checked);
		virtual void on_auto_align_changed(bool checked){}
protected:
	bool is_shape_changed_;
	WarheadSection* next_section_;
	WarheadSection* previous_section_;
	QCheckBox* align_next_btn_;
	QCheckBox* align_previous_btn_;
	void UpdateShapeParamWidget(const ShapeDescribe* shape);
};