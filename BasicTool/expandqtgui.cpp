#include "expandqtgui.h"
#include "expandqtcore.h"

ExpandQtGui::ExpandQtGui()
{

}

ExpandQtGui::~ExpandQtGui()
{

}

void ExpandQtGui::critical(QWidget* parent, const QString& title, const QString& text)
{
	QMessageBox box;
	box.setIcon(QMessageBox::Critical);
	box.addButton(ExpandQtCore::fromGBK("确定"), QMessageBox::AcceptRole);
	box.setText(text);
	box.setWindowTitle(title);
	box.exec();
}
void ExpandQtGui::information(QWidget* parent, const QString& title, const QString& text)
{
	QMessageBox box;
	box.setIcon(QMessageBox::Information);
	box.addButton(ExpandQtCore::fromGBK("确定"), QMessageBox::AcceptRole);
	box.setText(text);
	box.setWindowTitle(title);
	box.exec();
}
void ExpandQtGui::warning(QWidget* parent, const QString& title, const QString& text)
{
	QMessageBox box;
	box.setIcon(QMessageBox::Warning);
	box.addButton(ExpandQtCore::fromGBK("确定"), QMessageBox::AcceptRole);
	box.setText(text);
	box.setWindowTitle(title);
	box.exec();
}

// 创建动作
QAction* ExpandQtGui::createAction(const QString & text, const QObject * receiver, const char* method, QObject * parent, const QString & icon)
{
	QAction* action = new QAction(QIcon(icon), text, parent);
	QObject::connect(action, SIGNAL(triggered()), receiver, method);
	return action;
}
// 创建按钮
QPushButton* createPushButton(const QString & text, const QWidget * receiver, const char* method, QWidget * parent, const QString & icon)
{
	QPushButton* btn = new QPushButton(QIcon(icon), text, parent);
	QObject::connect(btn, SIGNAL(clicked()), receiver, method);
	return btn;
}
// 选择对话框
void ExpandQtGui::selectDlg(const QStringList& items, QStringList& selected, QWidget* parent)
{
	QDialog dlg(parent);
	QVBoxLayout* layout = new QVBoxLayout(&dlg);
	QVBoxLayout* item_layout = new QVBoxLayout;
	layout->addLayout(item_layout);
	QList<QCheckBox*> boxes;
	foreach(const QString& item, items)
	{
		QCheckBox* box = new QCheckBox(item, &dlg);
		boxes.append(box);
		item_layout->addWidget(box);
	}
	QHBoxLayout* btn_layout = new QHBoxLayout;
	layout->addLayout(btn_layout);
	btn_layout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
	QPushButton* ok_btn = new QPushButton(QIcon(), ExpandQtCore::fromGBK("确定"), parent);
	QObject::connect(ok_btn, SIGNAL(clicked()), &dlg, SLOT(accept()));
	QPushButton* cancel_btn = new QPushButton(QIcon(), ExpandQtCore::fromGBK("取消"), parent);
	QObject::connect(cancel_btn, SIGNAL(clicked()), &dlg, SLOT(reject()));
	btn_layout->addWidget(ok_btn);
	btn_layout->addWidget(cancel_btn);

	if(QDialog::Accepted == dlg.exec())
	{
		foreach(QCheckBox* box, boxes)
		{
			if(box->isChecked())
				selected.append(box->text());
		}
	}
}