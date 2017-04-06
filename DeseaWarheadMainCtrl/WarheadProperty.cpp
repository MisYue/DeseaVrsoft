#include "WarheadProperty.h"
#include "GlobalTool.h"
#include <WarheadModelData/warhead_model.h>
#include <WarheadReadWrite/warhead_write.h>

WarheadProperty::WarheadProperty(void)
	: id_(GlobalTool::instance().GetNewWarheadId())
	, guid_(QUuid::createUuid().toString())
	, share_(true)
	, name_(QString("New Warhead %1").arg(id_))
	, service_start_date_(QDate::currentDate())
	, service_end_date_(QDate::currentDate())
	, create_time_(QDateTime::currentDateTime())
	, update_time_(QDateTime::currentDateTime())
	, structure_(new WarheadModel)
{
}


WarheadProperty::~WarheadProperty(void)
{
}

void WarheadProperty::Structure2Xml()
{
	WarheadWrite writer(structure_);
	QString file_name("./temp");
	writer.WriteXMLFile(file_name, 200);
	QFile file(file_name);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		structure_2d_xml_ = file.readAll();
	}
}
void WarheadProperty::Power2Csv()
{

}

void WarheadProperty::Xml2Structure()
{

}
void WarheadProperty::Csv2Power()
{

}
