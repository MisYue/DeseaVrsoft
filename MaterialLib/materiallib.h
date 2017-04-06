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
	// 初始化材料库
	virtual bool Init(const QString& csv_file);
	// 初始化材料库
	virtual bool Init(DBConn* db_conn);
	// 获取所有材料GUID和名称
	QMap<QString, QString> GetAllGuidAndNames(void) ;
	// 获取属性名称列表
	QStringList GetPropertyNames() const { return propertie_names_; }
	// 追加材料
	virtual const Material* Append(const QString& line) { return 0; }
	// 获取材料
	const Material* GetMaterial(const QString& guid) const { return guid_2_material_.value(guid); }
protected:
	// 材料GUID和对象
	QMap<QString, Material*> guid_2_material_;
	// 材料GUID和名称
	QMap<QString, QString> guid_2_name_;
	// 属性名称列表
	QStringList propertie_names_;	
};

#endif // MATERIALLIB_H
