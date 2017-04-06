#pragma once

#include "dbmdata_global.h"
#include <QtCore>

//xml
//csv
//wms




class DBMDATA_EXPORT ExpandType
{
public:
	ExpandType(void);
	ExpandType(const QString& type, const QString& file_name);
	ExpandType(const QString& type, const QByteArray& bytes);

	virtual ~ExpandType(void);


	static void AddType(const QString& type);
	static void RemoveType(const QString& type);
	static QStringList GetTypes();

	bool operator == (const ExpandType& et) const;
protected:
	static QSet<QString> types_;

	QByteArray value_;
	QString type_;
};

Q_DECLARE_METATYPE(ExpandType)

