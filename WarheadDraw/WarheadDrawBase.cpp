#include "WarheadDrawBase.h"


WarheadDrawBase::WarheadDrawBase(void)
	: model_(NULL)
{
}

WarheadDrawBase::WarheadDrawBase(WarheadModel* warhead)
	: model_(warhead)
{
}

WarheadDrawBase::~WarheadDrawBase(void)
{
}


// 写入文件
bool WarheadDrawBase::Write(const QString& file_name)
{
	return false;
}


// 绘制
void WarheadDrawBase::Draw(void)
{
}



// 设置战斗部
void WarheadDrawBase::set_model(WarheadModel* warhead)
{
	model_ = warhead;
	Draw();
}


