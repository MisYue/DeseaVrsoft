#include "SelectView.h"


SelectView::SelectView(void)
{
}


SelectView::~SelectView(void)
{
}

//ѡ���¼
Record* SelectView::SelectRecord()
{
	Record* record = 0;

	if(QDialog::Accepted == QDialog::exec())
	{

	}

	return record;
}

int SelectView::exec()
{
	return QDialog::Accepted;
}