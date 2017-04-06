#include "ReadWriteWhd.h"
#include "warheadfilereadwriteengine.h"
#include <WarheadReadWrite/warhead_read.h>
#include <WarheadReadWrite/warhead_write.h>
#include <WarheadDataEntity/warheaddataentity.h>

ReadWriteWhd::ReadWriteWhd(void)
{
}


ReadWriteWhd::~ReadWriteWhd(void)
{
}

// 写入战斗部
bool ReadWriteWhd::Write(const WarheadDataEntityWrap* warhead_wrap, const QString& file_name)
{
	WarheadWrite writer(warhead_wrap->warhead->get_structure());
	return writer.WriteXMLFile(file_name, 0);
}

// 读取战斗部
WarheadDataEntity* ReadWriteWhd::Read(const QString& file_name)
{
	WarheadDataEntity* result = NULL;
	WarheadRead reader;
	WarheadStructure* structure = reader.ReadXMLFile(file_name);
	if(structure)
	{
		result = new WarheadDataEntity(structure);
	}
	return result;
}

// 将战斗部写入QString中
QString ReadWriteWhd::WriteString(const WarheadDataEntityWrap* warhead_wrap)
{
	QString result;
	//先写入文件
	QString file_name(".temp");
	bool ok = Write(warhead_wrap, file_name);
	if(ok)
	{
		QFile file(file_name);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			result = file.readAll();
			file.close();
			QFile::remove(file_name);
		}
	}
	return result;
}

// 从QString中读取战斗部
WarheadDataEntity* ReadWriteWhd::ReadString(const QString& text)
{
	WarheadDataEntity* result = NULL;
	//先写入文件
	QString file_name(".temp");
	QFile file(file_name);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		file.write(text.toStdString().c_str());
		file.close();
		result = Read(file_name);
		QFile::remove(file_name);
	}
	return result;
}