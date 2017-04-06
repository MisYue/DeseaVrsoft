#include "ResultProcessWgt.h"
#include "ui_formulacount.h"
#include "poweranalysis.h"
#include "OperatorDictionary.h"
#include "OperatorEngine.h"
#include <BasicTool/expandqtcore.h>
#include <QtXml>

const int g_c_format_width = 20;

ResultProcessWgt::ResultProcessWgt(PowerAnalysis* power_analysis, const OperatorDictionary* dict, QWidget* parent)
	: QWidget(parent)
	, power_analysis_(power_analysis)
	, dict_(dict)
	, ui_(new Ui::FormulaCount)
	, update_flag_(false)
{
	ui_->setupUi(this);

	InitUi();
}


ResultProcessWgt::~ResultProcessWgt(void)
{
	delete ui_;
}

void ResultProcessWgt::on_export()
{
	//找到要导出的是哪一项
	int tab_index = ui_->tabWidget->currentIndex();
	int task_index = result_pages_[tab_index].first->currentRow();
	QTextBrowser* browser = qobject_cast<QTextBrowser*>(result_pages_[tab_index].second[tab_index]);
	Q_ASSERT(browser);
	QString text = browser->toPlainText();
	if(text.isEmpty())
		return ;
	QString file_name = QFileDialog::getSaveFileName(this, ExpandQtCore::fromGBK("保存"), QString(), ExpandQtCore::fromGBK("威力结果 (*.csv)"));
	if(!file_name.isEmpty())
	{
		QFile file(file_name);
		if(!file.open(QFile::WriteOnly | QFile::Text))
			return ;
		QTextStream stream(&file);
		stream << text;
	}
}
void ResultProcessWgt::InitUi()
{
	setWindowTitle(ExpandQtCore::fromGBK("结果可视化"));
	ui_->pushButton_Count->setText(ExpandQtCore::fromGBK("导出"));
	connect(ui_->pushButton_Count, SIGNAL(clicked()), this, SLOT(on_export()));
	on_update_ui();
}
void ResultProcessWgt::on_update_ui()
{
	if(!isVisible())
	{
		update_flag_ = true;
		return ;
	}
	result_pages_.clear();
	ui_->tabWidget->clear();
	int warhead_type = power_analysis_->get_warhead_type();
	const ProcedureData* procedure = power_analysis_->GetProcedure(warhead_type);
	Q_ASSERT(procedure);
	result_pages_.reserve(procedure->sub_procedure_ids.size());
	foreach(QString sub_id, procedure->sub_procedure_ids)
	{
		const SubProcedureData* sub_procedure = power_analysis_->GetSubProcedure(sub_id);
		Q_ASSERT(sub_procedure);
		result_pages_.push_back(QPair<QListWidget*, QVector<QWidget*> >());
		QWidget* page = CreateSubProcedurePage(sub_procedure);
		ui_->tabWidget->addTab(page, sub_procedure->mean);
	}
}
void ResultProcessWgt::showEvent(QShowEvent * event)
{
	if(update_flag_)
	{
		update_flag_ = false;
		on_update_ui();
	}
}
QWidget* ResultProcessWgt::CreateSubProcedurePage(const SubProcedureData* sub_procedure)
{
	QWidget* page = new QWidget(this);
	QListWidget* list_wgt = new QListWidget(this);
	QStackedWidget* stacked_wgt = new QStackedWidget(this);
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
	result_pages_.back().first = list_wgt;
	result_pages_.back().second.reserve(sub_procedure->tasks.size());
	foreach(const CountTaskData& task, sub_procedure->tasks)
	{
		if(!task.checked)
			continue;

		list_wgt->addItem(task.mean);
		QString result_xml;
		if(!task.checked_operator.isEmpty())
		{
			//找到任务采用的算子引擎
			const OperatorEngine* engine = power_analysis_->GetOperatorEngine(task.operator_lib_id, task.checked_operator);
			Q_ASSERT(engine);
			result_xml = engine->get_result_xml();
		}
		QWidget* result_wgt = CreateResultShowPage(result_xml);
		result_wgt->setObjectName(task.mean);
		result_pages_.back().second.push_back(result_wgt);
		stacked_wgt->addWidget(result_wgt);
	}
	connect(list_wgt, SIGNAL(currentRowChanged(int)), stacked_wgt, SLOT(setCurrentIndex(int)));
	list_wgt->setCurrentRow(0);
	return page;
}
QWidget* ResultProcessWgt::CreateResultShowPage(const QString& result_xml)
{
	QTextBrowser* page = new QTextBrowser(this);
	if(result_xml.isEmpty())
		return page;
	page->setFont(QFont("Times", 10, QFont::Normal));
	//解析参数
	QDomDocument doc;
	bool ok = doc.setContent(result_xml);
	Q_ASSERT(ok);
	QDomElement root = doc.documentElement();
	QString str_result;
	for(QDomElement element = root.firstChildElement("argument"); !element.isNull(); element = element.nextSiblingElement())
	{
		QString type = element.attribute("type");
		if("unit_system" == type)
			str_result += FormatOutUnitSystem(&element, ',');
		else if("csv" == type)
			str_result += FormatOutCsv(&element, ',');
	}
	page->setText(str_result);
	return page;
}

QString ResultProcessWgt::FormatOutUnitSystem(QDomElement* element, char space)
{
	Q_ASSERT(element);
	QString result;
	QTextStream stream(&result);
	QString key = element->attribute("name");
	QString val = dict_->GetVal(key);
	stream << val << "\n";
	for(QDomElement child = element->firstChildElement(); !child.isNull(); child = child.nextSiblingElement())
	{
		QString name = dict_->GetVal(child.attribute("type"));
		QString val = dict_->GetVal(child.attribute("val"));
		stream << name << space << val << "\n";
	}
	return result;
}
QString ResultProcessWgt::FormatOutCsv(QDomElement* element, char space)
{
	Q_ASSERT(element);
	QString result;
	QTextStream stream(&result);
	QString key = element->attribute("name");
	QString val = dict_->GetVal(key);
	stream << val << "\n";
	//表头
	QDomElement header = element->firstChildElement();
	{
		QString vals = header.attribute("val");
		QStringList val_list = vals.split(',');
		stream << dict_->GetVal(val_list.first());
		val_list.removeFirst();
		foreach(const QString& val, val_list)
		{
			stream << space << dict_->GetVal(val);
		}
		stream << '\n';
	}
	for(QDomElement child = header.nextSiblingElement(); !child.isNull(); child = child.nextSiblingElement())
	{
		//QString vals = child.attribute("val");
		//QStringList val_list = vals.split(',');
		stream << child.attribute("val") << "\n";
	}
	return result;
}