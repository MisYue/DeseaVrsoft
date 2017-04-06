#pragma once

#include <QtWidgets>

class WarheadModel;
namespace Ui { class ModelProperty; }
class WarheadModelWrap;
class ModelPropertyDialog : public QDialog
{
	Q_OBJECT
public:
	ModelPropertyDialog(WarheadModelWrap* model_wrap, QWidget* parent = 0);
	~ModelPropertyDialog();
	bool IsNameChanged() const { return is_name_changed_; }
public slots:
	virtual void accept();
protected:
	WarheadModel* model_;
	WarheadModelWrap* model_wrap_;
	Ui::ModelProperty* ui_;
	bool is_name_changed_;
};