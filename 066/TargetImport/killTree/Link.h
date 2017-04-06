#ifndef LINK_H_
#define LINK_H_

#include <QGraphicsLineItem>

class Node;

class Link
	:public QGraphicsLineItem
{
public:
	Link(QPointF firstPos,QPointF secondPos);
	~Link();

	Node* fromNode() const;
	Node* toNode() const;

	void setColor(const QColor& color);
	QColor color() const;

	void traceNodes();
protected:
	 
	//virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
private:
	Node* myFromNode;
	Node* myToNode;
	QPointF firestPoint;
	QPointF secondPoint;

};

#endif