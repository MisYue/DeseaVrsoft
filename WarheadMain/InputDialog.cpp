#include "InputDialog.h"
#include <tool/tool.h>

CInputDialog::CInputDialog(void)
{
	QPushButton* ok = new QPushButton(this);
	ok->setText(GBK2Unicode("确定"));
	QPushButton* cancel = new QPushButton(this);
	cancel->setText(GBK2Unicode("取消"));

	QHBoxLayout* h_layout = new QHBoxLayout;
	h_layout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding));
	h_layout->addWidget(ok);
	h_layout->addWidget(cancel);

	connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
	connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

	QVBoxLayout* layout = new QVBoxLayout(this);
	f_layout_ = new QFormLayout;

	layout->addLayout(f_layout_);
	layout->addLayout(h_layout);
	layout->setSpacing(20);

	
}


CInputDialog::~CInputDialog(void)
{
}

int CInputDialog::AddRow(const QString& label, QWidget* widget)
{
	f_layout_->addRow(label, widget);
	int size = int_2_widget_.size();
	int_2_widget_.insert(size, widget);
	return size;
}
QString CInputDialog::GetInput(int row)
{
	QWidget* widget = int_2_widget_.value(row, 0);
	if(widget)
		return GetWidgetValue(widget);
	return QString();
}

void CInputDialog::accept()
{
	foreach(QWidget* widget, int_2_widget_.values())
	{
		if(GetWidgetValue(widget).isEmpty())
		{
			QMessageBox::warning(this, GBK2Unicode("输入检查"), GBK2Unicode("值不能为空"));
			return;
		}
	}
	QDialog::accept();
}

QString CInputDialog::GetWidgetValue(QWidget* widget)
{
	if(QLineEdit* text_inputer = qobject_cast<QLineEdit*>(widget))
	{
		return text_inputer->text();
	}
	else if(QAbstractSpinBox* spin_inputer = qobject_cast<QAbstractSpinBox*>(widget))
	{
		return spin_inputer->text();
	}
	else if(QComboBox* enum_inputer = qobject_cast<QComboBox*>(widget))
	{
		return enum_inputer->currentText();
	}
	return QString();
}
