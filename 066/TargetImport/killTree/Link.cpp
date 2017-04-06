
#include <QPen>
#include "Link.h"
#include "Node.h"
//#include "LogicalGate.h"

Link::Link(QPointF firstPos,QPointF secondPos)
	:firestPoint(firstPos),secondPoint(secondPos)
{
	setColor(Qt::darkRed);
	traceNodes();
}
Link::~Link()
{
}
Node* Link::fromNode() const
{
	return myFromNode;
}
Node* Link::toNode() const
{
	return myToNode;
}

void Link::setColor(const QColor& color)
{
	setPen(QPen(color,1.0));
	
}
QColor Link::color() const
{
	return pen().color();
}

void Link::traceNodes()
{
	setLine(QLineF(firestPoint ,secondPoint));
}


