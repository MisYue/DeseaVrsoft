#include "PartTree.h"
#include <QMouseEvent>
#include <QApplication>

PartTree::PartTree(QWidget* parent) : DDTreeWidget(parent)
{
	m_CrlPressed = false;
}

PartTree::~PartTree()
{
}

//void PartTree:: dragEnterEvent(QDragEnterEvent *event)
//{
//	QWidget* source = qobject_cast<PartTree*>(event->source());
//	if(source)
//	{
//		if(m_CrlPressed)
//		{
//			event->setDropAction(Qt::CopyAction);
//		}
//		else
//		{
//			event->setDropAction(Qt::MoveAction);
//		}
//		event->accept();
//	}
//}
//
//void PartTree:: dragMoveEvent(QDragMoveEvent *event)
//{
//	QWidget* source = qobject_cast<PartTree*>(event->source());
//	if(source)
//	{
//		const TreeItemMimeData* pMimeData = (const TreeItemMimeData*)(event->mimeData());
//		const QTreeWidgetItem* item = pMimeData->DragItemData();
//		QTreeWidgetItem* currentItem = this->itemAt(event->pos());
//		if(currentItem == item)
//		{
//			event->ignore();
//		}
//		else
//		{
//			setCurrentItem(currentItem);
//			if(m_CrlPressed)
//			{
//				event->setDropAction(Qt::CopyAction);
//			}
//			else
//			{
//				event->setDropAction(Qt::MoveAction);
//			}
//			event->accept();
//		}
//	}
//}
//
void PartTree:: dropEvent(QDropEvent *event)
{
	if(m_bAccept)
	{
		QWidget* source = qobject_cast<PartTree*>(event->source());
		const TreeItemMimeData* pMimeData = dynamic_cast<const TreeItemMimeData*>(event->mimeData());
		if(source && pMimeData)
		{
			const QTreeWidgetItem* item = pMimeData->DragItemData();
			if(item)
			{
				QTreeWidgetItem* pItem = item->clone();
				QTreeWidgetItem* currentItem = this->itemAt(event->pos());
				if(currentItem && (currentItem != item) && indexOfTopLevelItem(currentItem) != -1)
				{
					currentItem->addChild(pItem);
					currentItem->setExpanded(true);
					pItem->setSelected(true);
					emit addItem(pItem);
				}
			}
			if(m_CrlPressed)
			{
				event->setDropAction(Qt::CopyAction);
			}
			else
			{
				event->setDropAction(Qt::MoveAction);
			}
			event->accept();
		}
	}
}
void PartTree::performDrag()
{
	QTreeWidgetItem* item = currentItem();
	if(item && indexOfTopLevelItem(item) == -1)
	{
		TreeItemMimeData* mimeData = new TreeItemMimeData;
		mimeData->SetDragData("ItemMimeData", item);
		QDrag* drag = new QDrag(this);
		drag->setMimeData(mimeData);
		//drag->setPixmap(QPixmap("images/add.png"));
		if(m_CrlPressed)
		{
			drag->exec(Qt::CopyAction);
		}
		else
		{
			drag->exec(Qt::MoveAction);
			delete item;
		}
	}
}