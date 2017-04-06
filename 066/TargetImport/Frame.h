//***************************************
//	����ʱ��:	2016:7:14   17:36
//	�ļ�����: 	Frame.h
//	�ļ�����:	��Ⱥ��
//	
//	����˵��:	��������Զ���������Ŀ����
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

	//ͨ��getter����������frame��content�������������Ӧ����ӵ�����
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
