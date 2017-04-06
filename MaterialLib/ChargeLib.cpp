#include "ChargeLib.h"
#include "ChargeMaterial.h"
#include <BasicTool/expandqtcore.h>

ChargeLib::ChargeLib(void)
{
	propertie_names_ << ExpandQtCore::fromGBK("装药号") << ExpandQtCore::fromGBK("单位制-长度") << ExpandQtCore::fromGBK("单位制-质量") 
		<< ExpandQtCore::fromGBK("单位制-时间") << ExpandQtCore::fromGBK("装药名称") << ExpandQtCore::fromGBK("装药密度") 
		<< ExpandQtCore::fromGBK("爆炸爆速") << ExpandQtCore::fromGBK("装药爆热") << ExpandQtCore::fromGBK("装药爆压") 
		<< ExpandQtCore::fromGBK("备注");

}


ChargeLib::~ChargeLib(void)
{
}

// 初始化材料库
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


// 初始化材料库
bool ChargeLib::Init(DBConn* db_conn)
{
	return false;
}

enum { kId, kUL, kUM, kUT, kName, kDensity, kEPV, kEPH, EPP, kCMM, };
// 追加材料
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
	//判断guid是否存在，若存在，不追加
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