#include "TaskConfigWgt.h"
#include "poweranalysis.h"
#include "ui_taskconfig.h"
#include <WarheadModelData/warhead_model.h>
#include <BasicTool/expandqtcore.h>

TaskConfigWgt::TaskConfigWgt(PowerAnalysis* power_analysis, const WarheadModel* warhead, QWidget* parent)
	: QWidget(parent)
	, power_analysis_(power_analysis)
	, warhead_(warhead)
	, ui_(new Ui::TaskConfig)
{
	Q_ASSERT(power_analysis_);
	Q_ASSERT(warhead_);
	ui_->setupUi(this);
	InitUi();
}
TaskConfigWgt::~TaskConfigWgt(void)
{
	delete ui_;
}
void TaskConfigWgt::InitUi()
{
	WarheadType warhead_type = warhead_->get_type();
	QStringList type_mean;
	type_mean << ExpandQtCore::fromGBK("É±±¬µ¯") << ExpandQtCore::fromGBK("ÇÖ±¬µ¯");
	setWindowTitle(ExpandQtCore::fromGBK("%1ÍþÁ¦·ÖÎöÈÎÎñÅäÖÃ").arg(type_mean[warhead_type]));
	const ProcedureData* procedure = power_analysis_->GetProcedure(warhead_type);
	Q_ASSERT(procedure);
	foreach(QString sub_id, procedure->sub_procedure_ids)
	{
		const SubProcedureData* sub_procedure = power_analysis_->GetSubProcedure(sub_id);
		Q_ASSERT(sub_procedure);
		QWidget* page = CreateSubProcedurePage(sub_procedure);
		ui_->tabWidget->addTab(page, sub_procedure->mean);
	}
}
QWidget* TaskConfigWgt::CreateSubProcedurePage(const SubProcedureData* sub_procedure)
{
	QWidget* page = new QWidget(this);
	QVBoxLayout* layout = new QVBoxLayout(page);
	foreach(const CountTaskData& task, sub_procedure->tasks)
	{
		QCheckBox* box = new QCheckBox(this);
		box->setText(task.mean);
		box->setChecked(task.checked);
		layout->addWidget(box);
		box_2_task_.insert(box, &task);
		connect(box, SIGNAL(clicked(bool)), this, SLOT(on_task_state_changed(bool)));
	}
	layout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
	return page;
}
void TaskConfigWgt::on_task_state_changed(bool checked)
{
	QCheckBox* box = qobject_cast<QCheckBox*>(sender());
	const CountTaskData* task = box_2_task_.value(box, 0);
	Q_ASSERT(task);
	const_cast<CountTaskData*>(task)->checked = checked;
	emit sig_config_changed();
}
