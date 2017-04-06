#include "MetalLib.h"
#include "MetalMaterial.h"
#include <BasicTool/expandqtcore.h>

MetalLib::MetalLib(void)
{

	propertie_names_ << ExpandQtCore::fromGBK("������") << ExpandQtCore::fromGBK("��λ��-����") << ExpandQtCore::fromGBK("��λ��-����") 
		<< ExpandQtCore::fromGBK("��λ��-ʱ��") << ExpandQtCore::fromGBK("��������") << ExpandQtCore::fromGBK("�������") 
		<< ExpandQtCore::fromGBK("�ܶ�") << ExpandQtCore::fromGBK("ѹ������ǿ��") << ExpandQtCore::fromGBK("ѹ������ǿ��(Ӧ����)") 
		<< ExpandQtCore::fromGBK("��������ǿ��") << ExpandQtCore::fromGBK("��������ǿ��(Ӧ����)") << ExpandQtCore::fromGBK("ѹ������ǿ��") 
		<< ExpandQtCore::fromGBK("ѹ������ǿ��(Ӧ����)") << ExpandQtCore::fromGBK("���켫��ǿ��") << ExpandQtCore::fromGBK("���켫��ǿ��(Ӧ����)") 
		<< ExpandQtCore::fromGBK("Ӳ������") << ExpandQtCore::fromGBK("Ӳ��ֵ") << ExpandQtCore::fromGBK("����������")
		<< ExpandQtCore::fromGBK("����������(��Ӧ����)") << ExpandQtCore::fromGBK("�������������") << ExpandQtCore::fromGBK("�������������(��Ӧ����)")
		<< ExpandQtCore::fromGBK("����ģ��") << ExpandQtCore::fromGBK("����ģ��(��Ӧ����)") << ExpandQtCore::fromGBK("��������ģ��") 
		<< ExpandQtCore::fromGBK("��������ģ��(��Ӧ����)") << ExpandQtCore::fromGBK("ѹ��ģ��") << ExpandQtCore::fromGBK("ѹ��ģ��(��Ӧ����)") 
		<< ExpandQtCore::fromGBK("ѹ������ģ��") << ExpandQtCore::fromGBK("ѹ������ģ��(��Ӧ����)") << ExpandQtCore::fromGBK("���ɱ�_");
}


MetalLib::~MetalLib(void)
{
}

// ��ʼ�����Ͽ�
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


// ��ʼ�����Ͽ�
bool MetalLib::Init(DBConn* db_conn)
{
	return false;
}

// ׷�Ӳ���
const Material* MetalLib::Append(const QString& line)
{
	QString _line = line;
	_line.trimmed();
	QStringList values = _line.split(',');
	if(values.size() != 30)
		return 0;
	//�ж�guid�Ƿ���ڣ������ڣ���׷��
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
