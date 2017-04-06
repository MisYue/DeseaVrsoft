#include "Config.h"
#include "expandqtcore.h"

Config::Config(void)
{
}


Config::~Config(void)
{
}


Config::Config(const QString& file_name)
	: file_name_(file_name)
{
	ReadConfig();
}


// 设置配置文件
void Config::SetConfigFile(const QString& file_name)
{
	file_name_ = file_name;
	ReadConfig();
}


// 保存配置
bool Config::SaveConfig(void)
{
	return false;
}


// 获取数据
QString Config::GetConfigData(const QString& key) const
{
	return key_2_data_.value(key);
}


// 设置数据
void Config::SetConfigData(const QString& key, const QString& data)
{
	key_2_data_[key] = data;
}


// 读取配置
void Config::ReadConfig(void)
{
	QFile file(file_name_);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return ;
		//file.setFileName(":/root/data");
		//bool ok = file.open(QIODevice::ReadOnly | QIODevice::Text);
		//Q_ASSERT(ok);
	}

	key_2_data_.clear();
	while (!file.atEnd()) {
		QByteArray line = file.readLine();
		ParserLine(line);
	}
}


// 解析行
void Config::ParserLine(const QByteArray& line)
{
	QString strs = ExpandQtCore::fromGBK(const_cast<char*>(line.data()));
	if(strs.left(2) == QString("//"))
		return ;
	int index_1 = strs.indexOf('[');
	int index_2 = strs.indexOf(']');
	if(index_1 != -1 && index_2 != -1)
	{
		QString key = strs.mid(index_1+1, index_2-index_1-1);
		QString data = strs.right(strs.size()-index_2-1);
		key_2_data_.insert(key, data);
	}
}
