//***************************************
//	����ʱ��:	2016:7:14   17:38
//	�ļ�����: 	TitleBar.h
//	�ļ�����:	��Ⱥ��
//	
//	����˵��:	�����Զ����������
//***************************************

#pragma once
#include <QWidget>
#include <QToolButton>
#include <QPixmap>
#include <QPoint>
#include <QFrame>
#include <QLabel>

class Frame;

class TitleBar :
	public QFrame
{
	Q_OBJECT
public:
	TitleBar(QWidget* parent = NULL);
	virtual ~TitleBar(void);
	void setTitleText(const QString& text);
public slots:
	void showSmall();
	void showMaxRestore();
private:
	QToolButton* minimize;
	QToolButton* maximize;
	QToolButton* close;
	QLabel* titleIcon;
	QPixmap restorePix, maxPix;
	bool maxNormal;
	QPoint startPos;
	QPoint clickPos;
	Frame* frame;
	bool mouseDown;
	bool left, right, top;
	QLabel* titleLabel;
	QPoint oldPos;
protected:
	void mousePressEvent(QMouseEvent* me);
	void mouseMoveEvent(QMouseEvent* me);
	void mouseDoubleClickEvent(QMouseEvent* me);
	void mouseReleaseEvent(QMouseEvent* me);
	bool eventFilter(QObject *obj, QEvent *ev);
};
