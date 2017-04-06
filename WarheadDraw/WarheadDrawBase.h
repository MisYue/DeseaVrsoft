//***************************************
//	����ʱ��:	2017:3:15   10:22
//	�ļ�����: 	WarheadDrawBase.h
//	�ļ�����:	��Ⱥ��
//	
//	����˵��:	ս�������ƻ��ඨ��
//***************************************

#pragma once
#include "warhead_draw_global.h"

class WarheadModel;
class WARHEADDRAW_EXPORT WarheadDrawBase
{
public:
	WarheadDrawBase(void);
	WarheadDrawBase(WarheadModel* warhead);

	virtual ~WarheadDrawBase(void);
	// д���ļ�
	virtual bool Write(const QString& file_name);
	// ����
	virtual void Draw(void);
	// ����ս����
	void set_model(WarheadModel* warhead);

protected:
	// ս����
	WarheadModel* model_;

};

