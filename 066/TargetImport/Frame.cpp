//***************************************
//	创建时间:	2016:7:14   17:38
//	文件名称: 	Frame.cpp
//	文件作者:	岳群磊
//	
//	功能说明:	实现具有自定义标题栏的框架类
//***************************************

#include <Windows.h>
#include "Frame.h"
#include "TitleBar.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QMainWindow>
#include <QMenuBar>
#include <QDockWidget>
#include <QToolBar>
#include <QApplication>

QMenuBar* g_menuBar = NULL;

Frame::Frame(QWidget* parent) : QFrame(parent)
{
	setObjectName("mainFrame");

	QPalette palette;
	palette.setColor(QPalette::Foreground, QColor(112, 179, 214));
	setPalette(palette);

	mouseDown = false;
	left = false;
	right = false;
	bottom = false;
	setFrameShape(Box);
	setLineWidth(3);
	//设置无边框窗口
	//这会导致该窗口无法改变大小或移动
	setWindowFlags(Qt::FramelessWindowHint);
	setMouseTracking(true);
	_titleBar = new TitleBar(this);
	contentContainer = new QWidget(this);
	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addWidget(_titleBar);
	vbox->setMargin(0);
	vbox->setSpacing(0);

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(contentContainer);
	layout->setMargin(0);
	layout->setSpacing(0);
	vbox->addLayout(layout);
}

Frame::~Frame(void)
{
}

void Frame::mousePressEvent(QMouseEvent* e)
{
	oldPos = e->pos();
	mouseDown = e->button() == Qt::LeftButton;
}

void Frame::mouseMoveEvent(QMouseEvent* e)
{
	int x = e->x();
	int y = e->y();

	if(mouseDown)
	{
		int dx = x - oldPos.x();
		int dy = y - oldPos.y();

		QRect g = geometry();

		if(left)
			g.setLeft(g.left() + dx);
		if(right)
			g.setRight(g.right() + dx);
		if(bottom)
			g.setBottom(g.bottom() + dy);

		setGeometry(g);
		m_preRect = g;

		oldPos = QPoint(!left ? e->x() : oldPos.x(), e->y());
	}
	else if(!isMaximized())
	{
		QRect r = rect();
		left = qAbs(x - r.left()) <= 5;
		right = qAbs(x - r.right()) <= 5;
		bottom = qAbs(y - r.bottom()) <= 5;
		bool hor = left | right;

		if(hor && bottom)
		{
			if(left)
				setCursor(Qt::SizeBDiagCursor);
			else
				setCursor(Qt::SizeFDiagCursor);
		}
		else if(hor)
		{
			setCursor(Qt::SizeHorCursor);
		}
		else if(bottom)
		{
			setCursor(Qt::SizeVerCursor);	

		}
		else
		{
			setCursor(Qt::ArrowCursor);
		}
	}
	else
	{
		setCursor(Qt::ArrowCursor);
	}
}

void Frame::mouseReleaseEvent(QMouseEvent* e)
{
	mouseDown = false;
}



void Frame::setContentWidget(QWidget* contentWidget)
{
	QFrame* fc = dynamic_cast<QFrame*>(contentWidget);
	if(fc)
		fc->setWindowFlags(fc->windowFlags() & (~Qt::FramelessWindowHint));
	QVBoxLayout* layout = new QVBoxLayout(contentContainer);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(contentWidget);
	content = contentWidget;
	QRect rect = contentWidget->geometry();
	resize(rect.width(), rect.height());
	_titleBar->setTitleText(contentWidget->windowTitle());
	QMainWindow* m = dynamic_cast<QMainWindow*>(contentWidget);
	if(m)
	{
		m->menuBar()->installEventFilter(this);
		g_menuBar = m->menuBar();
		foreach(QObject* obj, m->children())
		{
			if(dynamic_cast<QToolBar*>(obj))
				obj->installEventFilter(this);
		}
	}
}

bool Frame::eventFilter(QObject *obj, QEvent *ev)
{
	if(obj && obj != this && ev->type() == QEvent::Enter)
	{
		if(dynamic_cast<QMenuBar*>(obj) || dynamic_cast<QToolBar*>(obj))
		{
			setCursor(Qt::ArrowCursor);
		}
	}
	return QFrame::eventFilter(obj, ev);
}
void Frame::closeEvent(QCloseEvent *event)
{
	QApplication::sendEvent(content, event);

}