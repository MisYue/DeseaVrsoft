#pragma once

#include "dbmdata_global.h"
#include <QtCore>

class Field;
class Record;
class DBMDATA_EXPORT Table
{
public:
	Table(void);
	virtual ~Table(void);


protected:
	QMap<QString, Field*> fields_;
	QString guid_;
};

