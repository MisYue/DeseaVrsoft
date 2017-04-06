//***************************************
//	����ʱ��:	2017:3:15   9:20
//	�ļ�����: 	warheadfilereadwriteengine.h
//	�ļ�����:	��Ⱥ��
//	
//	����˵��:	ս�����ļ���д�ඨ�壬д���ʽ��(whd,pwr,svg,stl)����ȡ��ʽ(whd)���μ��ļ���ʽ˵���ĵ�
//***************************************

#ifndef WARHEADFILEREADWRITEENGINE_H
#define WARHEADFILEREADWRITEENGINE_H

#include "warheadfilereadwrite_global.h"
#include <QtCore>

class ReadWriteBase;
class WarheadDataEntity;
class WarheadDrawBase;

struct WARHEADFILEREADWRITE_EXPORT WarheadDataEntityWrap
{
	const WarheadDataEntity* warhead;	//ս����
	const WarheadDrawBase* painter_2d;	//��ά���ƶ���
	const WarheadDrawBase* painter_3d;	//��ά���ƶ���
	QStringList pwr_to_out;	//��Ҫ���������������GUID���б�

	WarheadDataEntityWrap();
};
typedef WarheadDataEntityWrap WarheadReadWriteWrap;

class WARHEADFILEREADWRITE_EXPORT WarheadFileReadWriteEngine
{
public:
	enum Format
	{
		kWhd,	//�ṹ��ʽ
		kPwr,	//������ʽ
		kSvg,	//Svg�ṹ
		kStl,	//Stl�ṹ
	};
	WarheadFileReadWriteEngine();
	~WarheadFileReadWriteEngine();
	// д��ս����
	bool Write(const WarheadDataEntityWrap* warhead_wrap, const QString& file_name);
	// ��ȡս����
	WarheadDataEntity* Read(const QString& file_name);
	// ��ս����д��QString
	QString WriteString(const WarheadDataEntityWrap* warhead_wrap, Format format);
	// ��QString�ж�ȡս����
	WarheadDataEntity* ReadString(const QString& text, Format format);
};

#endif // WARHEADFILEREADWRITEENGINE_H
