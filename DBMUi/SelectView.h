#pragma once

#include "dbmui_global.h"
#include <QtWidgets>

class Record;
class DBMUI_EXPORT SelectView :
	public QDialog
{
public:
	SelectView(void);
	virtual ~SelectView(void);

	//Ñ¡Ôñ¼ÇÂ¼
	Record* SelectRecord();
private:
	int exec();
};

