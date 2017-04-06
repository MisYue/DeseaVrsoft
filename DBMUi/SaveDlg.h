#pragma once

#include "dbmui_global.h"
#include <QtWidgets>

class DBMUI_EXPORT SaveDlg :
	public QDialog
{
public:
	SaveDlg(const QString& table_name, const QList<QPair<QString, QVariant> >& field_names_and_values);
	virtual ~SaveDlg(void);
};

