//***************************************
//	创建时间:	2017:3:14   14:07
//	文件名称: 	SingleWarheadWnd.h
//	文件作者:	岳群磊
//	
//	功能说明:	单个战斗部建模及威力分析界面类定义
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
	//检查及询问是否保存
	//void CheckAndAskSave();
	WarheadDrawWnd* draw_wnd_;
};

