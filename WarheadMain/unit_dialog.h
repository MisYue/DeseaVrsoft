#pragma once
#include <QtWidgets>

namespace Ui { class unit; }
class UnitDialog : public QDialog
{
	Q_OBJECT
public:
	UnitDialog(QWidget* parent = 0);
	~UnitDialog();
public slots:
	virtual void accept();
	void on_set_material_file();
	void on_material_file_changed(const QString& text);
	void on_view_material();
private:
	Ui::unit* ui_;
	QLayout* CreateLayout(const QStringList& unit_names, const QString& current_unit);
	QString GetCurrentUnit(QLayout* layout);
	bool metal_already_open_;
	bool charge_already_open_;
};