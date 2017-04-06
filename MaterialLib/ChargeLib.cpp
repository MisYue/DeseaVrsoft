#include "ChargeLib.h"
#include "ChargeMaterial.h"
#include <BasicTool/expandqtcore.h>

ChargeLib::ChargeLib(void)
{
	propertie_names_ << ExpandQtCore::fromGBK("װҩ��") << ExpandQtCore::fromGBK("��λ��-����") << ExpandQtCore::fromGBK("��λ��-����") 
		<< ExpandQtCore::fromGBK("��λ��-ʱ��") << ExpandQtCore::fromGBK("װҩ����") << ExpandQtCore::fromGBK("װҩ�ܶ�") 
		<< ExpandQtCore::fromGBK("��ը����") << ExpandQtCore::fromGBK("װҩ����") << ExpandQtCore::fromGBK("װҩ��ѹ") 
		<< ExpandQtCore::fromGBK("��ע");

}


ChargeLib::~ChargeLib(void)
{
}

// ��ʼ�����Ͽ�
bool ChargeLib::Init(const QString& csv_file)
{
	QFile data(csv_file);
	if(data.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDeleteAll(guid_2_material_.values());
		guid_2_material_.clear();
		guid_2_name_.clear();
		QTextStream stream(&data);
		QString line = stream.readLine();
		while(!line.isNull())
		{
			Append(line);
			line = stream.readLine();
		}
		return true;
	}
	return false;
}


// ��ʼ�����Ͽ�
bool ChargeLib::Init(DBConn* db_conn)
{
	return false;
}

enum { kId, kUL, kUM, kUT, kName, kDensity, kEPV, kEPH, EPP, kCMM, };
// ׷�Ӳ���
const Material* ChargeLib::Append(const QString& line)
{
	QString _line = line;
	_line.trimmed();
	QStringList values = _line.split(',');
	if(values.size() != 10)
		return 0;

	int unit_length, unit_mass, unit_time;
	double density, explosion_vel, explosion_heat, explosion_pressure;
	QString id, name, comment;

	id = values[kId];
	unit_length = values[kUL].toInt();
	unit_mass = values[kUM].toInt();
	unit_time = values[kUT].toInt();
	name = values[kName];
	comment = values[kCMM];
	density = values[kDensity].toDouble();
	explosion_vel = values[kEPV].toDouble();
	explosion_heat = values[kEPH].toDouble();
	explosion_pressure = values[EPP].toDouble();
	//�ж�guid�Ƿ���ڣ������ڣ���׷��
	if(Material* mtl = guid_2_material_.value(id, 0))
		return mtl;
	ChargeMaterial* mtl = new ChargeMaterial;
	Bit_UnitSystem US(unit_length, unit_mass, unit_time);
	mtl->set_id(id);
	mtl->set_name(name);
	mtl->set_us(US);
	mtl->set_density(density);
	mtl->set_velocity(explosion_vel);
	mtl->set_heat(explosion_heat);
	mtl->set_pressure(explosion_pressure);
	mtl->SetPropertyValues(values);
	guid_2_material_.insert(id, mtl);
	guid_2_name_.insert(id, name);
	return mtl;
}