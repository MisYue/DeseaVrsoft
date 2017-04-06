#include "WarheadStructureWgt.h"
#include "ui_warheadstructure.h"
#include "PowerAnalysisBaseData.h"
#include <WarheadDraw/warhead_draw_wnd.h>
#include <BasicTool/expandqtcore.h>


WarheadStructureWgt::WarheadStructureWgt(PowerAnalysisBaseData* base_data, QWidget* parent)
	: QWidget(parent)
	, base_data_(base_data)
	, ui_(new Ui::WarheadStructure)
	, draw_wnd_(new WarheadDrawWnd(const_cast<WarheadModelWrap*>(base_data_->get_warhead_wrap()), WarheadDrawWnd::kView, this))
{
	ui_->setupUi(this);
	QVBoxLayout* layout = new QVBoxLayout(ui_->widget);
	layout->addWidget(draw_wnd_);

}


WarheadStructureWgt::~WarheadStructureWgt(void)
{
	delete ui_;
}

