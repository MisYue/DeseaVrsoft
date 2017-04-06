#pragma once

#include <QtWidgets>

class Bit_2DCSWithExpAndUS;
namespace Ui { class EditCS; }
class WarheadModelWrap;
class EditCSDialog : public QDialog
{
	Q_OBJECT
public:
	EditCSDialog(WarheadModelWrap* model_wrap, QWidget* parent=0);
	~EditCSDialog();
private slots:
	virtual void accept();
protected:
	WarheadModelWrap* model_wrap_;
	Bit_2DCSWithExpAndUS* cs_;
	Ui::EditCS* ui_;
};