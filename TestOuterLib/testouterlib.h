#ifndef TESTOUTERLIB_H
#define TESTOUTERLIB_H

#include <QtWidgets/QMainWindow>
#include "ui_testouterlib.h"

class TestOuterLib : public QMainWindow
{
	Q_OBJECT

public:
	TestOuterLib(QWidget *parent = 0);
	~TestOuterLib();

private:
	Ui::TestOuterLibClass ui;
};

#endif // TESTOUTERLIB_H
