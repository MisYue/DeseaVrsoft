#ifndef WARHEAD_WRITE_H
#define WARHEAD_WRITE_H

#include "warheadreadwrite_global.h"
#include <QtCore>

class WarheadModelWrap;
class WARHEADREADWRITE_EXPORT WarheadWrite
{
public:
	WarheadWrite(const WarheadModelWrap* model_wrap);
	~WarheadWrite();
	//文件名，装药曲线离散量
	bool WriteXMLFile(const QString& file_name, unsigned curve_descrete_num) const;
	bool WriteCSVFile(const QString& file_name);
private:
	const WarheadModelWrap* model_wrap_;
	
};

#endif // WARHEAD_WRITE_H
