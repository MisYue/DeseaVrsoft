#include "PowerAnalysisWnd.h"
#include "OperatorDictionary.h"
#include "poweranalysis.h"
#include "ui_poweranalysiswnd.h"
#include "TaskConfigDlg.h"
#include "FormulaCountDlg.h"
#include "PowerAnalysisBaseData.h"
#include "ResultProcessDlg.h"
#include "WarheadStructureDlg.h"
#include <ExpandQtCore/expandqtcore.h>
#include <WarheadModelData/warhead_model.h>

PowerAnalysisWnd::PowerAnalysisWnd(const QString& procedure_xml_file, const QString& dictionary_xml_file, WarheadModel* warhead, QWidget* parent)
	: QMainWindow(parent)
	, power_analysis_(new PowerAnalysis(procedure_xml_file))
	, operator_dic_(new OperatorDictionary(dictionary_xml_file))
	, ui_(new Ui::PowerAnalysisWnd)
	, base_data_(new PowerAnalysisBaseData(warhead))
{
	ui_->setupUi(this);

	if(warhead)
		power_analysis_->set_warhead_type(warhead->get_type());
}


PowerAnalysisWnd::~PowerAnalysisWnd(void)
{
	delete ui_;
}
void PowerAnalysisWnd::CreateWarheadStructureTab()
{

}
void PowerAnalysisWnd::CreateTaskConfigTab()
{

}
void PowerAnalysisWnd::CreateFormulaCountTab()
{

}
void PowerAnalysisWnd::CreateResultProcessTab()
{

}
void PowerAnalysisWnd::on_task_config()
{
	TaskConfigDlg dlg(power_analysis_, base_data_->get_warhead());
	dlg.exec();
}
void PowerAnalysisWnd::on_formula_count()
{
	FormulaCountDlg dlg(power_analysis_, base_data_, operator_dic_);
	dlg.exec();
}
void PowerAnalysisWnd::on_result_process()
{
	ResultProcessDlg dlg(power_analysis_, operator_dic_);
	dlg.exec();
}
void PowerAnalysisWnd::on_warhead_structure()
{
	const WarheadModel* warhead = base_data_->get_warhead();
	WarheadModel* temp_warhead = const_cast<WarheadModel*>(warhead);
	WarheadStructureDlg dlg(&temp_warhead);
	dlg.exec();
	ui_->toolButton_task->setEnabled(temp_warhead);
	ui_->toolButton_operator->setEnabled(temp_warhead);
	ui_->toolButton_result->setEnabled(temp_warhead);
	if(warhead != temp_warhead)
	{
		base_data_->set_warhead(temp_warhead);
		power_analysis_->set_warhead_type(temp_warhead->get_type());
	}
}
