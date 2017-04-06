#include "FormulaCountWgt.h"
#include "poweranalysis.h"
#include "PowerAnalysisBaseData.h"
#include "OperatorDictionary.h"
#include "OperatorEngine.h"
#include "ui_formulacount.h"
#include <WarheadModelData/warhead_model.h>
#include <BasicTool/expandqtcore.h>
#include <BasicTool/expandqtgui.h>
#include <BasicTool/basictool.h>
#include <QtXml>

FormulaCountWgt::FormulaCountWgt(PowerAnalysis* power_analysis, const PowerAnalysisBaseData* base_data, const OperatorDictionary* dict, QWidget* parent)
	: QWidget(parent)
	, power_analysis_(power_analysis)
	, base_data_(base_data)
	, dict_(dict)
	, ui_(new Ui::FormulaCount)
	, update_flag_(false)
{
	Q_ASSERT(power_analysis_);
	Q_ASSERT(base_data_);
	Q_ASSERT(dict_);
	ui_->setupUi(this);
	InitUi();
}
FormulaCountWgt::~FormulaCountWgt(void)
{
	delete ui_;
}
void FormulaCountWgt::InitUi()
{
	connect(ui_->pushButton_Count, SIGNAL(clicked()), this, SLOT(on_count()));
	on_update_ui();
}
void FormulaCountWgt::on_update_ui()
{
	if(!isVisible())
	{
		update_flag_ = true;
		return ;
	}
	box_2_task_.clear();
	wgt_2_id_and_engine_.clear();
	ui_->tabWidget->clear();
	const WarheadModel* warhead = base_data_->get_warhead_wrap()->get_structure();
	WarheadType warhead_type = warhead->get_type();
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
void FormulaCountWgt::showEvent(QShowEvent * event)
{
	if(update_flag_)
	{
		update_flag_ = false;
		on_update_ui();
	}
}
void FormulaCountWgt::on_count()
{
	//小流程的每一任务进行计算
	const WarheadModel* warhead = base_data_->get_warhead_wrap()->get_structure();
	WarheadType warhead_type = warhead->get_type();
	const ProcedureData* procedure = power_analysis_->GetProcedure(warhead_type);
	Q_ASSERT(procedure);
	bool ok = true;
	foreach(QString sub_id, procedure->sub_procedure_ids)
	{
		const SubProcedureData* sub_procedure = power_analysis_->GetSubProcedure(sub_id);
		Q_ASSERT(sub_procedure);
		foreach(const CountTaskData& task, sub_procedure->tasks)
		{
			//任务对应的QCombox
			CountTaskData* count_task = const_cast<CountTaskData*>(&task);
			QComboBox* box = box_2_task_.key(count_task, 0);
			Q_ASSERT(box);
			//获取算子dll
			count_task->checked_operator = box->currentText();
			//获取算子引擎
			OperatorEngine* engine = 0;
			foreach(const OperatorData& operator_data, power_analysis_->GetOperatorLib(task.operator_lib_id)->operators)
			{
				if(operator_data.dll == task.checked_operator)
				{
					engine = const_cast<OperatorEngine*>(operator_data.engine);
					break;
				}
			}
			Q_ASSERT(engine);
			engine->Count();
		}
	}
	if(ok)
	{
		ExpandQtGui::information(this, ExpandQtCore::fromGBK("信息"), ExpandQtCore::fromGBK("威力分析计算完成！"));
		emit sig_result_changed();
	}
}
void FormulaCountWgt::on_int_argu_changed(int value)
{
	QSpinBox* box = qobject_cast<QSpinBox*>(sender());
	Q_ASSERT(box);
	QPair<int, OperatorEngine*> key_and_engine = wgt_2_id_and_engine_.value(box);
	Q_ASSERT(key_and_engine.second);
	key_and_engine.second->SetArgumentValue(key_and_engine.first, QString::number(box->value()));
}
void FormulaCountWgt::on_double_argu_changed(double value)
{
	QDoubleSpinBox* box = qobject_cast<QDoubleSpinBox*>(sender());
	Q_ASSERT(box);
	QPair<int, OperatorEngine*> key_and_engine = wgt_2_id_and_engine_.value(box);
	Q_ASSERT(key_and_engine.second);
	key_and_engine.second->SetArgumentValue(key_and_engine.first, QString::number(box->value()));
}
void FormulaCountWgt::on_enum_argu_changed(int index)
{
	QComboBox* box = qobject_cast<QComboBox*>(sender());
	Q_ASSERT(box);
	QPair<int, OperatorEngine*> key_and_engine = wgt_2_id_and_engine_.value(box);
	Q_ASSERT(key_and_engine.second);
	key_and_engine.second->SetArgumentValue(key_and_engine.first, QString::number(box->itemData(index).toInt()));
}
void FormulaCountWgt::on_bool_argu_changed(bool value)
{
	QCheckBox* box = qobject_cast<QCheckBox*>(sender());
	Q_ASSERT(box);
	QPair<int, OperatorEngine*> key_and_engine = wgt_2_id_and_engine_.value(box);
	Q_ASSERT(key_and_engine.second);
	key_and_engine.second->SetArgumentValue(key_and_engine.first, value ? "1" : "0");
}
QWidget* FormulaCountWgt::CreateSubProcedurePage(const SubProcedureData* sub_procedure)
{
	QWidget* page = new QWidget(this);
	QListWidget* list_wgt = new QListWidget(this);
	list_wgt->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
	QStackedWidget* stacked_wgt = new QStackedWidget(this);
	stacked_wgt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QHBoxLayout* layout = new QHBoxLayout(page);
	QVBoxLayout* v_layout = new QVBoxLayout;
	v_layout->setContentsMargins(0, 0, 0, 0);
	v_layout->addWidget(new QLabel(ExpandQtCore::fromGBK("任务列表")));
	v_layout->addWidget(list_wgt);
	layout->addWidget(stacked_wgt);
	layout->addLayout(v_layout);
	layout->setContentsMargins(9, 9, 0, 0);
	layout->setStretch(0, 1);
	layout->setStretch(1, 1);
	foreach(const CountTaskData& task, sub_procedure->tasks)
	{
		if(!task.checked)
			continue;
		QWidget* sub_wgt = new QWidget(this);
		stacked_wgt->addWidget(sub_wgt);
		list_wgt->addItem(task.mean);

		QVBoxLayout* v_layout = new QVBoxLayout(sub_wgt);
		QHBoxLayout* h_layout = new QHBoxLayout;
		QLabel* label = new QLabel(this);
		QComboBox* box = new QComboBox(this);
		box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		h_layout->addWidget(label);
		h_layout->addWidget(box);
		v_layout->addLayout(h_layout);
		QStackedWidget* formulas_stacked_wgt =new QStackedWidget(this);
		v_layout->addWidget(formulas_stacked_wgt);
		v_layout->setContentsMargins(0, 0, 0, 0);
		const OperatorLib* lib = power_analysis_->GetOperatorLib(task.operator_lib_id);
		label->setText(lib->mean);
		foreach(const OperatorData& operator_data, lib->operators)
		{
			box->addItem(operator_data.dll);
			box->setItemData(box->count()-1, QVariant(reinterpret_cast<const char*>(&operator_data)));
			QWidget* page = CreateFormulaParamPage(operator_data.engine);
			formulas_stacked_wgt->addWidget(page);
		}
		box_2_task_.insert(box, const_cast<CountTaskData*>(&task));
		connect(box, SIGNAL(currentIndexChanged(int)), formulas_stacked_wgt, SLOT(setCurrentIndex(int)));
		box->setCurrentIndex(0);
	}
	connect(list_wgt, SIGNAL(currentRowChanged(int)), stacked_wgt, SLOT(setCurrentIndex(int)));
	list_wgt->setCurrentRow(0);
	return page;
}
QWidget* FormulaCountWgt::CreateFormulaParamPage(OperatorEngine* operator_engine)
{
	QWidget* page = new QWidget(this);
	QVBoxLayout* main_layout = new QVBoxLayout(page);
	main_layout->setContentsMargins(0, 0, 0, 0);
	QScrollArea* scroll = new QScrollArea(page);
	QWidget* scroll_contents =new QWidget;
	scroll->setWidgetResizable(true);
	scroll->setWidget(scroll_contents);
	main_layout->addWidget(scroll);
	//获取参数树
	QString argu_xml_ = operator_engine->get_argu_xml();
	//解析参数
	QDomDocument doc;
	bool ok = doc.setContent(argu_xml_);
	Q_ASSERT(ok);
	QDomElement root = doc.documentElement();
	QVBoxLayout* layout = new QVBoxLayout(scroll_contents);
	for(QDomElement child = root.firstChildElement(); !child.isNull(); child = child.nextSiblingElement())
	{
		if(child.tagName() == "argumentgroup")
			layout->addWidget(CreateGroupArguments(&child, operator_engine));
		else if(child.tagName() == "argument")
			layout->addLayout(CreateArguments(&child, operator_engine));
	}
	layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding));
	return page;
}
QGroupBox* FormulaCountWgt::CreateGroupArguments(QDomElement* element, OperatorEngine* operator_engine)
{
	Q_ASSERT(element);
	QGroupBox* group_box = new QGroupBox(this);
	QString key = element->attribute("name");
	QString label = dict_->GetVal(key);
	group_box->setTitle(label);
	QVBoxLayout* layout = new QVBoxLayout(group_box);
	for(QDomElement child = element->firstChildElement(); !child.isNull(); child = child.nextSiblingElement())
	{
		if(child.tagName() == "argumentgroup")
			layout->addWidget(CreateGroupArguments(&child, operator_engine));
		else if(child.tagName() == "argument")
			layout->addLayout(CreateArguments(&child, operator_engine));
	}
	return group_box;
}
QHBoxLayout* FormulaCountWgt::CreateArguments(QDomElement* element, OperatorEngine* operator_engine)
{
	Q_ASSERT(element);
	QString type = element->attribute("type").toLower();
	if("enum" == type)
		return CreateEnumArgument(element, operator_engine);
	else if("integer" == type)
		return CreateIntArgument(element, operator_engine);
	else if("double" == type)
		return CreateDoubleArgument(element, operator_engine);
	else if("bool" == type)
		return CreateBoolArgument(element, operator_engine);
	return new QHBoxLayout;
}
QHBoxLayout* FormulaCountWgt::CreateEnumArgument(QDomElement* element, OperatorEngine* operator_engine)
{
	QHBoxLayout* layout = new QHBoxLayout;
	QString key = element->attribute("name");
	QString mean = dict_->GetVal(key);
	QLabel* label = new QLabel(mean, this);
	layout->addWidget(label);
	QComboBox* box = new QComboBox(this);
	layout->addWidget(box);
	label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QMap<int, int> index_2_val;
	for(QDomElement child = element->firstChildElement(); !child.isNull(); child = child.nextSiblingElement())
	{
		int val = child.attribute("val").toInt();
		QString name = child.attribute("name");
		box->addItem(dict_->GetVal(name));
		int index = box->count()-1;
		box->setItemData(index, val);
		index_2_val.insert(index, val);
	}
	int id = element->attribute("id").toInt();
	//判断是否是战斗部结构参数
	QString str_val = base_data_->GetData(key);
	if(str_val.isEmpty())
		str_val = operator_engine->GetArgumentValue(id);
	else
		box->setEnabled(false);
	box->setCurrentIndex(index_2_val.key(str_val.toInt()));
	wgt_2_id_and_engine_.insert(box, qMakePair<int, OperatorEngine*>(id, operator_engine));
	connect(box, SIGNAL(currentIndexChanged(int)), this, SLOT(on_enum_argu_changed(int)));
	return layout;
}
QHBoxLayout* FormulaCountWgt::CreateIntArgument(QDomElement* element, OperatorEngine* operator_engine)
{
	QHBoxLayout* layout = new QHBoxLayout;
	QString key = element->attribute("name");
	QString mean = dict_->GetVal(key);
	QLabel* label = new QLabel(mean, this);
	layout->addWidget(label);
	QSpinBox* box = new QSpinBox(this);
	label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	layout->addWidget(box);
	int val = element->attribute("default", "0").toInt();
	QDomElement child = element->firstChildElement();
	int max = child.attribute("max", QString::number(INT_MAX)).toInt();
	int min = child.attribute("min", QString::number(INT_MIN)).toInt();
	int step = child.attribute("step", "1").toInt();
	box->setMaximum(max);
	box->setMinimum(min);
	box->setSingleStep(step);
	box->setValue(val);
	int id = element->attribute("id").toInt();
	//判断是否是战斗部结构参数
	QString str_val = base_data_->GetData(key);
	if(str_val.isEmpty())
		str_val = operator_engine->GetArgumentValue(id);
	else
		box->setEnabled(false);
	box->setValue(str_val.toInt());
	wgt_2_id_and_engine_.insert(box, qMakePair<int, OperatorEngine*>(id, operator_engine));
	connect(box, SIGNAL(valueChanged(int)), this, SLOT(on_int_argu_changed(int)));
	return layout;
}
QHBoxLayout* FormulaCountWgt::CreateDoubleArgument(QDomElement* element, OperatorEngine* operator_engine)
{
	QHBoxLayout* layout = new QHBoxLayout;
	QString key = element->attribute("name");
	QString mean = dict_->GetVal(key);
	QLabel* label = new QLabel(mean, this);
	layout->addWidget(label);
	QDoubleSpinBox* box = new QDoubleSpinBox(this);
	label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	layout->addWidget(box);
	double val = element->attribute("default", "0").toDouble();
	QDomElement child = element->firstChildElement();
	double max = child.attribute("max", QString::number(INT_MAX)).toDouble();
	double min = child.attribute("min", QString::number(INT_MIN)).toDouble();
	QString precision = child.attribute("precision");
	int decimals = 10; 
	if(!precision.isEmpty())
		decimals = BasicTool::decimals(precision.toDouble());
	double step = child.attribute("step", "1").toDouble();
	box->setMaximum(max);
	box->setMinimum(min);
	box->setSingleStep(step);
	box->setValue(val);
	box->setDecimals(decimals);
	int id = element->attribute("id").toInt();
	//判断是否是战斗部结构参数
	QString str_val = base_data_->GetData(key);
	if(str_val.isEmpty())
		str_val = operator_engine->GetArgumentValue(id);
	else
		box->setEnabled(false);
	box->setValue(str_val.toDouble());
	wgt_2_id_and_engine_.insert(box, qMakePair<int, OperatorEngine*>(id, operator_engine));
	connect(box, SIGNAL(valueChanged(double)), this, SLOT(on_double_argu_changed(double)));
	return layout;
}
QHBoxLayout* FormulaCountWgt::CreateBoolArgument(QDomElement* element, OperatorEngine* operator_engine)
{
	QHBoxLayout* layout = new QHBoxLayout;
	QString key = element->attribute("name");
	QString label = dict_->GetVal(key);
	QCheckBox* box = new QCheckBox(this);
	layout->addWidget(box);
	box->setText(label);
	box->setChecked(element->attribute("default", "1").toInt());
	int id = element->attribute("id").toInt();
	//判断是否是战斗部结构参数
	QString str_val = base_data_->GetData(key);
	if(str_val.isEmpty())
		str_val = operator_engine->GetArgumentValue(id);
	else
		box->setEnabled(false);
	box->setChecked(str_val.toInt());
	wgt_2_id_and_engine_.insert(box, qMakePair<int, OperatorEngine*>(id, operator_engine));
	connect(box, SIGNAL(clicked(bool)), this, SLOT(on_bool_argu_changed(bool)));
	return layout;
}
