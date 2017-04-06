//***************************************
//	创建时间:	2015:11:7   17:36
//	文件名称: 	KillTreeEditor.cpp
//	文件作者:	岳群磊
//	
//	功能说明:	实现毁伤树编辑器
//***************************************

#include "KillTreeEditor.h"
#include "DDTreeWidget.h"
#include "itemWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QSpacerItem>
#include <QFile>
#include <QTextStream>
#include <QCheckBox>

static QTreeWidgetItem* g_item = NULL;
static int g_column = -1;

KillTreeEditor::KillTreeEditor(QWidget* parent /* = NULL */)
: QMainWindow(parent),
m_currentKillTreeItem(NULL)

{
	QHBoxLayout* hlayout = new QHBoxLayout;
	QLabel* label = new QLabel(QString::fromLocal8Bit("毁伤等级"));
	hlayout->addWidget(label);
	m_comboBox = new QComboBox;
	m_comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	hlayout->addWidget(m_comboBox);
	m_add = new QToolButton;
	QIcon icon1;
	icon1.addFile(QString::fromUtf8(":/MainWindow/Resources/images/add.PNG"), QSize(), QIcon::Normal, QIcon::Off);
	m_add->setIcon(icon1);
	m_add->setIconSize(QSize(30, 30));
	m_add->setAutoRaise(true);
	m_add->setMinimumSize(30, 30);
	m_add->setMaximumSize(30, 30);
	hlayout->addWidget(m_add);
	m_delete = new QToolButton;
	QIcon icon2;
	icon2.addFile(QString::fromUtf8(":/MainWindow/Resources/images/delete.PNG"), QSize(), QIcon::Normal, QIcon::Off);
	m_delete->setIcon(icon2);
	m_delete->setIconSize(QSize(30, 30));
	m_delete->setAutoRaise(true);
	m_delete->setMinimumSize(30, 30);
	m_delete->setMaximumSize(30, 30);
	hlayout->addWidget(m_delete);
	QVBoxLayout* vlayout = new QVBoxLayout;
	vlayout->addLayout(hlayout);
	m_killTree = new DDTreeWidget;
	m_killTree->SetAllowMoveaway(false);
	vlayout->addWidget(m_killTree);
	QHBoxLayout* hlayout2 = new QHBoxLayout;
	m_addItem = new QToolButton;
	m_addItem->setIcon(icon1);
	m_addItem->setIconSize(QSize(30, 30));
	m_addItem->setAutoRaise(true);
	m_addItem->setMinimumSize(30, 30);
	m_addItem->setMaximumSize(30, 30);
	hlayout2->addWidget(m_addItem);
	m_addChildItem = new QToolButton;
	QIcon icon3;
	icon3.addFile(QString::fromUtf8(":/MainWindow/Resources/images/addChild.PNG"), QSize(), QIcon::Normal, QIcon::Off);
	m_addChildItem->setIcon(icon3);
	m_addChildItem->setIconSize(QSize(30, 30));
	m_addChildItem->setAutoRaise(true);
	m_addChildItem->setMinimumSize(30, 30);
	m_addChildItem->setMaximumSize(30, 30);
	hlayout2->addWidget(m_addChildItem);
	m_deleteItem = new QToolButton;
	m_deleteItem->setIcon(icon2);
	m_deleteItem->setIconSize(QSize(30, 30));
	m_deleteItem->setAutoRaise(true);
	m_deleteItem->setMinimumSize(30, 30);
	m_deleteItem->setMaximumSize(30, 30);

	hlayout2->addWidget(m_deleteItem);
	QSpacerItem* spacer =  new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	hlayout2->addItem(spacer);
	vlayout->addLayout(hlayout2);
	QWidget* central = new QWidget;
	central->setLayout(vlayout);
	setCentralWidget(central);
	m_killGrade.push_back(QString::fromLocal8Bit("五级"));
	m_killGrade.push_back(QString::fromLocal8Bit("四级"));
	m_killGrade.push_back(QString::fromLocal8Bit("三级"));
	m_killGrade.push_back(QString::fromLocal8Bit("二级"));
	m_killGrade.push_back(QString::fromLocal8Bit("一级"));
	m_comboBox->addItems(m_killGrade);

	QStringList header;
	header << QString::fromLocal8Bit("事件           ") << QString::fromLocal8Bit("毁伤权重") << QString::fromLocal8Bit("逻辑门");
	m_killTree->setHeaderLabels(header);
	m_killTree->resizeColumnToContents(0);
	m_addChildItem->setEnabled(false);
	m_addItem->setEnabled(false);
	m_deleteItem->setEnabled(false);

	connect(m_add, SIGNAL(clicked()), this, SLOT(OnAddKillTree()));
	connect(m_delete, SIGNAL(clicked()), this, SLOT(OnDeleteKillTree()));
	connect(m_comboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(OnValueChanged(const QString&)));
	connect(m_killTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(OnItemClicked(QTreeWidgetItem*, int)));
	connect(m_addItem, SIGNAL(clicked()), this, SLOT(OnAddItem()));
	connect(m_addChildItem, SIGNAL(clicked()), this, SLOT(OnAddChildItem()));
	connect(m_deleteItem, SIGNAL(clicked()), this, SLOT(OnDeleteItem()));
	connect(m_killTree, SIGNAL(addItem(QTreeWidgetItem*)), this, SLOT(OnAddItem(QTreeWidgetItem*)));
	connect(m_killTree, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(OnItemChanged(QTreeWidgetItem*, int)));
	connect(m_killTree, SIGNAL(/*itemClicked*/itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(EditorItemClicked(QTreeWidgetItem*, int)));
	connect(m_killTree, SIGNAL(itemClicked/*itemDoubleClicked*/(QTreeWidgetItem*,int)), this, SLOT(EditorClicked(QTreeWidgetItem*, int)));
	connect(m_killTree, SIGNAL(clicked ( const QModelIndex &)), this, SLOT(OnTreeWidgetClicked ( const QModelIndex &)));

	connect(m_killTree, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(EditorItemExpanded(QTreeWidgetItem*)));
}
void KillTreeEditor::Reset()
{
	foreach(QTreeWidgetItem* item, m_killTreeItem)
	{
		int index = m_killTree->indexOfTopLevelItem(item);
		m_killTree->takeTopLevelItem(index);
	}
	m_killTreeItem.clear();
	m_killTreeText.clear();
	emit KillTreeTextChanged(m_killTreeText);
	m_currentKillTreeItem = NULL;
	m_add->setEnabled(true);
	m_delete->setEnabled(false);
	m_comboBox->setCurrentIndex(0);
	m_addChildItem->setEnabled(false);
	m_deleteItem->setEnabled(false);
	m_addItem->setEnabled(false);
}
void KillTreeEditor::OnAddKillTree()
{
	QString text = m_comboBox->currentText();
	if(m_currentKillTreeItem)
		m_currentKillTreeItem->setHidden(true);
	QTreeWidgetItem* item = new QTreeWidgetItem;
	item->setText(0, text);
	m_killTree->addTopLevelItem(item);
	m_killTreeItem.insert(text, item);
	m_currentKillTreeItem = item;
	m_add->setEnabled(false);
	m_delete->setEnabled(true);
}
void KillTreeEditor::OnDeleteKillTree()
{
	QString text = m_comboBox->currentText();
	QMap<QString, QTreeWidgetItem*>::iterator iter = m_killTreeItem.find(text);
	if(iter != m_killTreeItem.end())
	{
		int index = m_killTree->indexOfTopLevelItem(iter.value());
		m_killTree->takeTopLevelItem(index);
		m_killTreeItem.erase(iter);
		m_add->setEnabled(true);
		m_delete->setEnabled(false);
		m_addChildItem->setEnabled(false);
		m_deleteItem->setEnabled(false);
		m_addItem->setEnabled(false);
	}
}
void KillTreeEditor::OnValueChanged(const QString& text)
{
	QMap<QString, QTreeWidgetItem*>::iterator iter = m_killTreeItem.find(text);
	bool exist = (iter != m_killTreeItem.end());
	m_add->setEnabled(!exist);
	m_delete->setEnabled(exist);
	if(m_currentKillTreeItem)
		m_currentKillTreeItem->setHidden(true);
	if(exist)
	{
		iter.value()->setHidden(false);
		m_currentKillTreeItem = iter.value();
		m_addChildItem->setEnabled(false);
		m_addItem->setEnabled(false);
		m_deleteItem->setEnabled(false);
	}
	UpdateKillTreeText();
}

void KillTreeEditor::OnItemClicked(QTreeWidgetItem* item, int column)
{
	QString text = item->text(0);
	bool isPart = m_partsName.contains(text);
	m_addChildItem->setEnabled(!isPart);
	bool isTop = item->parent() == NULL ? true : false;
	m_addItem->setEnabled(!isTop);
	m_deleteItem->setEnabled(!isTop);
}
void KillTreeEditor::OnAddItem()
{
	QList<QTreeWidgetItem*> items = m_killTree->selectedItems();
	if(items.size() == 1)
	{
		QTreeWidgetItem* item = items[0];
		QTreeWidgetItem* parent = item->parent();
		if(parent)
		{
			QTreeWidgetItem* itemNew = new QTreeWidgetItem;
			int index = parent->indexOfChild(item)+1;
			parent->insertChild(index, itemNew);
			itemNew->setText(0, QString::fromLocal8Bit("新事件"));
			OnAddItem(itemNew);
			parent->setExpanded(true);
			UpdateKillTreeText();
		}
	}
}
void KillTreeEditor::OnDeleteItem()
{
	QList<QTreeWidgetItem*> items = m_killTree->selectedItems();
	if(items.size() == 1)
	{
		QTreeWidgetItem* item = items[0];
		QTreeWidgetItem* parent = item->parent();
		if(parent)
		{
			parent->removeChild(item);
			UpdateKillTreeText();
		}
	}
}
void KillTreeEditor::OnAddChildItem()
{
	QList<QTreeWidgetItem*> items = m_killTree->selectedItems();
	if(items.size() == 1)
	{
		QTreeWidgetItem* item = items[0];
		QTreeWidgetItem* itemNew = new QTreeWidgetItem;
		itemNew->setText(0, QString::fromLocal8Bit("新事件"));
		item->insertChild(item->childCount(), itemNew);
		OnAddItem(itemNew);
		item->setExpanded(true);
		UpdateKillTreeText();
	}
}

void KillTreeEditor::UpdateKillTreeText()
{
	QString killTreeText;
	QString text = m_comboBox->currentText();
	QMap<QString, QTreeWidgetItem*>::iterator iter = m_killTreeItem.find(text);
	if(iter != m_killTreeItem.end())
	{
		m_killTreeVector.clear();
		UpdateKillTreeVector(iter.value(), 0);
		//killTreeText.sprintf("%s\n\n", iter.key());
		killTreeText += QString("%1\n").arg(iter.key());
		for(int i=0; i<m_killTreeVector.size(); ++i)
		{
			foreach(KEVENT kevnt, m_killTreeVector[i])
			{
				killTreeText += QString("%1    %2      %3   %4   %5  %6\n").arg(i+1).arg(kevnt.name).arg(kevnt.name).arg(kevnt.childCount).arg(kevnt.logic).arg(kevnt.weight);
			}
			killTreeText += "\n";
		}
	}
	else
	{
		killTreeText = "";
	}
	m_killTreeText = killTreeText;
	emit KillTreeTextChanged(killTreeText);
}

void KillTreeEditor::UpdateKillTreeVector(const QTreeWidgetItem* item, int level)
{
	int childCount = item->childCount();
	QString text = item->text(0);
	KEVENT kevent;
	kevent.name = text;
	kevent.logic = 0;
	kevent.logic = childCount > 0 ? 1 : 0;
	kevent.weight = item->text(1).toDouble();
	if(childCount > 0)
	{
		if(QString::fromLocal8Bit("或") == item->text(2))
			kevent.logic = 2;
	}
	kevent.childCount = childCount;
	int levels = m_killTreeVector.size();
	if(levels > level)
	{
		m_killTreeVector[level].push_back(kevent);
	}
	else
	{
		QList<KEVENT> list;
		list.push_back(kevent);
		m_killTreeVector.push_back(list);
	}
	if(childCount>0)
	{
		for(int i=0; i<childCount; ++i)
			UpdateKillTreeVector(item->child(i), level+1);
	}
}

void KillTreeEditor::OnAddItem(QTreeWidgetItem* item)
{
	QDoubleSpinBox* box = new IWDoubleSpinBox(item, 1);
	box->setMaximum(1);
	box->setSingleStep(0.1);
	box->setValue(1.0);
	item->setData(1, VisibleRole, 0);
	item->setData(1, ItemWidgetRole, (unsigned)box);
	m_killTree->setItemWidget(item, 1, box);
	QString eventName = item->text(0);
	if(!m_partsName.contains(eventName))
	{
		IWComboBox* comboBox = new IWComboBox(item, 2);
		comboBox->addItems(QStringList() << QString::fromLocal8Bit("与") << QString::fromLocal8Bit("或"));
		item->setData(2, VisibleRole, 0);
		item->setData(2, ItemWidgetRole, (unsigned)comboBox);
		m_killTree->setItemWidget(item, 2, comboBox);
		IWLineText* lineText = new IWLineText(item, 0);
		lineText->setText(eventName);
		item->setData(0, VisibleRole, 0);
		item->setData(0, ItemWidgetRole, (unsigned)lineText);
		m_killTree->setItemWidget(item, 0, lineText);
	}
	UpdateKillTreeText();
}

void KillTreeEditor::OnItemChanged(QTreeWidgetItem* item, int column)
{
	if(column == 0 || column == 2)
		UpdateKillTreeText();
}


void KillTreeEditor::EditorItemClicked ( QTreeWidgetItem * item, int column )
{
	if(g_item == item && column == g_column)
		return ;
	if(g_item && !g_item->isHidden())
	{
		QWidget* widget = (QWidget*)g_item->data(g_column, ItemWidgetRole).toUInt();
		if(widget)
		{
			widget->hide();
			g_item->setData(g_column, VisibleRole, 0);
		}
		g_item = NULL;
		g_column = -1;
	}
	if(!item->isHidden())
	{
		QWidget* widget = (QWidget*)item->data(column, ItemWidgetRole).toUInt();
		if(widget)
		{
			item->setData(column, VisibleRole, 1);
			if(NULL == m_killTree->itemWidget(item, column))
				m_killTree->setItemWidget(item, column, widget);
			else
				widget->show();
			g_item = item;
			g_column = column;
		}
	}
}
void KillTreeEditor::EditorClicked ( QTreeWidgetItem * item, int column )
{
	if(g_item == item && column == g_column)
		return ;
	if(g_item && !g_item->isHidden())
	{
		QWidget* widget = (QWidget*)g_item->data(g_column, ItemWidgetRole).toUInt();
		if(widget)
		{
			widget->hide();
			g_item->setData(g_column, VisibleRole, 0);
		}
		g_item = NULL;
		g_column = -1;
	}
}

void KillTreeEditor::OnTreeWidgetClicked ( const QModelIndex & index)
{

}

void KillTreeEditor::EditorItemExpanded(QTreeWidgetItem* item)
{
	if(item->childCount()==0)
	{
		for(int i=0; i<m_killTree->columnCount(); ++i)
		{
			QWidget* widget = (QWidget*)item->data(i, ItemWidgetRole).toUInt();
			if(widget && m_killTree->itemWidget(item, i) && !dynamic_cast<QCheckBox*>(widget))
			{
				item->setData(i, VisibleRole, 0);
				if(g_item == item)
				{
					g_item = NULL;
					g_column = -1;
				}
			}
		}
	}
	else
	{
		for(int i=0, n = item->childCount(); i<n; ++i)
			EditorItemExpanded(item->child(i));
	}
}
void KillTreeEditor::GetTargetKillTree(TIMP::TargetKillTree& killTree)
{

}
void KillTreeEditor::UpdateKillTree()
{
	if(m_killTreeText.isEmpty())
		return ;
	QTextStream in(&m_killTreeText);
	QString grade;
	in >> grade;
	m_comboBox->setCurrentIndex(m_comboBox->findText(grade));
	OnAddKillTree();
	QTreeWidgetItem* rootItem = m_killTreeItem[grade];
	int layer, index, childCount, logicType;
	QString code, name;
	double weight;
	struct PartGroup
	{
		int logicType;
		int childCount;
		double weight;
		QString name;
		QTreeWidgetItem* item;
		PartGroup(int logicType_, int childCount_, double weight_, QString name_)
			: logicType(logicType_), childCount(childCount_), weight(weight_), name(name_)
		{
			item = new QTreeWidgetItem;
			item->setText(0, name);
			item->setText(1, QString::number(weight));
			if(childCount > 0)
				item->setText(2, logicType==1?QString::fromLocal8Bit("与") : QString::fromLocal8Bit("或"));
		}
	};
	std::vector<std::vector<PartGroup> > groups;
	std::map<QString, QTreeWidgetItem*> items;
	while(!in.atEnd())
	{
		in >> layer >> code >> name >> childCount >> logicType >> weight;
		if(in.status() != QTextStream::Ok)
			continue;
		if(groups.size()<layer)
		{
			std::vector<PartGroup> parts;
			parts.push_back(PartGroup(logicType, childCount, weight, name));
			groups.push_back(parts);
		}
		else
		{
			groups[layer-1].push_back(PartGroup(logicType, childCount, weight, name));
		}
	}
	for(int i=1; i<groups.size(); ++i)
	{
		int index = 0;
		for(int j=0; j<groups[i].size(); ++j)
		{
			PartGroup& partGroup = groups[i][j];
			if(i==1)
				rootItem->addChild(partGroup.item);
			int childCount = partGroup.childCount;
			QString logic = partGroup.logicType==1?QString::fromLocal8Bit("与") : QString::fromLocal8Bit("或");
			if(childCount > 0)
			{
				SetWeightAndLogicItem(partGroup.item, partGroup.weight, logic, false);
				std::vector<PartGroup>& vparts = groups[i+1];
				for(int ii=0; ii<childCount; ++ii)
				{
					partGroup.item->addChild(vparts[index+ii].item);
				}
				index += childCount;
			}
			else
			{
				m_partsName.push_back(partGroup.name);
				SetWeightAndLogicItem(partGroup.item, partGroup.weight, logic, true);
			}
		}
	}
	m_comboBox->setCurrentIndex(m_comboBox->findText(grade));
	m_killTree->expandAll();
	UpdateKillTreeText();
}



void KillTreeEditor::SetWeightAndLogicItem(QTreeWidgetItem* item, double weight, const QString& logic, bool leaf)
{
	QDoubleSpinBox* box = new IWDoubleSpinBox(item, 1);
	box->setMaximum(1);
	box->setSingleStep(0.1);
	box->setValue(weight);
	item->setData(1, VisibleRole, 0);
	item->setData(1, ItemWidgetRole, (unsigned)box);
	m_killTree->setItemWidget(item, 1, box);
	if(!leaf)
	{
		IWComboBox* comboBox = new IWComboBox(item, 2);
		comboBox->addItems(QStringList() << QString::fromLocal8Bit("与") << QString::fromLocal8Bit("或"));
		comboBox->setCurrentIndex(comboBox->findText(logic));
		item->setData(2, VisibleRole, 0);
		item->setData(2, ItemWidgetRole, (unsigned)comboBox);
		m_killTree->setItemWidget(item, 2, comboBox);
		IWLineText* lineText = new IWLineText(item, 0);
		QString name = item->text(0);
		lineText->setText(name);
		item->setData(0, VisibleRole, 0);
		item->setData(0, ItemWidgetRole, (unsigned)lineText);
		m_killTree->setItemWidget(item, 0, lineText);
	}
}