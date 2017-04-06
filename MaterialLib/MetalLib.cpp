#include "MetalLib.h"
#include "MetalMaterial.h"
#include <BasicTool/expandqtcore.h>

MetalLib::MetalLib(void)
{

	propertie_names_ << ExpandQtCore::fromGBK("金属号") << ExpandQtCore::fromGBK("单位制-长度") << ExpandQtCore::fromGBK("单位制-质量") 
		<< ExpandQtCore::fromGBK("单位制-时间") << ExpandQtCore::fromGBK("金属名称") << ExpandQtCore::fromGBK("金属类别") 
		<< ExpandQtCore::fromGBK("密度") << ExpandQtCore::fromGBK("压缩屈服强度") << ExpandQtCore::fromGBK("压缩屈服强度(应变率)") 
		<< ExpandQtCore::fromGBK("拉伸屈服强度") << ExpandQtCore::fromGBK("拉伸屈服强度(应变率)") << ExpandQtCore::fromGBK("压缩极限强度") 
		<< ExpandQtCore::fromGBK("压缩极限强度(应变率)") << ExpandQtCore::fromGBK("拉伸极限强度") << ExpandQtCore::fromGBK("拉伸极限强度(应变率)") 
		<< ExpandQtCore::fromGBK("硬度类型") << ExpandQtCore::fromGBK("硬度值") << ExpandQtCore::fromGBK("拉伸延伸率")
		<< ExpandQtCore::fromGBK("拉伸延伸率(带应变率)") << ExpandQtCore::fromGBK("拉伸断面收缩率") << ExpandQtCore::fromGBK("拉伸断面收缩率(带应变率)")
		<< ExpandQtCore::fromGBK("杨氏模量") << ExpandQtCore::fromGBK("杨氏模量(带应变率)") << ExpandQtCore::fromGBK("拉伸切线模量") 
		<< ExpandQtCore::fromGBK("拉伸切线模量(带应变率)") << ExpandQtCore::fromGBK("压缩模量") << ExpandQtCore::fromGBK("压缩模量(带应变率)") 
		<< ExpandQtCore::fromGBK("压缩切线模量") << ExpandQtCore::fromGBK("压缩切线模量(带应变率)") << ExpandQtCore::fromGBK("泊松比_");
}


MetalLib::~MetalLib(void)
{
}

// 初始化材料库
bool MetalLib::Init(const QString& csv_file)
{
	QFile data(csv_file);
	if(data.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDeleteAll(guid_2_material_.values());
		guid_2_material_.clear();
		guid_2_name_.clear();
		QTextStream stream(data.readAll());
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
bool MetalLib::Init(DBConn* db_conn)
{
	return false;
}

// 追加材料
const Material* MetalLib::Append(const QString& line)
{
	QString _line = line;
	_line.trimmed();
	QStringList values = _line.split(',');
	if(values.size() != 30)
		return 0;
	//判断guid是否存在，若存在，不追加
	if(Material* mtl = guid_2_material_.value(values[0], 0))
		return mtl;
	MetalMaterial* mtl = new MetalMaterial;
	int index = 0;
	Bit_UnitSystem us(values[1].toInt(), values[2].toInt(), values[3].toInt());
	mtl->set_id(values[0]);
	mtl->set_name(values[4]);
	mtl->set_us(us);
	mtl->set_density(values[6].toDouble());
	mtl->SetPropertyValues(values);
	guid_2_material_.insert(values[0], mtl);
	guid_2_name_.insert(values[0], values[4]);
	return mtl;
}
