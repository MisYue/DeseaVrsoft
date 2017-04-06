#include "PowerAnalysisWgt.h"
#include "OperatorDictionary.h"
#include "poweranalysis.h"
#include "ui_PowerAnalysisWgt.h"
#include "TaskConfigWgt.h"
#include "FormulaCountWgt.h"
#include "PowerAnalysisBaseData.h"
#include "ResultProcessWgt.h"
#include "WarheadStructureWgt.h"
#include <BasicTool/expandqtcore.h>
#include <WarheadModelData/WarheadModelWrap.h>

PowerAnalysisWgt::PowerAnalysisWgt(const QString& procedure_xml_file, const QString& dictionary_xml_file, WarheadModelWrap* warhead_wrap, QWidget* parent)
	: QDialog(parent)
	, power_analysis_(new PowerAnalysis(procedure_xml_file))
	, operator_dic_(new OperatorDictionary(dictionary_xml_file))
	, ui_(new Ui::PowerAnalysis)
	, base_data_(new PowerAnalysisBaseData(warhead_wrap))
{
	ui_->setupUi(this);
	ui_->tabWidget->setCurrentIndex(0);
	power_analysis_->set_warhead_type(warhead_wrap->get_structure()->get_type());
	CreateWarheadStructureTab();
	CreateTaskConfigTab();
	CreateFormulaCountTab();
	CreateResultProcessTab();
	connect(ui_->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(on_current_tab_changed(int)));
	connect(task_wgt_, SIGNAL(sig_config_changed()), formula_wgt_, SLOT(on_update_ui()));
	connect(formula_wgt_, SIGNAL(sig_result_changed()), result_wgt_, SLOT(on_update_ui()));
}

PowerAnalysisWgt::~PowerAnalysisWgt(void)
{
	delete ui_;
}
void PowerAnalysisWgt::CreateWarheadStructureTab()
{
	structure_wgt_ = new WarheadStructureWgt(base_data_);
	QVBoxLayout* layout = new QVBoxLayout(ui_->tab_structure);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(structure_wgt_);
}
void PowerAnalysisWgt::CreateTaskConfigTab()
{
	task_wgt_ = new TaskConfigWgt(power_analysis_, base_data_->get_warhead_wrap()->get_structure());
	QVBoxLayout* layout = new QVBoxLayout(ui_->tab_task);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(task_wgt_);
}
void PowerAnalysisWgt::CreateFormulaCountTab()
{
	formula_wgt_ = new FormulaCountWgt(power_analysis_, base_data_, operator_dic_);
	QVBoxLayout* layout = new QVBoxLayout(ui_->tab_formula);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(formula_wgt_);
}
void PowerAnalysisWgt::CreateResultProcessTab()
{
	result_wgt_ = new ResultProcessWgt(power_analysis_, operator_dic_);
	QVBoxLayout* layout = new QVBoxLayout(ui_->tab_result);
	layout->addWidget(result_wgt_);
}
void PowerAnalysisWgt::on_current_tab_changed(int index)
{
	switch(index)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		return ;
	}
}

