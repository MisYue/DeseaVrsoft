#pragma once
#include "poweranalysis_global.h"
#include <QtWidgets>

class PowerAnalysis;
class OperatorDictionary;
class PowerAnalysisBaseData;
class WarheadModelWrap;
class TaskConfigWgt;
class FormulaCountWgt;
class ResultProcessWgt;
class WarheadStructureWgt;
namespace Ui { class PowerAnalysis; }
class POWERANALYSIS_EXPORT PowerAnalysisWgt :
	public QDialog
{
	Q_OBJECT
public:
	PowerAnalysisWgt(const QString& procedure_xml_file, const QString& dictionary_xml_file, WarheadModelWrap* warhead_wrap, QWidget* parent=0);
	virtual ~PowerAnalysisWgt(void);
public slots:
	void on_current_tab_changed(int index);
protected:
	OperatorDictionary* operator_dic_;
	PowerAnalysis* power_analysis_;
	PowerAnalysisBaseData* base_data_;
	Ui::PowerAnalysis* ui_;
	TaskConfigWgt* task_wgt_;
	WarheadStructureWgt* structure_wgt_;
	ResultProcessWgt* result_wgt_;
	FormulaCountWgt* formula_wgt_;

	void CreateWarheadStructureTab();
	void CreateTaskConfigTab();
	void CreateFormulaCountTab();
	void CreateResultProcessTab();
};

