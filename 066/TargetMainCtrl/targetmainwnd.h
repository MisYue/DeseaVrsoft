#ifndef TARGETMAINWND_H
#define TARGETMAINWND_H

#include <QtWidgets>
namespace Ui { class TargetMainWndClass; }
class TargetMainWnd : public QMainWindow
{
	Q_OBJECT

public:
	TargetMainWnd(QWidget *parent = 0);
	~TargetMainWnd();

private:
	Ui::TargetMainWndClass* ui;
};

#endif // TARGETMAINWND_H
