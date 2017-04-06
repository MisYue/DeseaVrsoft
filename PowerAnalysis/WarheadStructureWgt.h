#pragma once
#include <QtWidgets>

class PowerAnalysisBaseData;
class WarheadDrawWnd;
namespace Ui { class WarheadStructure; }
class WarheadStructureWgt :
	public QWidget
{
public:
	WarheadStructureWgt(PowerAnalysisBaseData* base_data, QWidget* parent=0);
	virtual ~WarheadStructureWgt(void);
protected:
	PowerAnalysisBaseData* base_data_;
	Ui::WarheadStructure* ui_;
	WarheadDrawWnd* draw_wnd_;
};

