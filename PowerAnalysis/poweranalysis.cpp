#include "poweranalysis.h"
#include "OperatorEngine.h"
#include <BasicTool/expandqtcore.h>
#include <QtXml>

PowerAnalysis::PowerAnalysis(const QString& procedure_xml_file)
	: procedure_xml_file_(procedure_xml_file)
	, warhead_type_(0)
{
	ParseProcedureFile();
}

PowerAnalysis::~PowerAnalysis()
{
	foreach(OperatorLib* lib, id_2_operator_lib_.values())
	{
		foreach(const OperatorData& optd, lib->operators)
			delete optd.engine;
	}
	qDeleteAll(type_2_procedure_.values());
	qDeleteAll(id_2_operator_lib_.values());
	qDeleteAll(id_2_sub_procedure_.values());
}
//获取任务采用的算子引擎
const OperatorEngine* PowerAnalysis::GetOperatorEngine(const QString& lib_id, const QString& operator_name) const
{
	OperatorLib* lib = id_2_operator_lib_.value(lib_id, 0);
	if(lib)
	{
		foreach(const OperatorData& operator_data, lib->operators)
		{
			if(operator_data.dll == operator_name)
				return operator_data.engine;
		}
	}
	return 0;
}
//解析流程文件
void PowerAnalysis::ParseProcedureFile()
{
	if(procedure_xml_file_.isEmpty())
	{
		qWarning() << ExpandQtCore::fromGBK("未指定威力流程配置文件!");
		return ;
	}
	if(!QFile::exists(procedure_xml_file_))
	{
		qWarning() << ExpandQtCore::fromGBK("威力流程配置文件'%1'不存在!").arg(procedure_xml_file_);
		return ;
	}

	QDomDocument doc;
	QFile file(procedure_xml_file_);
	bool ok = false;
	if (file.open(QIODevice::ReadOnly))
	{
		if (doc.setContent(&file)) 
		{
			ok = true;
		}
	}
	if(!ok)
	{
		qWarning() << ExpandQtCore::fromGBK("打开威力流程配置文件'%1'失败!").arg(procedure_xml_file_);
		return ;
	}
	QDomElement root = doc.documentElement();
	QDomElement element;
	element = root.firstChildElement("SubProcedures");
	if(!element.isNull())
		ParseSubProcedure(&element);
	element = root.firstChildElement("OperatorLib");
	if(!element.isNull())
		ParseOperatorLib(&element);
	for(QDomElement child = root.firstChildElement("WarheadProcedure"); !child.isNull(); child = child.nextSiblingElement("WarheadProcedure"))
	{
		ParseProcedure(&child);
	}
}

//解析算子库
void PowerAnalysis::ParseOperatorLib(QDomElement* element)
{
	Q_ASSERT(element);
	for(QDomElement child = element->firstChildElement(); !child.isNull(); child = child.nextSiblingElement())
	{
		QString id = child.attribute("id");
		QString mean = child.attribute("mean");
		OperatorLib* lib = new OperatorLib;
		lib->id = id;
		lib->mean = mean;
		for(QDomElement opt_elem = child.firstChildElement(); !opt_elem.isNull(); opt_elem = opt_elem.nextSiblingElement())
		{
			lib->operators.push_back(OperatorData());
			OperatorData& optor = lib->operators.back();
			optor.dll = opt_elem.attribute("dll");
			optor.get_argu = opt_elem.firstChildElement("GetArgumentsEx").attribute("name");
			optor.set_argu = opt_elem.firstChildElement("SetArgumentsEx").attribute("name");
			optor.init = opt_elem.firstChildElement("InitEnginEx").attribute("name");
			optor.verify = opt_elem.firstChildElement("VerifyArgumentsEx").attribute("name");
			optor.run = opt_elem.firstChildElement("RunEx").attribute("name");
			optor.result = opt_elem.firstChildElement("GetResultEx").attribute("name");
			optor.release = opt_elem.firstChildElement("ReleaseEx").attribute("name");
			optor.exception = opt_elem.firstChildElement("ExceptionInfoEx").attribute("name");
			optor.engine = new OperatorEngine(&optor);
		}
		id_2_operator_lib_.insert(id, lib);
	}
}
//解析小流程
void PowerAnalysis::ParseSubProcedure(QDomElement* element)
{
	Q_ASSERT(element);
	for(QDomElement child = element->firstChildElement(); !child.isNull(); child = child.nextSiblingElement())
	{
		QString id = child.attribute("id");
		QString mean = child.attribute("mean");
		SubProcedureData* sub_procedure = new SubProcedureData;
		sub_procedure->id = id;
		sub_procedure->mean = mean;
		QDomElement tasks_elem = child.firstChildElement("CountTasks");
		if(tasks_elem.isNull())
			break;
		for(QDomElement task_elem = tasks_elem.firstChildElement(); !task_elem.isNull(); task_elem = task_elem.nextSiblingElement())
		{
			QString mean = task_elem.attribute("mean");
			QString operator_lib_id = task_elem.attribute("operators");
			CountTaskData task;
			task.mean = mean;
			task.operator_lib_id = operator_lib_id;
			task.checked = false;
			sub_procedure->tasks.push_back(task);
		}
		id_2_sub_procedure_.insert(id, sub_procedure);
	}
}
//解析大流程
void PowerAnalysis::ParseProcedure(QDomElement* element)
{
	Q_ASSERT(element);
	int warhead_type = element->attribute("warhead_type", "-1").toInt();
	if(-1 == warhead_type)
		return ;
	ProcedureData* procedure = new ProcedureData;
	procedure->warhead_type = warhead_type;
	for(QDomElement child = element->firstChildElement(); !child.isNull(); child = child.nextSiblingElement())
	{
		QString id = child.attribute("id");
		procedure->sub_procedure_ids.push_back(id);
	}
	type_2_procedure_.insert(warhead_type, procedure);
}