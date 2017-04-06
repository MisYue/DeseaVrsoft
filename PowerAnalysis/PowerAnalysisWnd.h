#pragma once
#include "poweranalysis_global.h"
#include <QtWidgets>

class PowerAnalysis;
class OperatorDictionary;
class PowerAnalysisBaseData;
class WarheadModel;
namespace Ui { class PowerAnalysisWnd; }
class POWERANALYSIS_EXPORT PowerAnalysisWnd :
	public QMainWindow
{
	Q_OBJECT
public:
	PowerAnalysisWnd(const QString& procedure_xml_file, const QString& dictionary_xml_file, WarheadModel* warhead, QWidget* parent=0);
	virtual ~PowerAnalysisWnd(void);
public slots:
	void on_task_config();
	void on_formula_count();
	void on_result_process();
	void on_warhead_structure();

protected:
	OperatorDictionary* operator_dic_;
	PowerAnalysis* power_analysis_;
	PowerAnalysisBaseData* base_data_;
	Ui::PowerAnalysisWnd* ui_;

	void CreateWarheadStructureTab();
	void CreateTaskConfigTab();
	void CreateFormulaCountTab();
	void CreateResultProcessTab();
};

