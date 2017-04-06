//#pragma once
/********************************************************************
created:	2016/06/8
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	CSV文件相关操作

*********************************************************************/
// 动态库导出
#include "Bit_FileExtend_Global.h"
// 装药数据
#include "BITMaterialDataBase/Bit_ChargeAllData.h"
// 威力计算系数数据
#include "BITWPCDS/Bit_WPCCData.h"
// 类型转换
#include "BITTransformSupport/Bit_TypeTransform.h"
//
#include "Bit_MatrixString.h"
//map头文件
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

	////读入文件放入二维矩阵中
	bool inputDateBase( const string& filepath , Bit_MatrixString MatrixString);
	//读入文件得到列数
	int GetColumnNumber( const string& Filepath )const;
	//读入文件得到行数
	int GetRowNumber( const string& Filepath )const;

	//读入文件得到某一个数
	string GetCellString( const string &Filepath , const int &Row , const int &Column ) const;

	//*******文件压入*********
	//读入装药数据(1行)
	bool InputChargeDate( const string& Filepath , Bit_ChargeAllData *CAD )const;

	//读入战斗部威力计算系数数据(1行)
	bool InputWarheadPCCData( const string& Filepath , Bit_WPCCData *GCD )const;

private:

	
};
#endif
