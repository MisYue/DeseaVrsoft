//***************************************
//	创建时间:	2015:11:4   17:55
//	文件名称: 	PartEditor.cpp
//	文件作者:	岳群磊
//	
//	功能说明:	实现部件编辑器
//***************************************

#include "partEditor.h"
#include "itemWidget.h"
#include "StringExtend.h"
#include <QCheckBox>
#include <QRadioButton>
#include <QMessageBox>
#include <cassert>

static QTreeWidgetItem* g_item = NULL;
static bool g_flag;
static std::string g_name;

QTreeWidgetItem* NewPartEditorItem(const QString& text)
{
	QTreeWidgetItem* item = new QTreeWidgetItem;
	item->setText(0, text);
	return item;
}
PartEditor::PartEditor(QWidget* parent) : QTreeWidget(parent)
{
	QStringList names;
	names << QString::fromLocal8Bit("钢") << QString::fromLocal8Bit("铁");
	m_materials.insert(QString::fromLocal8Bit("金属"), names);
	names.clear();
	names << QString::fromLocal8Bit("C-15混凝土") << QString::fromLocal8Bit("C-20混凝土");
	m_materials.insert(QString::fromLocal8Bit("非金属"), names);
	m_criterions.push_back(QString::fromLocal8Bit("等效厚度判据"));
	m_criterions.push_back(QString::fromLocal8Bit("动能弹体判据"));
	m_criterions.push_back(QString::fromLocal8Bit("破片判据"));
	m_criterions.push_back(QString::fromLocal8Bit("冲击波判据"));
	m_criterionEMTItem = NULL;
	m_criterionKEItem = NULL;
	m_criterionFRAGItem = NULL;
	m_criterionSWItem = NULL;
	m_geometrySizeItem = NULL;
	Init();
	Connect();
}

void PartEditor::Connect()
{
	connect(this, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(EditorItemClicked(QTreeWidgetItem*, int)));
	connect(this, SIGNAL(itemCollapsed(QTreeWidgetItem*)), this, SLOT(EditorItemCollapsed(QTreeWidgetItem*)));
	connect(this, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(EditorItemExpanded(QTreeWidgetItem*)));
	connect(this, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(OnItemChanged(QTreeWidgetItem*, int)));
}

void PartEditor::Init()
{
	setHeaderLabels(QStringList() << QString::fromLocal8Bit("属性") << QString::fromLocal8Bit("值"));
	m_nameItem = NewPartEditorItem(QString::fromLocal8Bit("名称"));
	addTopLevelItem(m_nameItem);
	IWLineText* lineText = new IWLineText(m_nameItem);
	m_nameItem->setData(1, VisibleRole, 0);
	m_nameItem->setData(1, ItemWidgetRole, (unsigned)lineText);
	setItemWidget(m_nameItem, 1, lineText);
	m_codeItem = NewPartEditorItem(QString::fromLocal8Bit("代码"));
	addTopLevelItem(m_codeItem);
	lineText = new IWLineText(m_codeItem);
	m_codeItem->setData(1, VisibleRole, 0);
	m_codeItem->setData(1, ItemWidgetRole, (unsigned)lineText);
	setItemWidget(m_codeItem, 1, lineText);
	QTreeWidgetItem* item = NewPartEditorItem(QString::fromLocal8Bit("壳体"));
	addTopLevelItem(item);
	setItemWidget(item, 1, new QCheckBox);
	m_thicknessItem = NewPartEditorItem(QString::fromLocal8Bit("厚度(毫米)"));
	addTopLevelItem(m_thicknessItem);
	QDoubleSpinBox* box = new IWDoubleSpinBox(m_thicknessItem);
	box->setMaximum(10000);
	box->setSingleStep(1.0);
	m_thicknessItem->setData(1, VisibleRole, 0);
	m_thicknessItem->setData(1, ItemWidgetRole, (unsigned)box);
	setItemWidget(m_thicknessItem, 1, box);
	m_shellItem = item;
	CreateMaterialItem();
	CreateDamageCriterionItem();
	expandAll();
}
void PartEditor::SetProperties(const PartExtraInfo& partInfo)
{
	g_flag = true;
	g_name = partInfo.GetPropertyValue("name");
	SetLineEditValue(m_nameItem, g_name);
	SetLineEditValue(m_codeItem, partInfo.GetPropertyValue("code"));
	QCheckBox* checkBox = dynamic_cast<QCheckBox*>(itemWidget(m_shellItem, 1));
	if(checkBox)
		checkBox->setChecked(StringExtend::toInt(partInfo.GetPropertyValue("shell")));
	SetDoubleItemValue(m_thicknessItem, partInfo.GetPropertyValue("thickness"));
	std::vector<std::string> params;
	StringExtend::toStrings(partInfo.GetPropertyValue("material"), ',', params);
	if(params.size()==2 && m_materialItem->childCount()==2)
	{
		SetComoboBoxItemValue(m_materialItem->child(0), params[0]);
		SetComoboBoxItemValue(m_materialItem->child(1), params[1]);
	}
	params.clear();
	StringExtend::toStrings(partInfo.GetPropertyValue("criterionEMT"), ',', params);
	if(params.size()>=4 && m_criterionEMTItem->childCount()>=3)
	{
		m_criterionEMTItem->setHidden(params[0] == "1" ? false : true);
		SetComoboBoxItemValue(m_criterionEMTItem->child(0), params[1]);
		SetComoboBoxItemValue(m_criterionEMTItem->child(1), params[2]);
		SetDoubleItemValue(m_criterionEMTItem->child(2), params[3]);
	}
	params.clear();
	StringExtend::toStrings(partInfo.GetPropertyValue("criterionKE"), ',', params);
	if(params.size()>=4 && m_criterionKEItem->childCount()>=3)
	{
		m_criterionKEItem->setHidden(params[0] == "1" ? false : true);
		SetComoboBoxItemValue(m_criterionKEItem->child(0), params[1]);
		SetDoubleItemValue(m_criterionKEItem->child(1), params[2]);
		SetDoubleItemValue(m_criterionKEItem->child(2), params[3]);
	}
	params.clear();
	StringExtend::toStrings(partInfo.GetPropertyValue("criterionFRAG"), ',', params);
	if(params.size()>=7 && m_criterionFRAGItem->childCount()>=6)
	{
		m_criterionFRAGItem->setHidden(params[0] == "1" ? false : true);
		SetComoboBoxItemValue(m_criterionFRAGItem->child(0), params[1]);
		SetComoboBoxItemValue(m_criterionFRAGItem->child(1), params[2]);
		SetComoboBoxItemValue(m_criterionFRAGItem->child(2), params[3]);
		SetDoubleItemValue(m_criterionFRAGItem->child(3), params[4]);
		SetDoubleItemValue(m_criterionFRAGItem->child(4), params[5]);
		SetIntItemValue(m_criterionFRAGItem->child(5), params[6]);
	}
	params.clear();
	StringExtend::toStrings(partInfo.GetPropertyValue("criterionSW"), ',', params);
	if(params.size()>=7 && m_criterionSWItem->childCount()>=3)
	{
		m_criterionSWItem->setHidden(params[0] == "1" ? false : true);
		QRadioButton* radioBtn = dynamic_cast<QRadioButton*>(itemWidget(m_criterionSWItem->child(StringExtend::toInt(params[1])),1));
		if(radioBtn)
			radioBtn->setChecked(true);
		SetDoubleItemValue(m_criterionSWItem->child(0)->child(0), params[2]);
		SetDoubleItemValue(m_criterionSWItem->child(1)->child(0), params[3]);
		SetDoubleItemValue(m_criterionSWItem->child(2)->child(0), params[4]);
		SetDoubleItemValue(m_criterionSWItem->child(2)->child(1), params[5]);
		SetDoubleItemValue(m_criterionSWItem->child(2)->child(2), params[6]);
	}
	if(g_item && !g_item->isHidden())
	{
		QWidget* widget = (QWidget*)g_item->data(1, ItemWidgetRole).toUInt();
		if(widget)
		{
			widget->hide();
			g_item->setData(1, VisibleRole, 0);
		}
		g_item = NULL;
	}
}
void PartEditor::GetProperties(PartExtraInfo& partInfo)
{
	partInfo.SetPropertyValue("name", m_nameItem->text(1).toLocal8Bit().data());
	partInfo.SetPropertyValue("code", m_codeItem->text(1).toLocal8Bit().data());
	QCheckBox* checkBox = dynamic_cast<QCheckBox*>(itemWidget(m_shellItem, 1));
	if(checkBox)
		partInfo.SetPropertyValue("shell", checkBox->checkState()==Qt::Checked?"1":"0");
	partInfo.SetPropertyValue("thickness", m_thicknessItem->text(1).toLocal8Bit().data());
	QString material;
	material = m_materialItem->child(0)->text(1);
	material += "," + m_materialItem->child(1)->text(1);;
	partInfo.SetPropertyValue("material", material.toLocal8Bit().data());
	QString value;
	value = m_criterionEMTItem->isHidden() ? "0" : "1";
	for(int i=0; i<m_criterionEMTItem->childCount(); ++i)
		value += "," + m_criterionEMTItem->child(i)->text(1);
	partInfo.SetPropertyValue("criterionEMT", value.toLocal8Bit().data());
	value = m_criterionKEItem->isHidden() ? "0" : "1";
	for(int i=0; i<m_criterionKEItem->childCount(); ++i)
		value += "," + m_criterionKEItem->child(i)->text(1);
	partInfo.SetPropertyValue("criterionKE", value.toLocal8Bit().data());
	value = m_criterionFRAGItem->isHidden() ? "0" : "1";
	for(int i=0; i<m_criterionFRAGItem->childCount(); ++i)
		value += "," + m_criterionFRAGItem->child(i)->text(1);
	partInfo.SetPropertyValue("criterionFRAG", value.toLocal8Bit().data());
	value = m_criterionSWItem->isHidden() ? "0" : "1";
	QString temp;
	for(int i=0; i<m_criterionSWItem->childCount(); ++i)
	{
		QRadioButton* radioButton = dynamic_cast<QRadioButton*>(itemWidget(m_criterionSWItem->child(i), 1));
		if(radioButton->isChecked())
			value += "," + QString::number(i);
		QTreeWidgetItem* childItem = m_criterionSWItem->child(i);
		for(int j=0; j<childItem->childCount(); ++j)
			temp += "," + childItem->child(j)->text(1);
	}
	value += temp;
	partInfo.SetPropertyValue("criterionSW", value.toLocal8Bit().data());
}
void PartEditor::SetComoboBoxItemValue(QTreeWidgetItem* item, const std::string& value)
{
	QComboBox* comboBox = dynamic_cast<QComboBox*>(itemWidget(item, 1));
	if(comboBox)
	{
		QString text = QString::fromLocal8Bit(value.c_str());
		int index = comboBox->findText(text);
		comboBox->setCurrentIndex(index);
	}
}
void PartEditor::SetDoubleItemValue(QTreeWidgetItem* item, const std::string& value)
{
	QDoubleSpinBox* doubleBox = dynamic_cast<QDoubleSpinBox*>(itemWidget(item, 1));
	if(doubleBox)
		doubleBox->setValue(StringExtend::toDouble(value));
}
void PartEditor::SetIntItemValue(QTreeWidgetItem* item, const std::string& value)
{
	QSpinBox* intBox = dynamic_cast<QSpinBox*>(itemWidget(item, 1));
	if(intBox)
		intBox->setValue(StringExtend::toInt(value));
}
void PartEditor::SetColortItemValue(QTreeWidgetItem* item, const QColor& color)
{
	QtColorEditWidget* colorWidget = dynamic_cast<QtColorEditWidget*>(itemWidget(item, 1));
	if(colorWidget)
		colorWidget->setValue(color);
}
void PartEditor::SetLineEditValue(QTreeWidgetItem* item, const std::string& value)
{
	QLineEdit* edit = dynamic_cast<QLineEdit*>(itemWidget(item, 1));
	if(edit)
	{
		QString text = QString::fromLocal8Bit(value.c_str());
		edit->setText(text);
		item->setText(1, text);
	}
}
void PartEditor::EditorItemClicked ( QTreeWidgetItem * item, int column )
{
	if(g_item == item && column == 1)
		return ;
	if(g_item && !g_item->isHidden())
	{
		QWidget* widget = (QWidget*)g_item->data(1, ItemWidgetRole).toUInt();
		if(widget)
		{
			widget->hide();
			g_item->setData(1, VisibleRole, 0);
		}
		g_item = NULL;
	}
	if(!item->isHidden() && column == 1)
	{
		QWidget* widget = (QWidget*)item->data(1, ItemWidgetRole).toUInt();
		if(widget)
		{
			item->setData(1, VisibleRole, 1);

			if(NULL == itemWidget(item, column))
				setItemWidget(item, 1, widget);
			else
				widget->show();
			g_item = item;
		}
	}
}
void PartEditor::EditorItemCollapsed(QTreeWidgetItem* item)
{
}
void PartEditor::EditorItemExpanded(QTreeWidgetItem* item)
{
	if(item->childCount()==0)
	{
		QWidget* widget = (QWidget*)item->data(1, ItemWidgetRole).toUInt();
		if(widget && itemWidget(item, 1) && !dynamic_cast<QCheckBox*>(widget))
		{
			item->setData(1, VisibleRole, 0);
			if(g_item == item)
				g_item = NULL;
		}
	}
	else
	{
		for(int i=0, n = item->childCount(); i<n; ++i)
			EditorItemExpanded(item->child(i));
	}
}
QTreeWidgetItem* PartEditor::CreateMaterialItem()
{
	QTreeWidgetItem* item = NewPartEditorItem(QString::fromLocal8Bit("材料"));
	addTopLevelItem(item);
	CreateMaterialTypeAndNameItems(item);
	m_materialItem = item;
	return item;
}
QTreeWidgetItem* PartEditor::CreateDamageCriterionItem()
{
	m_criterionItem = NewPartEditorItem(QString::fromLocal8Bit("毁伤判据"));
	addTopLevelItem(m_criterionItem);
	m_criterionItem->setData(1, VisibleRole, 0);
	IWComboBoxEx* boxEx = new IWComboBoxEx(m_criterionItem);
	m_criterionItem->setData(1, ItemWidgetRole, (unsigned)boxEx);
	boxEx->addItems(m_criterions);
	connect(boxEx, SIGNAL(addCmd(const QString&)), this, SLOT(OnAddCriterion(const QString&)));
	connect(boxEx, SIGNAL(deleteCmd(const QString&)), this, SLOT(OnDeleteCriterion(const QString&)));
	//等效材料厚度
	m_criterionEMTItem = NewPartEditorItem(QString::fromLocal8Bit("等效厚度判据"));
	m_criterionItem->addChild(m_criterionEMTItem);
	CreateMaterialTypeAndNameItems(m_criterionEMTItem);
	QTreeWidgetItem* thickness = NewPartEditorItem(QString::fromLocal8Bit("材料厚度(mm)"));
	m_criterionEMTItem->addChild(thickness);
	thickness->setData(1, VisibleRole, 0);
	QDoubleSpinBox* box = new IWDoubleSpinBox(thickness);
	box->setMaximum(10000);
	thickness->setData(1, ItemWidgetRole, (unsigned)box);
	setItemWidget(thickness, 1, box);
	//动能弹体
	m_criterionKEItem = NewPartEditorItem(QString::fromLocal8Bit("动能弹体判据"));
	m_criterionItem->addChild(m_criterionKEItem);
	QTreeWidgetItem* warheadShape = NewPartEditorItem(QString::fromLocal8Bit("弹头形状"));
	m_criterionKEItem->addChild(warheadShape);
	IWComboBox* comboBox = new IWComboBox(warheadShape);
	comboBox->addItems(QStringList() << QString::fromLocal8Bit("长方体") << QString::fromLocal8Bit("圆柱体"));
	warheadShape->setData(1, VisibleRole, 0);
	warheadShape->setData(1, ItemWidgetRole, (unsigned)comboBox);
	setItemWidget(warheadShape, 1, comboBox);
	QTreeWidgetItem* mass = NewPartEditorItem(QString::fromLocal8Bit("质量(g)"));
	m_criterionKEItem->addChild(mass);
	mass->setData(1, VisibleRole, 0);
	/*QDoubleSpinBox* */box = new IWDoubleSpinBox(mass);
	box->setMaximum(10000);
	mass->setData(1, ItemWidgetRole, (unsigned)box);
	setItemWidget(mass, 1, box);

	QTreeWidgetItem* vel = NewPartEditorItem(QString::fromLocal8Bit("速度(m/s)"));
	m_criterionKEItem->addChild(vel);
	vel->setData(1, VisibleRole, 0);
	/*QDoubleSpinBox* */box = new IWDoubleSpinBox(vel);
	box->setMaximum(10000);
	vel->setData(1, ItemWidgetRole, (unsigned)box);
	setItemWidget(vel, 1, box);
	//破片
	m_criterionFRAGItem = NewPartEditorItem(QString::fromLocal8Bit("破片判据"));
	m_criterionItem->addChild(m_criterionFRAGItem);
	CreateMaterialTypeAndNameItems(m_criterionFRAGItem);
	QTreeWidgetItem* fragShape = NewPartEditorItem(QString::fromLocal8Bit("形状"));
	m_criterionFRAGItem->addChild(fragShape);
	/*IWComboBox* */comboBox = new IWComboBox(fragShape);
	comboBox->addItems(QStringList() << QString::fromLocal8Bit("长方体") << QString::fromLocal8Bit("圆柱体"));
	fragShape->setData(1, VisibleRole, 0);
	fragShape->setData(1, ItemWidgetRole, (unsigned)comboBox);
	setItemWidget(fragShape, 1, comboBox);
	/*QTreeWidgetItem* */mass = NewPartEditorItem(QString::fromLocal8Bit("质量(g)"));
	m_criterionFRAGItem->addChild(mass);
	mass->setData(1, VisibleRole, 0);
	/*QDoubleSpinBox* */box = new IWDoubleSpinBox(mass);
	box->setMaximum(10000);
	mass->setData(1, ItemWidgetRole, (unsigned)box);
	setItemWidget(mass, 1, box);

	/*QTreeWidgetItem* */vel = NewPartEditorItem(QString::fromLocal8Bit("速度(m/s)"));
	m_criterionFRAGItem->addChild(vel);
	vel->setData(1, VisibleRole, 0);
	/*QDoubleSpinBox* */box = new IWDoubleSpinBox(vel);
	box->setMaximum(10000);
	vel->setData(1, ItemWidgetRole, (unsigned)box);
	setItemWidget(vel, 1, box);

	QTreeWidgetItem* num = NewPartEditorItem(QString::fromLocal8Bit("枚数"));
	m_criterionFRAGItem->addChild(num);
	num->setData(1, VisibleRole, 0);
	QSpinBox* box_2 = new IWSpinBox(num);
	box_2->setMaximum(10000);
	num->setData(1, ItemWidgetRole, (unsigned)box_2);
	setItemWidget(num, 1, box_2);
	//冲击波
	m_criterionSWItem = NewPartEditorItem(QString::fromLocal8Bit("冲击波判据"));
	m_criterionItem->addChild(m_criterionSWItem);
	QTreeWidgetItem* OP = NewPartEditorItem(QString::fromLocal8Bit("超压"));
	m_criterionSWItem->addChild(OP);
	setItemWidget(OP, 1, new QRadioButton);
	QTreeWidgetItem* threshold = NewPartEditorItem(QString::fromLocal8Bit("阀值(MPa)"));
	OP->addChild(threshold);
	threshold->setData(1, VisibleRole, 0);
	/*QDoubleSpinBox* */box = new IWDoubleSpinBox(threshold);
	box->setMaximum(10000);
	threshold->setData(1, ItemWidgetRole, (unsigned)box);
	setItemWidget(threshold, 1, box);
	QTreeWidgetItem* SI = NewPartEditorItem(QString::fromLocal8Bit("比冲量"));
	m_criterionSWItem->addChild(SI);
	setItemWidget(SI, 1, new QRadioButton);
	/*QTreeWidgetItem* */threshold = NewPartEditorItem(QString::fromLocal8Bit("阀值(N*s/mm^2)"));
	SI->addChild(threshold);
	threshold->setData(1, VisibleRole, 0);
	/*QDoubleSpinBox* */box = new IWDoubleSpinBox(threshold);
	box->setMaximum(10000);
	threshold->setData(1, ItemWidgetRole, (unsigned)box);
	setItemWidget(threshold, 1, box);
	QTreeWidgetItem* OPSI = NewPartEditorItem(QString::fromLocal8Bit("超压比冲量联合"));
	m_criterionSWItem->addChild(OPSI);
	setItemWidget(OPSI, 1, new QRadioButton);
	QTreeWidgetItem* opValue = NewPartEditorItem(QString::fromLocal8Bit("超压值(MPa)"));
	OPSI->addChild(opValue);
	opValue->setData(1, VisibleRole, 0);
	/*QDoubleSpinBox* */box = new IWDoubleSpinBox(opValue);
	box->setMaximum(10000);
	opValue->setData(1, ItemWidgetRole, (unsigned)box);
	setItemWidget(opValue, 1, box);
	QTreeWidgetItem* siValue = NewPartEditorItem(QString::fromLocal8Bit("比冲量值(N*s/mm^2)"));
	OPSI->addChild(siValue);
	siValue->setData(1, VisibleRole, 0);
	/*QDoubleSpinBox* */box = new IWDoubleSpinBox(siValue);
	box->setMaximum(10000);
	siValue->setData(1, ItemWidgetRole, (unsigned)box);
	setItemWidget(siValue, 1, box);
	/*QTreeWidgetItem* */threshold = NewPartEditorItem(QString::fromLocal8Bit("阀值"));
	OPSI->addChild(threshold);
	threshold->setData(1, VisibleRole, 0);
	/*QDoubleSpinBox* */box = new IWDoubleSpinBox(threshold);
	box->setMaximum(10000);
	threshold->setData(1, ItemWidgetRole, (unsigned)box);
	setItemWidget(threshold, 1, box);

	m_criterionEMTItem->setHidden(true);
	m_criterionKEItem->setHidden(true);
	m_criterionFRAGItem->setHidden(true);
	m_criterionSWItem->setHidden(true);
	return m_criterionItem;
}
QTreeWidgetItem* PartEditor::CreateGeometryItem()
{
	QTreeWidgetItem* item = NewPartEditorItem(QString::fromLocal8Bit("等效几何体"));
	addTopLevelItem(item);
	QTreeWidgetItem* shape = NewPartEditorItem(QString::fromLocal8Bit("形状"));
	item->addChild(shape);
	IWComboBox* comboBox = new IWComboBox(shape);
	comboBox->addItems(QStringList() << QString::fromLocal8Bit("长方体") << QString::fromLocal8Bit("圆柱体"));
	shape->setData(1, VisibleRole, 0);
	shape->setData(1, ItemWidgetRole, (unsigned)comboBox);
	setItemWidget(shape, 1, comboBox);
	connect(comboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(OnGeometryTypeChanged(const QString&)));

	QTreeWidgetItem* coord = NewPartEditorItem(QString::fromLocal8Bit("中心坐标"));
	item->addChild(coord);
	{
		QTreeWidgetItem* x = NewPartEditorItem(QString::fromLocal8Bit("X"));
		coord->addChild(x);
		x->setData(1, VisibleRole, 0);
		QDoubleSpinBox* box = new IWDoubleSpinBox(x);
		box->setMaximum(1000000);
		x->setData(1, ItemWidgetRole, (unsigned)box);
		setItemWidget(x, 1, box);

		QTreeWidgetItem* y = NewPartEditorItem(QString::fromLocal8Bit("Y"));
		coord->addChild(y);
		y->setData(1, VisibleRole, 0);
		/*QDoubleSpinBox* */box = new IWDoubleSpinBox(y);
		box->setMaximum(1000000);
		y->setData(1, ItemWidgetRole, (unsigned)box);
		setItemWidget(y, 1, box);

		QTreeWidgetItem* z = NewPartEditorItem(QString::fromLocal8Bit("Z"));
		coord->addChild(z);
		z->setData(1, VisibleRole, 0);
		/*QDoubleSpinBox* */box = new IWDoubleSpinBox(z);
		box->setMaximum(1000000);
		z->setData(1, ItemWidgetRole, (unsigned)box);
		setItemWidget(z, 1, box);
	}
	QTreeWidgetItem* coordDsb = NewPartEditorItem(QString::fromLocal8Bit("坐标系描述"));
	item->addChild(coordDsb);
	QTreeWidgetItem* size = NewPartEditorItem(QString::fromLocal8Bit("尺寸"));
	item->addChild(size);
	m_geometrySizeItem = size;
	{
		QTreeWidgetItem* thickness = NewPartEditorItem(QString::fromLocal8Bit("厚度(0:实心)"));
		size->addChild(thickness);
		thickness->setData(1, VisibleRole, 0);
		QDoubleSpinBox* box = new IWDoubleSpinBox(thickness);
		thickness->setData(1, ItemWidgetRole, (unsigned)box);
		setItemWidget(thickness, 1, box);
		OnGeometryTypeChanged(shape->text(1));
	}
	QTreeWidgetItem* color = NewPartEditorItem(QString::fromLocal8Bit("颜色"));
	item->addChild(color);
	{
		setItemWidget(color, 1, new QtColorEditWidget);
	}
	m_geometryTypeItem = shape;
	m_geometryCoorItem = coord;
	m_geometryCoorDsbItem = coordDsb;
	m_geometrySizeItem = size;
	m_geometryColorItem = color;
	return item;
}

void PartEditor::CreateMaterialTypeAndNameItems(QTreeWidgetItem* parent)
{
	QTreeWidgetItem* type = NewPartEditorItem(QString::fromLocal8Bit("材料种类"));
	parent->addChild(type);
	type->setData(1, VisibleRole, 0);
	IWComboBox* comboBoxType = new IWComboBox(type);
	{
		foreach(QString key, m_materials.keys())
			comboBoxType->addItem(key);
		type->setData(1, ItemWidgetRole, (unsigned)comboBoxType);
		setItemWidget(type, 1, comboBoxType);
		connect(comboBoxType, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(OnMaterialTypeChanged(const QString&)));
	}
	QTreeWidgetItem* name = NewPartEditorItem(QString::fromLocal8Bit("材料名称"));
	parent->addChild(name);
	name->setData(1, VisibleRole, 0);
	IWComboBox* comboBoxName = new IWComboBox(name);
	{
		name->setData(1, ItemWidgetRole, (unsigned)comboBoxName);
		setItemWidget(name, 1, comboBoxName);
	}
	if(comboBoxType->count()>0)
	{
		comboBoxType->setItemData(0, (unsigned)comboBoxName);
		comboBoxType->setCurrentIndex(-1);
	}
}
void PartEditor::OnMaterialTypeChanged(const QString& type)
{
	QComboBox* comboBox = dynamic_cast<QComboBox*>(sender());
	if(comboBox && type.size()>0)
	{
		QComboBox* comboBoxName = (QComboBox*)(comboBox->itemData(0).toUInt());
		if(comboBoxName)
		{
			comboBoxName->clear();
			comboBoxName->addItems(m_materials[type]);
		}
	}
}
void PartEditor::OnGeometryTypeChanged(const QString& text)
{
	if(m_geometrySizeItem)
	{
		while(m_geometrySizeItem->childCount()>1)
			m_geometrySizeItem->removeChild(m_geometrySizeItem->child(1));
		QStringList sizeParam;
		if(text == QString::fromLocal8Bit("圆柱体"))
			sizeParam << QString::fromLocal8Bit("半径") << QString::fromLocal8Bit("高");
		else if(text == QString::fromLocal8Bit("长方体"))
			sizeParam << QString::fromLocal8Bit("长") << QString::fromLocal8Bit("宽") << QString::fromLocal8Bit("高");
		foreach(QString text, sizeParam)
		{
			QTreeWidgetItem* param = NewPartEditorItem(text);
			m_geometrySizeItem->addChild(param);
			param->setData(1, VisibleRole, 0);
			QDoubleSpinBox* box = new IWDoubleSpinBox(param);
			box->setMaximum(100000);
			param->setData(1, ItemWidgetRole, (unsigned)box);
			setItemWidget(param, 1, box);
		}
	}
}
void PartEditor::OnAddCriterion(const QString& text)
{
	if(0 == m_criterions.indexOf(text) && m_criterionEMTItem)
	{
		m_criterionEMTItem->setHidden(false);
	}
	else if(1 == m_criterions.indexOf(text) && m_criterionKEItem)
	{
		m_criterionKEItem->setHidden(false);
	}
	else if(2 == m_criterions.indexOf(text) && m_criterionFRAGItem)
	{
		m_criterionFRAGItem->setHidden(false);
	}
	else if(3 == m_criterions.indexOf(text) && m_criterionSWItem)
	{
		m_criterionSWItem->setHidden(false);
	}
}
void PartEditor::OnDeleteCriterion(const QString& text)
{
	if(0 == m_criterions.indexOf(text) && m_criterionEMTItem)
	{
		m_criterionEMTItem->setHidden(true);
	}
	else if(1 == m_criterions.indexOf(text) && m_criterionKEItem)
	{
		m_criterionKEItem->setHidden(true);
	}
	else if(2 == m_criterions.indexOf(text) && m_criterionFRAGItem)
	{
		m_criterionFRAGItem->setHidden(true);
	}
	else if(3 == m_criterions.indexOf(text) && m_criterionSWItem)
	{
		m_criterionSWItem->setHidden(true);
	}
}
void PartEditor::OnItemChanged ( QTreeWidgetItem * item, int column )
{
	if(item == m_nameItem && column == 1)
	{
		QString newName = m_nameItem->text(1);
		if(g_name != std::string(newName.toLocal8Bit().data()))
		{
			emit partNameChanged(m_nameItem->text(1));
			g_name = newName.toLocal8Bit().data();
		}
	}
}