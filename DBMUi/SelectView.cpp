#include "SelectView.h"


SelectView::SelectView(void)
{
}


SelectView::~SelectView(void)
{
}

//Ñ¡Ôñ¼ÇÂ¼
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