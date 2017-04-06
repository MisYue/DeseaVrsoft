//#pragma once
/********************************************************************
created:	2016/06/8
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	CSV�ļ���ز���

*********************************************************************/
// ��̬�⵼��
#include "Bit_FileExtend_Global.h"
// װҩ����
#include "BITMaterialDataBase/Bit_ChargeAllData.h"
// ��������ϵ������
#include "BITWPCDS/Bit_WPCCData.h"
// ����ת��
#include "BITTransformSupport/Bit_TypeTransform.h"
//
#include "Bit_MatrixString.h"
//mapͷ�ļ�
#include <map>
//Vector
#include <vector>


#ifndef BITCSVFiLE_H__
#define BITCSVFiLE_H__

class BITFILEEXTEND_API Bit_CSVFile
{
public:
	Bit_CSVFile(void);
	~Bit_CSVFile(void);

	////�����ļ������ά������
	bool inputDateBase( const string& filepath , Bit_MatrixString MatrixString);
	//�����ļ��õ�����
	int GetColumnNumber( const string& Filepath )const;
	//�����ļ��õ�����
	int GetRowNumber( const string& Filepath )const;

	//�����ļ��õ�ĳһ����
	string GetCellString( const string &Filepath , const int &Row , const int &Column ) const;

	//*******�ļ�ѹ��*********
	//����װҩ����(1��)
	bool InputChargeDate( const string& Filepath , Bit_ChargeAllData *CAD )const;

	//����ս������������ϵ������(1��)
	bool InputWarheadPCCData( const string& Filepath , Bit_WPCCData *GCD )const;

private:

	
};
#endif
