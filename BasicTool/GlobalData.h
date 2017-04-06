#pragma once
#include "config.h"

class BASICTOOL_EXPORT GlobalData :
	public Config
{
public:
	static GlobalData& instance()
	{
		static GlobalData s_instance;
		return s_instance;
	}
	virtual ~GlobalData(void);
private:
	GlobalData(void);
};

