#ifndef VRDA066_H
#define VRDA066_H

#include <QtWidgets/QMainWindow>
#include "ui_vrda066.h"

class VRDA066 : public QMainWindow
{
	Q_OBJECT

public:
	VRDA066(QWidget *parent = 0);
	~VRDA066();

private:
	Ui::VRDA066Class ui;
};

#endif // VRDA066_H
