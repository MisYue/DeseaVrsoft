//***************************************
//	����ʱ��:	2017:3:14   14:07
//	�ļ�����: 	SingleWarheadWnd.h
//	�ļ�����:	��Ⱥ��
//	
//	����˵��:	����ս������ģ���������������ඨ��
//***************************************

#pragma once
#include <QtWidgets>

struct WarheadPropertyWrap;
class WarheadDrawWnd;
class WarheadDrawBase;
class SingleWarheadWnd :
	public QMainWindow
{
	Q_OBJECT
public:
	SingleWarheadWnd(WarheadPropertyWrap* warhead_wrap, QWidget* parent=0);
	virtual ~SingleWarheadWnd(void);
	WarheadPropertyWrap* get_warhead_wrap() { return warhead_wrap_; }
	WarheadDrawBase* GetPainter2D();
	WarheadDrawBase* GetPainter3D();

protected:
	void closeEvent(QCloseEvent * event);
protected:
	WarheadPropertyWrap* warhead_wrap_;
	//��鼰ѯ���Ƿ񱣴�
	//void CheckAndAskSave();
	WarheadDrawWnd* draw_wnd_;
};

