//***************************************
//	创建时间:	2015:11:8   17:35
//	文件名称: 	DDTreeWidget.h
//	文件作者:	岳群磊
//	
//	功能说明:	定义拖拽功能树部件
//***************************************

#pragma once
#include <QtWidgets>

class TreeItemMimeData : public QMimeData
{
	Q_OBJECT
public:
	TreeItemMimeData() : QMimeData()
	{
		m_pDragItem = NULL;
	}
	~TreeItemMimeData()
	{
	}
	void SetDragData(QString mimeType, QTreeWidgetItem* pItem)
	{
		m_format << mimeType;
		m_pDragItem = pItem;
	}
	QStringList formats()const
	{
		return m_format;
	}
	const QTreeWidgetItem* DragItemData()const
	{
		return m_pDragItem;
	}
protected:
	QVariant retrieveData(const QString& mimeType, QVariant::Type preferredType)const
	{
		if(mimeType == "ItemMimeData")
		{
			return m_pDragItem;
		}
		else
		{
			return QMimeData::retrieveData(mimeType, preferredType);
		}
	}
private:
	const QTreeWidgetItem* m_pDragItem;
	QStringList m_format;
};

//鼠标左键在同一个控件中移动数据
//鼠标右键在两个控件中移动数据

class DDTreeWidget : public QTreeWidget
{
	Q_OBJECT
public:
	DDTreeWidget(QWidget* parent = NULL);
	~DDTreeWidget();
	void SetAllowMoveaway(bool allowMoveaway)
	{
		m_allowMoveaway = allowMoveaway;
	}
	bool GetAllowMoveaway()
	{
		return m_allowMoveaway;
	}
signals:
	void addItem(QTreeWidgetItem* item);
protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);
protected:
	QPoint m_startDragPoint;
	virtual void performDrag();
	bool m_allowMoveaway;
};
