#pragma once
#include <QtWidgets>

class PowerAnalysis;
class PowerAnalysisBaseData;
class OperatorDictionary;
class SubProcedureData;
class CountTaskData;
class OperatorEngine;
class QDomElement;
namespace Ui { class FormulaCount; }
class FormulaCountWgt :
	public QWidget
{
	Q_OBJECT
public:
	FormulaCountWgt(PowerAnalysis* power_analysis, const PowerAnalysisBaseData* base_data, const OperatorDictionary* dict, QWidget* parent=0);
	virtual ~FormulaCountWgt(void);
public slots:
	void on_count();
	void on_int_argu_changed(int value);
	void on_double_argu_changed(double value);
	void on_enum_argu_changed(int index);
	void on_bool_argu_changed(bool value);
	void on_update_ui();
signals:
	void sig_result_changed();
protected:
	PowerAnalysis* power_analysis_;
	const PowerAnalysisBaseData* base_data_;
	const OperatorDictionary* dict_;
	Ui::FormulaCount* ui_;
	QMap<QComboBox*, CountTaskData*> box_2_task_;
	QMap<QWidget*, QPair<int, OperatorEngine*> > wgt_2_id_and_engine_;
	bool update_flag_;

	void InitUi();
	QWidget* CreateSubProcedurePage(const SubProcedureData* sub_procedure);
	QWidget* CreateFormulaParamPage(OperatorEngine* operator_engine);
	QGroupBox* CreateGroupArguments(QDomElement* element, OperatorEngine* operator_engine);
	QHBoxLayout* CreateArguments(QDomElement* element, OperatorEngine* operator_engine);
	QHBoxLayout* CreateEnumArgument(QDomElement* element, OperatorEngine* operator_engine);
	QHBoxLayout* CreateIntArgument(QDomElement* element, OperatorEngine* operator_engine);
	QHBoxLayout* CreateDoubleArgument(QDomElement* element, OperatorEngine* operator_engine);
	QHBoxLayout* CreateBoolArgument(QDomElement* element, OperatorEngine* operator_engine);

	virtual void showEvent(QShowEvent * event);
};

