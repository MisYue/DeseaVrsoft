#pragma once
#include <QtCore>

class Argument;
class OperatorData;
class QDomElement;
class OperatorEngine
{
public:
	OperatorEngine(const OperatorData* operator_data);
	virtual ~OperatorEngine(void);
	//获取参数树xml格式
	QString get_argu_xml() const { return argu_xml_; }
	//获取结果树xml格式
	QString get_result_xml() const { return result_xml_; }
	//设置参数
	void SetArgumentValue(int id, const QString& val);
	//获取参数
	QString GetArgumentValue(int id) const;
	//计算
	void Count();

protected:
	const OperatorData* operator_data_;
	QString argu_xml_;	//参数树
	QString result_xml_; //结果树
	QMap<int, Argument*> id_2_argu_;
	QString arguments_id_;
	QString arguments_version_;

	typedef void (*StrParamFunc)(char*);
	typedef bool (*IntParamFun)(int&);
	typedef void (*StrAndIntParamFun)(char*, int&);
	typedef void (*NullParamFun)();

	StrParamFunc set_argu_func_;
	IntParamFun init_func_;
	IntParamFun verify_func_;
	IntParamFun run_func_;
	StrAndIntParamFun result_func_;
	NullParamFun release_func_;
	StrAndIntParamFun exception_func_;

	void Init();
	void ParseArgument();
	void ParseArgumentGroup(QDomElement* element);
	void ParseArgument(QDomElement* element);
	void ReportError(const QString& title, int exception_code);
};

