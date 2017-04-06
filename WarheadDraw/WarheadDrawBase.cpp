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


// д���ļ�
bool WarheadDrawBase::Write(const QString& file_name)
{
	return false;
}


// ����
void WarheadDrawBase::Draw(void)
{
}



// ����ս����
void WarheadDrawBase::set_model(WarheadModel* warhead)
{
	model_ = warhead;
	Draw();
}


