#pragma once

#include <QtWidgets>

class WarheadModel;
class WarheadFirePoint;
namespace Ui { class  EditFirePoint; }
class WarheadModelWrap;
class EditFirePointDialog : public QDialog
{
public:
	EditFirePointDialog(WarheadModelWrap* model_wrap, WarheadFirePoint* fire_point, QWidget* parent = 0);
	~EditFirePointDialog();
	bool IsPosChanged() const { return is_pos_changed_; }
public slots:
	virtual void accept();
protected:
	Ui::EditFirePoint* ui_;
	WarheadFirePoint* fire_point_;
	bool is_pos_changed_;
	WarheadModelWrap* model_wrap_;

};

class AddFirePointDialog : public QDialog
{
public:
	AddFirePointDialog(WarheadModelWrap* model_wrap, QWidget* parent = 0);
	~AddFirePointDialog();
	WarheadFirePoint* get_new_fire_point() { return fire_point_; }
public slots:
	virtual void accept();
protected:
	Ui::EditFirePoint* ui_;
	WarheadFirePoint* fire_point_;
	WarheadModel* model_;
	WarheadModelWrap* model_wrap_;
};
