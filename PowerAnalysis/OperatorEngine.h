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
	//��ȡ������xml��ʽ
	QString get_argu_xml() const { return argu_xml_; }
	//��ȡ�����xml��ʽ
	QString get_result_xml() const { return result_xml_; }
	//���ò���
	void SetArgumentValue(int id, const QString& val);
	//��ȡ����
	QString GetArgumentValue(int id) const;
	//����
	void Count();

protected:
	const OperatorData* operator_data_;
	QString argu_xml_;	//������
	QString result_xml_; //�����
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

