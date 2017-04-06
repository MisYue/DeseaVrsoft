#ifndef TESTPOWERANALYSIS_H
#define TESTPOWERANALYSIS_H

#include <QtWidgets/QMainWindow>
#include "ui_testpoweranalysis.h"

class TestPowerAnalysis : public QMainWindow
{
	Q_OBJECT

public:
	TestPowerAnalysis(QWidget *parent = 0);
	~TestPowerAnalysis();

private:
	Ui::TestPowerAnalysisClass ui;
};

#endif // TESTPOWERANALYSIS_H
