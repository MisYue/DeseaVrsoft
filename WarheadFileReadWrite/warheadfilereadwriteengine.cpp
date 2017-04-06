#include "warheadfilereadwriteengine.h"
#include "ReadWriteObjFactor.h"
#include <WarheadDraw/WarheadDrawBase.h>
#include <WarheadDataEntity/warheaddataentity.h>
#include <BasicTool/expandqtcore.h>
#include <BasicTool/EnumMgr.h>

class StaticIniter
{
public:
	StaticIniter()
	{
		EnumMgr& enum_mgr = EnumMgr::instance();
		enum_mgr.AddEnum<WarheadFileReadWriteEngine::Format>(WarheadFileReadWriteEngine::kWhd, ExpandQtCore::fromGBK("whd"));
		enum_mgr.AddEnum<WarheadFileReadWriteEngine::Format>(WarheadFileReadWriteEngine::kPwr, ExpandQtCore::fromGBK("pwr"));
		enum_mgr.AddEnum<WarheadFileReadWriteEngine::Format>(WarheadFileReadWriteEngine::kSvg, ExpandQtCore::fromGBK("svg"));
		enum_mgr.AddEnum<WarheadFileReadWriteEngine::Format>(WarheadFileReadWriteEngine::kStl, ExpandQtCore::fromGBK("stl"));
	}
};

static StaticIniter g_s_inter;

WarheadDataEntityWrap::WarheadDataEntityWrap()
	: warhead(0)
	, painter_2d(0)
	, painter_3d(0)
{
}


WarheadFileReadWriteEngine::WarheadFileReadWriteEngine()
{
}

WarheadFileReadWriteEngine::~WarheadFileReadWriteEngine()
{

}


// 写入战斗部
bool WarheadFileReadWriteEngine::Write(const WarheadDataEntityWrap* warhead_wrap, const QString& file_name)
{
	bool result = false;
	QString format_name = ExpandQtCore::getSuffix(file_name);
	if("svg" == format_name)
	{
		return const_cast<WarheadDrawBase*>(warhead_wrap->painter_2d)->Write(file_name);
	}
	if("stl" == format_name)
	{
		return const_cast<WarheadDrawBase*>(warhead_wrap->painter_3d)->Write(file_name);
	}
	ReadWriteBase* writer = ReadWriteObjFactor::instance().Create(EnumMgr::instance().GetEnumValue<WarheadFileReadWriteEngine::Format>(format_name));
	if(writer)
	{
		result = writer->Write(warhead_wrap, file_name);
		delete writer;
	}
	else
	{
		qWarning() << ExpandQtCore::fromGBK("写入战斗部失败，不支持%1格式").arg(format_name);
	}
	return result;
}

// 读取战斗部
WarheadDataEntity* WarheadFileReadWriteEngine::Read(const QString& file_name)
{
	WarheadDataEntity* result = NULL;
	QString format_name = ExpandQtCore::getSuffix(file_name);
	ReadWriteBase* reader = ReadWriteObjFactor::instance().Create(EnumMgr::instance().GetEnumValue<WarheadFileReadWriteEngine::Format>(format_name));
	if(reader)
	{
		result = reader->Read(file_name);
		delete reader;
	}
	else
	{
		qWarning() << ExpandQtCore::fromGBK("读取战斗部失败，不支持%1格式").arg(format_name);
	}
	return result;
}





// 将战斗部写入QString
QString WarheadFileReadWriteEngine::WriteString(const WarheadDataEntityWrap* warhead_wrap, Format format)
{
	QString result;
	QString format_name = EnumMgr::instance().GetEnumName<WarheadFileReadWriteEngine::Format>(format);
	ReadWriteBase* writer = ReadWriteObjFactor::instance().Create(format);
	if(writer)
	{
		result = writer->WriteString(warhead_wrap);
		delete writer;
	}
	else
	{
		qWarning() << ExpandQtCore::fromGBK("写入战斗部失败，不支持%1格式").arg(format_name);
	}
	return result;
}


// 从QString中读取战斗部
WarheadDataEntity* WarheadFileReadWriteEngine::ReadString(const QString& text, Format format)
{
	WarheadDataEntity* result = NULL;
	QString format_name = EnumMgr::instance().GetEnumName<WarheadFileReadWriteEngine::Format>(format);
	ReadWriteBase* reader = ReadWriteObjFactor::instance().Create(format);
	if(reader)
	{
		result = reader->ReadString(text);
		delete reader;
	}
	else
	{
		qWarning() << ExpandQtCore::fromGBK("读取战斗部失败，不支持%1格式").arg(format_name);
	}
	return result;
}
