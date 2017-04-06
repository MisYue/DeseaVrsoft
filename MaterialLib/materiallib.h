#ifndef MATERIALLIB_H
#define MATERIALLIB_H

#include <MaterialLib/materiallib_global.h>
#include <MaterialLib/MetalMaterial.h>
#include <MaterialLib/ChargeMaterial.h>
#include <QtCore>

class DBConn;
class MATERIALLIB_EXPORT MaterialLib
{
public:
	MaterialLib();
	~MaterialLib();
	// ��ʼ�����Ͽ�
	virtual bool Init(const QString& csv_file);
	// ��ʼ�����Ͽ�
	virtual bool Init(DBConn* db_conn);
	// ��ȡ���в���GUID������
	QMap<QString, QString> GetAllGuidAndNames(void) ;
	// ��ȡ���������б�
	QStringList GetPropertyNames() const { return propertie_names_; }
	// ׷�Ӳ���
	virtual const Material* Append(const QString& line) { return 0; }
	// ��ȡ����
	const Material* GetMaterial(const QString& guid) const { return guid_2_material_.value(guid); }
protected:
	// ����GUID�Ͷ���
	QMap<QString, Material*> guid_2_material_;
	// ����GUID������
	QMap<QString, QString> guid_2_name_;
	// ���������б�
	QStringList propertie_names_;	
};

#endif // MATERIALLIB_H
