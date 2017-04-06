#pragma once

#include <QtWidgets>

class CInputDialog :
	public QDialog
{
	Q_OBJECT
public:
	CInputDialog(void);
	virtual ~CInputDialog(void);
	//·µ»ØÐÐºÅ
	int AddRow(const QString& label, QWidget* widget);
	QString GetInput(int row);
public slots:	
	virtual void accept();

private:
	QMap<int, QWidget*> int_2_widget_;
	QFormLayout* f_layout_;

	QString GetWidgetValue(QWidget* widget);
};

