//***************************************
//	����ʱ��:	2015:10:29   17:15
//	�ļ�����: 	FileOperation.h
//	�ļ�����:	��Ⱥ��
//	
//	����˵��:	�����ļ�������
//***************************************

#pragma once
#include "targetInfo.h"
#include <string>
#include <list>

class FileOperation
{
public:
	static void ParseModel(const std::string& fileName, TIMP::TargetInfo& targetInfo);
	static void SaveModel(const std::string& fileName, const TIMP::TargetInfo& targetInfo);
private:
	static void ParseLiModel(const std::string& fileName, TIMP::TargetInfo& targetInfo);
	static void ParsePiModel(const std::string& fileName, TIMP::TargetInfo& targetInfo);
	static void ParseVrsModel(const std::string& fileName, TIMP::TargetInfo& targetInfo);
};