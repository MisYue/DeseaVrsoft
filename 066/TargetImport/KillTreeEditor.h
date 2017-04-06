//***************************************
//	创建时间:	2015:11:7   17:36
//	文件名称: 	KillTreeEditor.h
//	文件作者:	岳群磊
//	
//	功能说明:	定义毁伤树编辑器类
//***************************************

#pragma once
#include "targetInfo.h"
#include <QMainWindow>
#include <QTreeWidget>
#include <QComboBox>
#include <QToolButton>
#include <QMap>
#include <QVector>
class DDTreeWidget;

class KillTreeEditor : public QMainWindow
{
	Q_OBJECT
public:
	KillTreeEditor(QWidget* parent = NULL);
	void SetPartsName(const QStringList& partsName)
	{
		m_partsName = partsName;
	}
	void AddPartName(const QString& name)
	{
		m_partsName.push_back(name);
	}
	void DeletePartName(const QString& name)
	{
		int index = m_partsName.indexOf(name);
		if(index >= 0)
		{
			m_partsName.takeAt(index);
		}
	}
	void UpdatePartName(const QString& oldName, const QString& newName)
	{
		int index = m_partsName.indexOf(oldName);
		if(index >= 0)
		{
			m_partsName.replace(index, newName);
			if(m_currentKillTreeItem)
				UpdateItemName(m_currentKillTreeItem, oldName, newName);
		}
	}
	void GetTargetKillTree(TIMP::TargetKillTree& killTree);
	QString GetTargetKillTree()
	{
		UpdateKillTreeText();
		return m_killTreeText;
	}
	void SetTargetKillTree(const QString& text)
	{
		Reset();
		m_killTreeText = text;
		UpdateKillTree();
	}
	void Reset();
public slots:
	void OnAddKillTree();
	void OnDeleteKillTree();
	void OnValueChanged(const QString& text);
	void OnItemClicked(QTreeWidgetItem* item, int column);
	void OnAddItem();
	void OnDeleteItem();
	void OnAddChildItem();
	void OnAddItem(QTreeWidgetItem* item);
	void OnItemChanged(QTreeWidgetItem* item, int column);
	void EditorItemClicked ( QTreeWidgetItem * item, int column );
	void EditorClicked ( QTreeWidgetItem * item, int column );
	void OnTreeWidgetClicked ( const QModelIndex & index);
	void EditorItemExpanded(QTreeWidgetItem* item);
signals:
	void KillTreeTextChanged(const QString& text);
private:
	DDTreeWidget* m_killTree;
	QComboBox* m_comboBox;
	QToolButton* m_add;
	QToolButton* m_delete;
	QStringList m_killGrade;
	QMap<QString, QTreeWidgetItem*> m_killTreeItem;
	QTreeWidgetItem* m_currentKillTreeItem;
	QToolButton* m_addItem;
	QToolButton* m_addChildItem;
	QToolButton* m_deleteItem;
	QStringList m_partsName;
	QString m_killTreeText;
	void UpdateKillTreeText();
	void UpdateKillTree();
	struct KEVENT
	{
		QString name;
		int childCount;
		int logic; //2:或 1:与
		double weight;
	};
	QVector<QList<KEVENT> > m_killTreeVector;
	void UpdateKillTreeVector(const QTreeWidgetItem* item, int level);
	bool UpdateItemName(QTreeWidgetItem* item, const QString& oldName, const QString& newName)
	{
		if(item->childCount()==0)
		{
			if(item->text(0) == oldName)
			{
				item->setText(0, newName);
				return true;
			}
			return false;
		}
		else
		{
			for(int i=0; i<item->childCount(); ++i)
			{
				if(UpdateItemName(item->child(i), oldName, newName))
					return true;
			}
			return false;
		}

	}
	void SetWeightAndLogicItem(QTreeWidgetItem* item, double weight, const QString& logic, bool leaf);
};