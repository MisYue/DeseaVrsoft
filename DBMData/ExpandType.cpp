#include "ExpandType.h"


QSet<QString> ExpandType::types_;

ExpandType::ExpandType(void)
{
}
ExpandType::ExpandType(const QString& type, const QString& file_name)
{
	if(types_.contains(type))
	{
		type_ = type;
		QFile file(file_name);
		if(file.open(QFile::ReadOnly))
		{
			value_ = file.readAll();
		}
	}
	else
	{
		qWarning() << "type " << type << " not exist!";
	}
}

ExpandType::ExpandType(const QString& type, const QByteArray& bytes)
{
	if(types_.contains(type))
	{
		type_ = type;
		value_ = bytes;
	}
	else
	{
		qWarning() << "type " << type << " not exist!";
	}
}

ExpandType::~ExpandType(void)
{
}

void ExpandType::AddType(const QString& type)
{
	types_.insert(type);
}
void ExpandType::RemoveType(const QString& type)
{
	types_.remove(type);
}
QStringList ExpandType::GetTypes()
{
	return types_.values();
}

bool ExpandType::operator == (const ExpandType& et) const
{
	return ((type_ == et.type_)&&(value_ == et.value_));
}

