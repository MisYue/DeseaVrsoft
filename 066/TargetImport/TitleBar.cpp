//***************************************
//	创建时间:	2016:7:14   17:39
//	文件名称: 	TitleBar.cpp
//	文件作者:	岳群磊
//	
//	功能说明:	实现自定义标题栏类
//***************************************

#include "TitleBar.h"
#include "Frame.h"
#include <QLabel>
#include <QStyle>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <iostream>

//拉伸到屏幕边界时，不能继续拉伸
//上下方向移动或拉伸到屏幕边界时，若继续保持按下鼠标停留，则上下达到最大值
//在最大化界面时，按下鼠标移动标题栏时，先设置到原来的大小，位置设置为右上角，再移动

const static int g_margin = 0;

TitleBar::TitleBar(QWidget* parent) : QFrame(parent)
{
	setObjectName("titleBar");
	frame = dynamic_cast<Frame*>(parent);
	mouseDown = false;
	left = false;
	right = false;
	top = false;
	setFrameShape(NoFrame);
	setWindowFlags(Qt::FramelessWindowHint);
	setMouseTracking(true);

	//不继承父组件的背景色
	//setAutoFillBackground(true);
	//使用 Highlight 作为背景色
	//setBackgroundRole(QPalette::Highlight);

	minimize = new QToolButton(this);
	minimize->setAutoRaise(true);
	minimize->setIcon(QIcon(":/MainWindow/Resources/images/minMW.png"));
	minimize->setIconSize(QSize(32, 32));
	maximize = new QToolButton(this);
	maximize->setAutoRaise(true);
	maximize->setIcon(QIcon(":/MainWindow/Resources/images/maxMW.png"));
	maximize->setIconSize(QSize(32, 32));

	close = new QToolButton(this);
	close->setAutoRaise(true);
	close->setIcon(QIcon(":/MainWindow/Resources/images/closeMW.png"));
	close->setIconSize(QSize(32, 32));

	titleIcon = new QLabel(this);
	titleIcon->setFrameShape(NoFrame);
	titleIcon->setStyleSheet("border-image: url(:/MainWindow/Resources/images/myappico.ico);");
	titleIcon->setMinimumHeight(24);
	titleIcon->setMinimumWidth(24);

	minimize->setObjectName("minimize");
	maximize->setObjectName("maximize");
	close->setObjectName("close");
	titleIcon->setObjectName("titleIcon");

	titleLabel = new QLabel(this);
	titleLabel->setObjectName("titleLabel");
	

	QHBoxLayout* hbox = new QHBoxLayout(this);
	hbox->setContentsMargins(5, 2, 10, 2);
	hbox->addWidget(titleIcon);
	hbox->addWidget(titleLabel);
	hbox->addWidget(minimize);
	hbox->addWidget(maximize);
	hbox->addWidget(close);
	hbox->setSpacing(2);

	hbox->insertStretch(2, 500);


	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	maxNormal = false;

	connect(close, SIGNAL(clicked()), parent, SLOT(close()));
	connect(minimize, SIGNAL(clicked()), this, SLOT(showSmall()));
	connect(maximize, SIGNAL(clicked()), this, SLOT(showMaxRestore()));

	minimize->installEventFilter(this);
	maximize->installEventFilter(this);
	close->installEventFilter(this);
	titleIcon->installEventFilter(this);
	titleLabel->installEventFilter(this);
}

TitleBar::~TitleBar(void)
{
}

void TitleBar::showSmall()
{
	frame->showMinimized();
}
void TitleBar::showMaxRestore()
{
	if(maxNormal)
	{
		frame->move(0, 0);
		frame->showNormal();
		maxNormal = !maxNormal;
	}
	else
	{
		frame->showMaximized();
		maxNormal = !maxNormal;
	}
}

void TitleBar::mousePressEvent(QMouseEvent* me)
{
	mouseDown = me->button() == Qt::LeftButton;
	startPos = me->globalPos();
	clickPos = mapToParent(me->pos());
}
void TitleBar::mouseMoveEvent(QMouseEvent* e)
{
	if(maxNormal)
		return;
	int x = e->x();
	int y = e->y();
	QRect r = rect();
	if(mouseDown)
	{
		int dx = x - oldPos.x();
		if(right)
			dx = dx - r.right();
		int dy = y - oldPos.y();

		QRect g = frame->geometry();
		if(left)
		{
			int i = g.left() + dx;
			i = qMax(i, g_margin);
			g.setLeft(i);
		}
		else if(right)
		{
			int i = g.right() + dx;
			g.setRight(i);
		}
		if(top)
		{
			int i = g.top() + dy;
			i = qMax(i, g_margin);
			g.setTop(i);
		}
		else
		{
			frame->move(e->globalPos() - clickPos);
			return ;
		}

		std::cout << x << " " << y << " " << oldPos.x() << " " << oldPos.y() << " " << dx << " " << dy << std::endl;

		frame->setGeometry(g);
		frame->m_preRect = g;

		oldPos = QPoint(0, 0);
		//oldPos = QPoint(x, y);
	}
	else if(!frame->isMaximized())
	{
		left = qAbs(x - r.left()) <= 5;
		right = qAbs(x - r.right()) <= 5;
		top = qAbs(y - r.top()) <= 5;
		bool hor = left | right;

		if(hor && top)
		{
			if(left)
				setCursor(Qt::SizeFDiagCursor);
			else
				setCursor(Qt::SizeBDiagCursor);
		}
		else if(hor)
		{
			setCursor(Qt::SizeHorCursor);
		}
		else if(top)
		{
			setCursor(Qt::SizeVerCursor);	
		}
		else
		{
			setCursor(Qt::ArrowCursor);
		}
		oldPos = QPoint(x, y);
	}
	else
	{
		setCursor(Qt::ArrowCursor);
	}
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent* me)
{
	maxNormal = frame->isMaximized ();
	showMaxRestore();
}
void TitleBar::mouseReleaseEvent(QMouseEvent* me)
{
	mouseDown = false;
}


void TitleBar::setTitleText(const QString& text)
{
	titleLabel->setText(text);
}

bool TitleBar::eventFilter(QObject *obj, QEvent *ev)
{
	if(obj && obj != this && ev->type() == QEvent::Enter)
	{
		if(obj == minimize || obj == maximize || obj == close || obj == titleIcon || obj == titleLabel)
		{
			setCursor(Qt::ArrowCursor);
		}
	}
	return QFrame::eventFilter(obj, ev);
}
