#ifndef NODE_H_
#define NODE_H_

#include <QApplication>
#include <QSet>
#include <QGraphicsItem>
#include "../structHead.h"

class Link;

class Node : public QGraphicsItem
{
	Q_DECLARE_TR_FUNCTIONS(Node);
public:
	Node();
	~Node(); 

	QString text() const;
	QColor textColor() const;
	QColor outlineColor() const;
	QColor backgroundColor() const;
	void setText(const QString& text);
	void setTextColor(const QColor& color);
	void setOutlineColor(const QColor& color);
	void setBackgroundColor(const QColor& color);

	void addLink(Link* link);
	void removeLink(Link* link);

	virtual QRectF boundingRect() const;
	virtual QPainterPath shape() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

	void SetNodeSubEvent(int nSubEventNum)	{ mySubEventNum = nSubEventNum; }
	void SetKillTreeInfo(KTInfo ktInfo)		{ myktInfo = ktInfo; }

protected:
	//	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
	//	virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value);

private:
	QRectF outlineRect() const;
	int roundness(double size) const;

	QSet<Link*> myLinks;
	QString myText;
	QColor myTextColor;
	QColor myOutlineColor;
	QColor myBackgroundColor;
	int mySubEventNum;
	KTInfo myktInfo;
};

#endif