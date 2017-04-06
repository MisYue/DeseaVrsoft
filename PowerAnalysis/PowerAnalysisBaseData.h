//***************************************
//	����ʱ��:	2017:3:15   16:55
//	�ļ�����: 	PowerAnalysisBaseData.h
//	�ļ�����:	��Ⱥ��
//	
//	����˵��:	�����������������ඨ��
//***************************************

#pragma once
#include "poweranalysis_global.h"
#include <WarheadModelData/WarheadModelWrap.h>
#include <QtCore>

//���������������ݣ���ս�����ṹ�������


class POWERANALYSIS_EXPORT PowerAnalysisBaseData
{
public:
	PowerAnalysisBaseData(const WarheadModelWrap* model_wrap);
	virtual ~PowerAnalysisBaseData(void);
	void set_warhead_wrap(WarheadModelWrap* warhead_wrap);
	const WarheadModelWrap* get_warhead_wrap() const { return model_wrap_; }
	//��ȡ��������
	QString GetData(const QString& key) const;
protected:
	const WarheadModelWrap* model_wrap_;
	const WarheadModel* warhead_;
};

