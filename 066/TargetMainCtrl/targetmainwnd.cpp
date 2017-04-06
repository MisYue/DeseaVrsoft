#include "targetmainwnd.h"
#include "ui_targetmainwnd.h"

TargetMainWnd::TargetMainWnd(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::TargetMainWndClass)
{
	ui->setupUi(this);
}

TargetMainWnd::~TargetMainWnd()
{
	delete ui;
}
