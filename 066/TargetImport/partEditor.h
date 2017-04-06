#pragma once
#include "TargetInfo.h"
#include <QTreeWidget>
#include <QComboBox>
#include <QMap>
#include <QStringList>
#include <QColor>
#include <string>

using namespace TIMP;
class PartEditor : public QTreeWidget
{
	Q_OBJECT
public:
	PartEditor(QWidget* parent=NULL);
	void SetProperties(const PartExtraInfo& partInfo);
	void GetProperties(PartExtraInfo& partInfo);
	public slots:
		void EditorItemClicked ( QTreeWidgetItem * item, int column );
		void EditorItemCollapsed(QTreeWidgetItem* item);
		void EditorItemExpanded(QTreeWidgetItem* item);
		void OnMaterialTypeChanged(const QString& type);
		void OnGeometryTypeChanged(const QString& text);
		void OnAddCriterion(const QString& text);
		void OnDeleteCriterion(const QString& text);
		void OnItemChanged ( QTreeWidgetItem * item, int column );
signals:
		void partNameChanged(const QString& name);

private:
	void Connect();
	void Init();
	QTreeWidgetItem* CreateMaterialItem();
	void CreateMaterialTypeAndNameItems(QTreeWidgetItem* parent);
	QTreeWidgetItem* CreateDamageCriterionItem();
	QTreeWidgetItem* CreateGeometryItem();
	void SetComoboBoxItemValue(QTreeWidgetItem* item, const std::string& value);
	void SetDoubleItemValue(QTreeWidgetItem* item, const std::string& value);
	void SetIntItemValue(QTreeWidgetItem* item, const std::string& value);
	void SetColortItemValue(QTreeWidgetItem* item, const QColor& color);
	void SetLineEditValue(QTreeWidgetItem* item, const std::string& value);
private:
	QTreeWidgetItem* m_nameItem;
	QTreeWidgetItem* m_codeItem;
	QTreeWidgetItem* m_shellItem;
	QTreeWidgetItem* m_thicknessItem;
	QTreeWidgetItem* m_materialItem;
	QTreeWidgetItem* m_criterionItem;
	QTreeWidgetItem* m_criterionEMTItem;
	QTreeWidgetItem* m_criterionKEItem;
	QTreeWidgetItem* m_criterionFRAGItem;
	QTreeWidgetItem* m_criterionSWItem;
	QTreeWidgetItem* m_geometryTypeItem;
	QTreeWidgetItem* m_geometryCoorItem;
	QTreeWidgetItem* m_geometryCoorDsbItem;
	QTreeWidgetItem* m_geometrySizeItem;
	QTreeWidgetItem* m_geometryColorItem;
	QMap<QString, QStringList> m_materials;
	QStringList m_criterions;
};
