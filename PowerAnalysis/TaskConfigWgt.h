#pragma once
#include <QtWidgets>

class PowerAnalysis;
class WarheadModel;
class SubProcedureData;
class CountTaskData;
namespace Ui { class TaskConfig; }
class TaskConfigWgt :
	public QWidget
{
	Q_OBJECT
public:
	TaskConfigWgt(PowerAnalysis* power_analysis, const WarheadModel* warhead, QWidget* parent=0);
	virtual ~TaskConfigWgt(void);
public slots:
	void on_task_state_changed(bool checked);
signals:
	void sig_config_changed();
protected:
	PowerAnalysis* power_analysis_;
	const WarheadModel* warhead_;
	Ui::TaskConfig* ui_;
	QMap<QCheckBox*, const CountTaskData*> box_2_task_;
	void InitUi();
	QWidget* CreateSubProcedurePage(const SubProcedureData* sub_procedure);
};

