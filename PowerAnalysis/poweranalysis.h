#ifndef POWERANALYSIS_H
#define POWERANALYSIS_H

#include "poweranalysis_global.h"
#include <QtCore>

class OperatorEngine;
//��������
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

//���ӿ�����
struct OperatorLib
{
	QString id;
	QString mean;
	QList<OperatorData> operators;	//���и�������
};

//������������
struct CountTaskData
{
	QString mean;
	bool checked;	//�����Ƿ�ѡ��
	QString checked_operator;	//ѡ�������
	QString operator_lib_id;	//��Ӧ���ӿ�
};

//С��������
struct SubProcedureData
{
	QString id;
	QString mean;
	QList<CountTaskData> tasks;	//С�����е������б�
};

//������
struct ProcedureData
{
	QString warhead_type;
	QList<QString> sub_procedure_ids;	//С�����б�
};

class QDomElement;
class POWERANALYSIS_EXPORT PowerAnalysis
{
public:
	PowerAnalysis(const QString& procedure_xml_file);
	~PowerAnalysis();

	//��ȡ������
	const ProcedureData* GetProcedure(int warhead_type) const
	{
		return type_2_procedure_.value(warhead_type, 0);
	}
	//��ȡС����
	const SubProcedureData* GetSubProcedure(const QString& id) const
	{
		return id_2_sub_procedure_.value(id, 0);
	}
	//��ȡ���ӿ�
	const OperatorLib* GetOperatorLib(const QString& id) const
	{
		return id_2_operator_lib_.value(id, 0);
	}
	//��ȡ������õ���������
	const OperatorEngine* GetOperatorEngine(const QString& lib_id, const QString& operator_name) const;

	//����
	void set_warhead_type(int warhead_type) { warhead_type_ = warhead_type; }
	int get_warhead_type() { return warhead_type_; }
private:
	int warhead_type_;
	QString procedure_xml_file_;	//��������xml�ļ�
	QMap<int, ProcedureData*> type_2_procedure_;	//������
	QMap<QString, SubProcedureData*> id_2_sub_procedure_; //С����
	QMap<QString, OperatorLib*> id_2_operator_lib_; //���ӿ�

	//////////////˽�г�Ա����/////////////
	//���������ļ�
	void ParseProcedureFile();
	//�����ֵ��ļ�
	void ParseDictionaryFile();
	//�������Ӳ���
	void ParseOperatorParam();
	//�������ӿ�
	void ParseOperatorLib(QDomElement* element);
	//����С����
	void ParseSubProcedure(QDomElement* element);
	//����������
	void ParseProcedure(QDomElement* element);
};

#endif // POWERANALYSIS_H
