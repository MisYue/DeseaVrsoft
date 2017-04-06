//***************************************
//	创建时间:	2015:11:8   17:35
//	文件名称: 	DDTreeWidget.cpp
//	文件作者:	岳群磊
//	
//	功能说明:	实现拖拽功能树部件
//***************************************

#include "DDTreeWidget.h"


DDTreeWidget::DDTreeWidget(QWidget* parent) : QTreeWidget(parent), m_allowMoveaway(true)
{
	this->setSelectionMode(QAbstractItemView::SingleSelection);
	this->setAcceptDrops(true);
	this->setDragEnabled(true);
}

DDTreeWidget::~DDTreeWidget()
{
}

void DDTreeWidget:: mouseMoveEvent(QMouseEvent *event)
{
	if(event->buttons() & Qt::LeftButton)
	{
		int dragDistance = (event->pos() - m_startDragPoint).manhattanLength();
		if(dragDistance > QApplication::startDragDistance())
		{
			performDrag();
		}
	}
	QTreeWidget::mouseMoveEvent(event);
}

void DDTreeWidget:: mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		m_startDragPoint = event->pos();
	}
	QTreeWidget::mousePressEvent(event);
}

void DDTreeWidget:: mouseReleaseEvent(QMouseEvent *event)
{
	QTreeWidget::mouseReleaseEvent(event);
}

void DDTreeWidget:: dragEnterEvent(QDragEnterEvent *event)
{
	QWidget* source = qobject_cast<DDTreeWidget*>(event->source());
	if(source)
	{
		event->accept();
	}
}

void DDTreeWidget:: dragMoveEvent(QDragMoveEvent *event)
{
	QWidget* source = qobject_cast<DDTreeWidget*>(event->source());
	if(source)
	{
		const TreeItemMimeData* pMimeData = dynamic_cast<const TreeItemMimeData*>(event->mimeData());
		if(pMimeData)
		{
			const QTreeWidgetItem* item = pMimeData->DragItemData();
			QTreeWidgetItem* currentItem = this->itemAt(event->pos());
			if(currentItem == item)
			{
				event->ignore();
			}
			else
			{
				setCurrentItem(currentItem);
				event->accept();
			}
		}
		else
		{
			event->ignore();
		}
	}
}

void DDTreeWidget:: dropEvent(QDropEvent *event)
{
	DDTreeWidget* source = qobject_cast<DDTreeWidget*>(event->source());
	if(source)
	{
		if(!source->GetAllowMoveaway() && source != this)
		{
			return ;
		}
		QTreeWidgetItem* currentItem = this->itemAt(event->pos());
		if(currentItem)
		{
			const TreeItemMimeData* pMimeData = dynamic_cast<const TreeItemMimeData*>(event->mimeData());
			if(pMimeData)
			{
				const QTreeWidgetItem* item = pMimeData->DragItemData();
				if(item)
				{
					QTreeWidgetItem* pItem = item->clone();
					if(currentItem != item)
					{
						currentItem->addChild(pItem);
						currentItem->setExpanded(true);
						//setCurrentItem(pItem);
						emit addItem(pItem);
						if(source == this)
							delete item;
					}
				}
			}
		}
	}
}
void DDTreeWidget::performDrag()
{
	QTreeWidgetItem* item = currentItem();
	if(item)
	{
			TreeItemMimeData* mimeData = new TreeItemMimeData;
			mimeData->SetDragData("ItemMimeData", item);
			QDrag* drag = new QDrag(this);
			drag->setMimeData(mimeData);
			drag->exec(Qt::CopyAction);
	}
}
