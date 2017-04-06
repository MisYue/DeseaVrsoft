//***************************************
//	创建时间:	2016:7:14   17:36
//	文件名称: 	Frame.h
//	文件作者:	岳群磊
//	
//	功能说明:	定义具有自定义标题栏的框架类
//***************************************

#pragma once
#include <QFrame>
#include <QRect>
#include <QFocusEvent>

class TitleBar;

class Frame :
	public QFrame
{
	friend TitleBar;
public:
	Frame(QWidget* parent = NULL);
	virtual ~Frame(void);

	//通过getter允许外界访问frame的content区域，其它子组件应该添加到这里
	QWidget* contentWidget() const { return contentContainer; }

	void setContentWidget(QWidget* content);

	TitleBar* titleBar() const { return _titleBar; }

	void mousePressEvent(QMouseEvent* e);

	void mouseMoveEvent(QMouseEvent* e);

	void mouseReleaseEvent(QMouseEvent* e);
protected:
	bool eventFilter(QObject *obj, QEvent *ev);
	virtual void closeEvent(QCloseEvent *event);
private:
	TitleBar* _titleBar;
	QWidget* contentContainer;
	QWidget* content;
	QPoint oldPos;
	QRect m_preRect;
	bool mouseDown;
	bool left, right, bottom;

};
