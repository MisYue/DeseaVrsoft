#include "material_dialog.h"
#include <WarheadMaterialLib/warheadmateriallib.h>

MaterialDialog::MaterialDialog(Type type, QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	QTableWidget* tab = new QTableWidget(this);
	layout->addWidget(tab);

	WarheadMaterialLib& lib = WarheadMaterialLib::intances();
	QStringList property_names;
	QStringList material_names;
	if(type == kCharge)
	{
		property_names = WarheadMaterialLib::GetChargePropertyNames();
		material_names = lib.GetChargeNames();
	}
	else 
	{
		property_names = WarheadMaterialLib::GetMetalPropertyNames();
		material_names = lib.GetMetalNames();
	}
	int row_count = material_names.size();
	int column_count = property_names.size();
	tab->setRowCount(row_count);
	tab->setColumnCount(column_count);
	tab->setHorizontalHeaderLabels(property_names);
	for(int i=0; i<row_count; ++i)
	{
		QString name = material_names[i];
		QString properties;
		if(type == kCharge)
			properties = lib.GetChargeProperties(name);
		else
			properties = lib.GetMetalProperties(name);
		QStringList property_list = properties.split(',');
		Q_ASSERT(property_list.size() == column_count);
		for(int j=0; j<column_count; ++j)
		{
			QTableWidgetItem *newItem = new QTableWidgetItem(property_list[j]);
			tab->setItem(i, j, newItem);
		}
	}
}