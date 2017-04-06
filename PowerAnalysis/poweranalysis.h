#ifndef POWERANALYSIS_H
#define POWERANALYSIS_H

#include "poweranalysis_global.h"
#include <QtCore>

class OperatorEngine;
//算子数据
struct OperatorData
{
	QString dll;
	QString get_argu;
	QString set_argu;
	QString init;
	QString verify;
	QString run;
	QString result;
	QString release;
	QString exception;
	OperatorEngine* engine;
};

//算子库数据
struct OperatorLib
{
	QString id;
	QString mean;
	QList<OperatorData> operators;	//所有该类算子
};

//计算任务数据
struct CountTaskData
{
	QString mean;
	bool checked;	//任务是否选中
	QString checked_operator;	//选择的算子
	QString operator_lib_id;	//对应算子库
};

//小流程数据
struct SubProcedureData
{
	QString id;
	QString mean;
	QList<CountTaskData> tasks;	//小流程中的任务列表
};

//大流程
struct ProcedureData
{
	QString warhead_type;
	QList<QString> sub_procedure_ids;	//小流程列表
};

class QDomElement;
class POWERANALYSIS_EXPORT PowerAnalysis
{
public:
	PowerAnalysis(const QString& procedure_xml_file);
	~PowerAnalysis();

	//获取大流程
	const ProcedureData* GetProcedure(int warhead_type) const
	{
		return type_2_procedure_.value(warhead_type, 0);
	}
	//获取小流程
	const SubProcedureData* GetSubProcedure(const QString& id) const
	{
		return id_2_sub_procedure_.value(id, 0);
	}
	//获取算子库
	const OperatorLib* GetOperatorLib(const QString& id) const
	{
		return id_2_operator_lib_.value(id, 0);
	}
	//获取任务采用的算子引擎
	const OperatorEngine* GetOperatorEngine(const QString& lib_id, const QString& operator_name) const;

	//类型
	void set_warhead_type(int warhead_type) { warhead_type_ = warhead_type; }
	int get_warhead_type() { return warhead_type_; }
private:
	int warhead_type_;
	QString procedure_xml_file_;	//流程配置xml文件
	QMap<int, ProcedureData*> type_2_procedure_;	//大流程
	QMap<QString, SubProcedureData*> id_2_sub_procedure_; //小流程
	QMap<QString, OperatorLib*> id_2_operator_lib_; //算子库

	//////////////私有成员函数/////////////
	//解析流程文件
	void ParseProcedureFile();
	//解析字典文件
	void ParseDictionaryFile();
	//解析算子参数
	void ParseOperatorParam();
	//解析算子库
	void ParseOperatorLib(QDomElement* element);
	//解析小流程
	void ParseSubProcedure(QDomElement* element);
	//解析大流程
	void ParseProcedure(QDomElement* element);
};

#endif // POWERANALYSIS_H
