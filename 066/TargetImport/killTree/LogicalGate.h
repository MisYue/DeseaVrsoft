
#ifndef LOGICALGATE_H_
#define LOGICALGATE_H_

#include <QApplication>
#include <QSet>
#include <QGraphicsItem>

class Link;

class LogicalGate
	:public QGraphicsItem
{

	Q_DECLARE_TR_FUNCTIONS(LogicalGate);
public:
	LogicalGate(int nDoorType);
	~LogicalGate(); 

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

protected:
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
	virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value);
	virtual void	mousePressEvent ( QGraphicsSceneMouseEvent * event );
	bool sceneEventFilter ( QGraphicsItem * watched, QEvent * event );
private:
	QRectF outlineRect() const;
	int roundness(double size) const;

	QSet<Link*> myLinks;
	QString myText;
	QColor myTextColor;
	QColor myOutlineColor;
	QColor myBackgroundColor;
	int myDoorType;

};

#endif	//LOGICALGATE_H_