#ifndef WARHEADMAIN_H
#define WARHEADMAIN_H

#include <QtWidgets>

class WarheadModel;
class WarheadDrawWnd;
namespace Ui { class WarheadMainClass; }
class WarheadMain : public QMainWindow
{
	Q_OBJECT

public:
	WarheadMain(const QString& model_file = QString(), QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~WarheadMain();
public slots:
	void on_new();
	void on_save();
	void on_save_as();
	void on_open();
	void on_metal_material();
	void on_charge_material();
private:
	Ui::WarheadMainClass* ui;
	WarheadModel* model_;
	WarheadDrawWnd* draw_wnd_;
	QString model_file_;
private:
	void JudgeSave();
	void TryOpenModel(const QString& model_file);
	int GetInputDestreteNum();
	bool SaveSet(int& destrete_num);
	bool SaveCheck();
};

#endif // WARHEADMAIN_H
