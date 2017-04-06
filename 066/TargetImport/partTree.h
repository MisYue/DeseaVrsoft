#pragma once
#include "DDTreeWidget.h"

class PartTree : public DDTreeWidget
{
	Q_OBJECT
public:
	PartTree(QWidget* parent = NULL);
	~PartTree();
signals:
	void addItem(QTreeWidgetItem* item);
protected:
	//void dragEnterEvent(QDragEnterEvent *event);
	//void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);
	virtual void performDrag();

};
