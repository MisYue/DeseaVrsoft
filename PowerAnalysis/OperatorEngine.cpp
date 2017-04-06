#include "OperatorEngine.h"
#include "poweranalysis.h"
#include <QtXml>
#include <BasicTool/expandqtgui.h>
#include <BasicTool/expandqtcore.h>


//将单位制信息单独保存
//QMap<TypeKey, QMap<ValKey, Val> >

const int BufMaxSize = 1024*1000;

struct Argument
{
	int id;
	QString type;
	QString des;
	QString version;
	QString val;
};
OperatorEngine::OperatorEngine(const OperatorData* operator_data)
	: operator_data_(operator_data)
{
	Q_ASSERT(operator_data_);
	Init();
}
OperatorEngine::~OperatorEngine(void)
{
	qDeleteAll(id_2_argu_.values());
	release_func_();
}
//设置参数
void OperatorEngine::SetArgumentValue(int id, const QString& val)
{
	Argument* argu = id_2_argu_.value(id, 0);
	if(argu)
		argu->val = val;
}
//获取参数
QString OperatorEngine::GetArgumentValue(int id) const
{
	Argument* argu = id_2_argu_.value(id, 0);
	if(argu)
		return argu->val;
	return QString();
}
//计算
void OperatorEngine::Count()
{
	QDomDocument doc("arguments");
	QDomElement root = doc.createElement("arguments");
	doc.appendChild(root);
	root.setAttribute("version", arguments_version_);
	root.setAttribute("id", arguments_id_);
	foreach(const Argument* argu, id_2_argu_.values())
	{
		QDomElement argu_element = doc.createElement("argument");
		argu_element.setAttribute("version", argu->version);
		argu_element.setAttribute("id", argu->id);
		argu_element.setAttribute("type", argu->type);
		argu_element.setAttribute("val", argu->val);
		argu_element.setAttribute("des", argu->des);
		root.appendChild(argu_element);
	}
	QString set_argu_xml = doc.toString(2);
	//设置参数
	set_argu_func_(const_cast<char*>(set_argu_xml.toStdString().c_str()));
	//初始化
	int exception_code = 0;
	bool ok = init_func_(exception_code);
	if(!ok)
	{
		ReportError(ExpandQtCore::fromGBK("初始化算子异常"), exception_code);
		return;
	}
	ok = verify_func_(exception_code);
	if(!ok)
	{
		ReportError(ExpandQtCore::fromGBK("检查算子参数异常"), exception_code);
		return;
	}
	ok = run_func_(exception_code);
	//if(!ok)
	//{
	//	ReportError(ExpandQtCore::fromGBK("算子计算异常"), exception_code);
	//	return;
	//}
	char* buf = new char[BufMaxSize];
	memset(buf, 0, BufMaxSize);
	result_func_(buf, exception_code);
	result_xml_ = buf;
	delete buf;
}
void OperatorEngine::ReportError(const QString& title, int exception_code)
{
	char* buf = new char[BufMaxSize];
	memset(buf, 0, BufMaxSize);
	exception_func_(buf, exception_code);
	ExpandQtGui::critical(0, title, buf);
	delete buf;
}
void OperatorEngine::Init()
{
	QString dll = operator_data_->dll;
	Q_ASSERT(!dll.isEmpty());
#ifdef _DEBUG
	dll += 'd';
#endif
	//运行时，加载算子库
	QLibrary lib(dll);
	//算子参数树
	QString get_argu_name = operator_data_->get_argu;
	if(get_argu_name.right(4) == ".xml")
	{
		QString file_name = get_argu_name;
		Q_ASSERT(QFile::exists(file_name));
		QFile file(file_name);
		bool ok = file.open(QIODevice::ReadOnly);
		Q_ASSERT(ok);
		argu_xml_ = file.readAll();
		file.close();
	}
	else
	{
		StrParamFunc get_argu_func = (StrParamFunc) lib.resolve(get_argu_name.toStdString().c_str());
		Q_ASSERT(get_argu_func);
		char* buf = new char[BufMaxSize];
		memset(buf, 0, BufMaxSize);
		get_argu_func(buf);
		argu_xml_ = buf;
		delete buf;
	}
	set_argu_func_ = (StrParamFunc) lib.resolve(operator_data_->set_argu.toStdString().c_str());
	Q_ASSERT(set_argu_func_);
	init_func_ = (IntParamFun)lib.resolve(operator_data_->init.toStdString().c_str());
	Q_ASSERT(init_func_);
	verify_func_ = (IntParamFun)lib.resolve(operator_data_->verify.toStdString().c_str());
	Q_ASSERT(verify_func_);	
	run_func_ = (IntParamFun)lib.resolve(operator_data_->run.toStdString().c_str());
	Q_ASSERT(run_func_);
	result_func_ = (StrAndIntParamFun)lib.resolve(operator_data_->result.toStdString().c_str());
	Q_ASSERT(result_func_);	
	release_func_ = (NullParamFun)lib.resolve(operator_data_->release.toStdString().c_str());
	Q_ASSERT(release_func_);
	exception_func_ = (StrAndIntParamFun)lib.resolve(operator_data_->exception.toStdString().c_str());
	Q_ASSERT(exception_func_);

	ParseArgument();
}
void OperatorEngine::ParseArgument()
{
	QDomDocument doc;
	bool ok = doc.setContent(argu_xml_);
	Q_ASSERT(ok);
	QDomElement root = doc.documentElement();
	arguments_id_ = root.attribute("id");
	arguments_version_ = root.attribute("version");

	for(QDomElement child = root.firstChildElement(); !child.isNull(); child = child.nextSiblingElement())
	{
		if(child.tagName() == "argumentgroup")
			ParseArgumentGroup(&child);
		else if(child.tagName() == "argument")
			ParseArgument(&child);
	}
}
void OperatorEngine::ParseArgumentGroup(QDomElement* element)
{
	Q_ASSERT(element);
	for(QDomElement child = element->firstChildElement(); !child.isNull(); child = child.nextSiblingElement())
		ParseArgument(&child);
}
void OperatorEngine::ParseArgument(QDomElement* element)
{
	Q_ASSERT(element);
	Argument* argu = new Argument;
	int id = element->attribute("id").toInt();
	id_2_argu_.insert(id, argu);
	argu->id = id;
	argu->version = element->attribute("version");
	argu->des = element->attribute("des");
	argu->type = element->attribute("type");
	argu->val = element->attribute("default");
}
