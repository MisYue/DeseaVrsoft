#include "MaterialViewDlg.h"
#include <MaterialLib/materiallib.h>

MaterialViewDlg::MaterialViewDlg(const MaterialLib* material_lib, QWidget* parent)
	: QDialog(parent)
	, material_lib_(material_lib)
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	QTableWidget* tab = new QTableWidget(this);
	layout->addWidget(tab);

	QStringList property_names = const_cast<MaterialLib*>(material_lib_)->GetPropertyNames();
	QMap<QString, QString> guid_2_name = const_cast<MaterialLib*>(material_lib_)->GetAllGuidAndNames();
	int row_count = guid_2_name.size();
	int column_count = property_names.size();
	tab->setRowCount(row_count);
	tab->setColumnCount(column_count);
	tab->setHorizontalHeaderLabels(property_names);
	int i = 0;
	for(QMap<QString, QString>::iterator beg = guid_2_name.begin();
		beg != guid_2_name.end();
		++beg)
	{
		const Material* mtl = material_lib_->GetMaterial(beg.key());
		QStringList property_list = mtl->GetPropertyValues();
		Q_ASSERT(property_list.size() == column_count);
		for(int j=0; j<column_count; ++j)
		{
			QTableWidgetItem *newItem = new QTableWidgetItem(property_list[j]);
			tab->setItem(i, j, newItem);
		}
		++i;
	}
	setGeometry(200, 200, 800, 600);
}


MaterialViewDlg::~MaterialViewDlg(void)
{
}
