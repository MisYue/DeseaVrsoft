#include "SingleWarheadWnd.h"
#include "WarheadPropertyDlg.h"
#include <WarheadDraw/warhead_draw_wnd.h>
#include <WarheadDataEntity/warheaddataentity.h>


SingleWarheadWnd::SingleWarheadWnd(WarheadPropertyWrap* warhead_wrap, QWidget* parent)
	: QMainWindow(parent)
	, warhead_wrap_(warhead_wrap)
	, draw_wnd_(new WarheadDrawWnd(warhead_wrap->warhead->get_structure()))
{
	setCentralWidget(draw_wnd_);
}


SingleWarheadWnd::~SingleWarheadWnd(void)
{
}

void SingleWarheadWnd::closeEvent(QCloseEvent * event)
{
	//CheckAndAskSave();
}
WarheadDrawBase* SingleWarheadWnd::GetPainter2D()
{
	return draw_wnd_->GetPainter2D();
}
WarheadDrawBase* SingleWarheadWnd::GetPainter3D()
{
	return draw_wnd_->GetPainter3D();
}