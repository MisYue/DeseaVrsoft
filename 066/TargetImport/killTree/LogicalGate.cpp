#include <QPainter>
#include <QFontMetricsF>
#include <QStyleOptionGraphicsItem>
#include <QInputDialog>
#include <QGraphicsSceneMouseEvent>

#include "LogicalGate.h"
#include "link.h"
LogicalGate::LogicalGate(int nDoorType)
{
	myTextColor=Qt::darkGreen;
	myOutlineColor=Qt::darkBlue;
	myBackgroundColor=Qt::blue;

	myDoorType = nDoorType;
	
	setFlags(ItemIsMovable|ItemIsSelectable);
	myText = "+";
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);
	//setCacheMode(DeviceCoordinateCache);
}

LogicalGate::~LogicalGate()
{
	foreach(Link* link, myLinks)
		delete link;
}

void LogicalGate::setText(const QString& text)
{
	prepareGeometryChange();
	myText=text;
	update();
}

QString LogicalGate::text() const
{
	return myText;
}

void LogicalGate::setTextColor(const QColor& color)
{
	myTextColor=color;
	update();
}

QColor LogicalGate::textColor() const
{
	return myTextColor;
}

void LogicalGate::setOutlineColor(const QColor& color)
{
	myOutlineColor=color;
	update();
}

QColor LogicalGate::outlineColor() const
{
	return myOutlineColor;
}

void LogicalGate::setBackgroundColor(const QColor& color)
{
	myBackgroundColor=color;
	update();
}

QColor LogicalGate::backgroundColor() const
{
	return myBackgroundColor;
}

void LogicalGate::addLink(Link* link)
{
	myLinks.insert(link);
}

void LogicalGate::removeLink(Link* link)
{
	myLinks.remove(link);
}

//计算一个包围节点文字的矩阵
QRectF LogicalGate::boundingRect() const //边界 ，边界区域大于轮廓区域1个像素点
{
	const int Margin=1;
	return outlineRect().adjusted(-Margin,-Margin,Margin,Margin);
}

QPainterPath LogicalGate::shape() const
{
	QPainterPath paintPath;
	QRectF rect=outlineRect();
	paintPath.addRoundedRect(rect,roundness(rect.width()),roundness(rect.height()));
	return paintPath;
}

void LogicalGate::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen pen(myOutlineColor);
	//pen.setWidth(1);

	if (option->state & QStyle::State_Selected)//被选中
	{
		pen.setStyle(Qt::DotLine);
		pen.setWidth(2);
	}

	painter->setPen(pen);
 	QRectF rect= outlineRect();
 	myBackgroundColor.setAlpha(100);
 //	QLinearGradient gradient;
 //	gradient.setStart(rect.topLeft());
 //	gradient.setFinalStop(rect.bottomLeft());
 //	gradient.setColorAt(0.0,Qt::black);
 //	gradient.setColorAt(0.1,myBackgroundColor);
 //	gradient.setColorAt(0.5,Qt::white);
 //	gradient.setColorAt(0.9,myBackgroundColor);
 //	gradient.setColorAt(1,Qt::black);
	//painter->setBrush(gradient);

	switch (myDoorType)
	{
	case 1:
		{
			//////////////////////////////////////////////////////////////////////////
			//与门
		 	QRectF rectangle(0.0, 20.0, 45.0, 80.0);
		 	int startAngle = 50 * 16;
		 	int spanAngle = 80 * 16;
		 	painter->drawArc(rectangle, startAngle, spanAngle);
		 	painter->drawLine(8.0, 30.0, 8.0, 60.0);
		 	painter->drawLine(8.0, 60.0, 37.0, 60.0);
		 	painter->drawLine(37.0, 60.0, 37.0, 30.0);
			painter->drawText(18, 47, myText);
			//////////////////////////////////////////////////////////////////////////
		}
		break;
	case 2:
		{
			//或门
			QRectF rectangleT(0.0, 20.0, 45.0, 80.0);
			int startAngle = 50 * 16;
			int spanAngle = 80 * 16;
			painter->drawArc(rectangleT, startAngle, spanAngle);

			QRectF rectangleB(0.0, 50.0, 45.0, 80.0);
			painter->drawArc(rectangleB, startAngle, spanAngle);

			painter->drawLine(8.0, 30.0, 8.0, 60.0);
			painter->drawLine(37.0, 60.0, 37.0, 30.0);
			painter->drawText(18, 47, myText);

		}
		break;
	case 3:
		{
			//表决门
			QRectF rectangleT(0.0, 20.0, 45.0, 80.0);
			int startAngle = 50 * 16;
			int spanAngle = 80 * 16;
			painter->drawArc(rectangleT, startAngle, spanAngle);

			QRectF rectangleB(0.0, 50.0, 45.0, 80.0);
			painter->drawArc(rectangleB, startAngle, spanAngle);

			painter->drawLine(8.0, 30.0, 8.0, 60.0);
			painter->drawLine(37.0, 60.0, 37.0, 30.0);

			painter->setPen(myTextColor);
			QRectF rectangleText(0.0, 0.0, 45.0, 80.0);
			painter->drawText(rectangleText,Qt::AlignCenter,myText);
		}
		break;
	}	
}


/////////////////////////////////////protected:
void LogicalGate::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
	QString text=QInputDialog::getText(event->widget(),tr("Edit text"),tr("Enter new text:"), QLineEdit::Normal,myText);
	if (!text.isEmpty())
	{
		setText(text);
	}

}
void	LogicalGate::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
	if(myText == "+")
		myText = "-";
	else myText = "+";
}
bool LogicalGate::sceneEventFilter ( QGraphicsItem * watched, QEvent * event )
{
	return false;
}

QVariant LogicalGate::itemChange(GraphicsItemChange change, const QVariant& value)
{
	if (change==ItemPositionHasChanged)
	{	
		foreach(Link* link,myLinks)
		{
			link->traceNodes();
		}
	}
	return QGraphicsItem::itemChange(change,value);
}

/////////////////////////////////////////private:
QRectF LogicalGate::outlineRect() const //轮廓
{
	const int padding = 10;
	QFontMetricsF metrics=qApp->font();
	QRectF rect=metrics.boundingRect(myText);
	rect.adjust(-padding,-padding,padding,padding);
	rect.translate(-rect.center());
	return rect;
}

int LogicalGate::roundness(double size) const
{
	const int Diameter=12; //当rect的长宽都是快12时，即显示原型。因为：qreal xRadius, qreal yRadius的参数取值在0-99之间，99为满圆形
	return 100*Diameter/int(size);
}