#pragma once
#include <QtWidgets>

class PowerAnalysis;
class OperatorDictionary;
class SubProcedureData;
class QDomElement;
namespace Ui { class FormulaCount; }
class ResultProcessWgt :
	public QWidget
{
	Q_OBJECT
public:
	ResultProcessWgt(PowerAnalysis* power_analysis, const OperatorDictionary* dict, QWidget* parent=0);
	virtual ~ResultProcessWgt(void);
public slots:
	void on_export();
	void on_update_ui();
protected:
	PowerAnalysis* power_analysis_;
	const OperatorDictionary* dict_;
	Ui::FormulaCount* ui_;
	QVector< QPair<QListWidget*, QVector<QWidget*> > > result_pages_;
	bool update_flag_;

	void InitUi();
	QWidget* CreateSubProcedurePage(const SubProcedureData* sub_procedure);
	QWidget* CreateResultShowPage(const QString& result_xml);

	QString FormatOutUnitSystem(QDomElement* element, char space);
	QString FormatOutCsv(QDomElement* element, char space);

	virtual void showEvent(QShowEvent * event);
};

