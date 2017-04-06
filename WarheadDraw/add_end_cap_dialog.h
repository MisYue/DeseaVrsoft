#pragma once

#include <QtWidgets>

class WarheadModelWrap;
class WarheadModel;
class WarheadEndCap;
namespace Ui { class  AddEndCap; }
class AddEndCapDialog : public QDialog
{
public:
	AddEndCapDialog(WarheadModelWrap* model_wrap, QWidget* parent = 0);
	~AddEndCapDialog();
	WarheadEndCap* get_new_end_cap() { return new_end_cap_; }
public slots:
	virtual void accept();
protected:
	WarheadModelWrap* model_wrap_;
	WarheadModel* model_;
	Ui::AddEndCap* ui_;
	WarheadEndCap* new_end_cap_;
	QMap<QString, QString> material_guid_2_name_;
};

class EditEndCapDialog : public AddEndCapDialog
{
public:
	EditEndCapDialog(WarheadModelWrap* model_wrap, WarheadEndCap* end_cap, QWidget* parent = 0);
	~EditEndCapDialog();
	bool IsLengthChanged() const { return is_length_changed_; }
public slots:
	virtual void accept();
protected:
	bool is_length_changed_;
	WarheadEndCap* end_cap_;
};