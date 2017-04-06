#include <QPainter>
#include <QFontMetricsF>
#include <QStyleOptionGraphicsItem>
#include <QInputDialog>
#include <QGraphicsSceneMouseEvent>

#include "node.h"
#include "link.h"
Node::Node()
{
	myTextColor=Qt::darkGreen;
	myOutlineColor=Qt::darkBlue;
	myBackgroundColor=Qt::blue;
//	setFlags(ItemIsMovable|ItemIsSelectable);
}
Node::~Node()
{
	foreach(Link* link, myLinks)
		delete link;
}
void Node::setText(const QString& text)
{
	prepareGeometryChange();
	myText=text;
	update();
}
QString Node::text() const
{
	return myText;
}
void Node::setTextColor(const QColor& color)
{
	myTextColor=color;
	update();
}
QColor Node::textColor() const
{
	return myTextColor;
}
void Node::setOutlineColor(const QColor& color)
{
	myOutlineColor=color;
	update();
}
QColor Node::outlineColor() const
{
	return myOutlineColor;
}
void Node::setBackgroundColor(const QColor& color)
{
	myBackgroundColor=color;
	update();
}
QColor Node::backgroundColor() const
{
	return myBackgroundColor;
}

void Node::addLink(Link* link)
{
	myLinks.insert(link);
}
void Node::removeLink(Link* link)
{
	myLinks.remove(link);
}

//计算一个包围节点文字的矩阵
QRectF Node::boundingRect() const //边界 ，边界区域大于轮廓区域1个像素点
{
	const int Margin=1;
	return outlineRect().adjusted(-Margin,-Margin,Margin,Margin);
}

QPainterPath Node::shape() const
{
	QPainterPath paintPath;
	QRectF rect=outlineRect();
	paintPath.addRoundedRect(rect,roundness(rect.width()),roundness(rect.height()));
	return paintPath;
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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
	//myBackgroundColor.setAlpha(100);
	//QLinearGradient gradient;
	//gradient.setStart(rect.topLeft());
	//gradient.setFinalStop(rect.bottomLeft());
	//gradient.setColorAt(0.0,Qt::black);
	//gradient.setColorAt(0.1,myBackgroundColor);
	//gradient.setColorAt(0.5,Qt::white);
	//gradient.setColorAt(0.9,myBackgroundColor);
	//gradient.setColorAt(1,Qt::black);
	//painter->setBrush(gradient);


	if(mySubEventNum > 0)
	{
		//painter->drawRoundRect(rect,roundness(rect.width()),roundness(rect.height()));
		painter->drawRoundRect(rect, 0, 0);
	}
	else
	{
		//painter->drawEllipse(rect);
		painter->drawRoundRect(rect,25/*roundness(rect.width())*/,99/*roundness(rect.height())*/);

	}

	//不用QPainterPath是因为，写文字时还要用到rect；
	//QPainterPath paintPath=shape();
	//painter->drawPath(paintPath);

	painter->setPen(myTextColor);
	QFont serifFont("Times", 8, QFont::Bold);
	painter->setFont(serifFont);
// 	int nCount = myText.size();
// 	if(nCount > 4)
// 	{
// 		myText = myText.left(2) + QString::fromLocal8Bit("...");
// 	}
	painter->drawText(rect,Qt::AlignCenter,myText);
}

QRectF Node::outlineRect() const //轮廓
{
	const int padding = 8;
	QFontMetricsF metrics=qApp->font();
	QRectF rect=metrics.boundingRect(myText);
	rect.adjust(-padding,-padding,padding,padding);
	rect.translate(-rect.center());
	return rect;
}

int Node::roundness(double size) const
{
	const int Diameter=12; //当rect的长宽都是快12时，即显示原型。因为：qreal xRadius, qreal yRadius的参数取值在0-99之间，99为满圆形
	//return 100*Diameter/int(size);
	return 50;
}