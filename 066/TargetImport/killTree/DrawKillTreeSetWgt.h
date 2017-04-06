#pragma once

#include <QtGui/QGraphicsView>
#include <QDialog>

#include "ui_DrawKillTreeSet.h"
//#include "DrawKillTreeGraphView.h"

class DrawKillTreeSetWgt : public  QDialog
{
	Q_OBJECT

public:
	DrawKillTreeSetWgt(QWidget *parent = 0);
	~DrawKillTreeSetWgt(void);

	QColor getKillTreeBackgroundColor() { return KillTreeBackgroundColor; }
	QColor getNodeTextColor() { return NodeTextColor; }
	QColor getNodeLineColor() { return NodeLineColor; }
	QColor getNodeBackgroundColor() { return NodeBackgroundColor; }
	bool   getShowNameOrID()	{ return m_bFlag; }

	void setKillTreeBackgroundColor(QColor color) { KillTreeBackgroundColor = color; }
	void setNodeTextColor(QColor color) { NodeTextColor = color; }
	void setNodeLineColor(QColor color) { NodeLineColor = color; }
	void setNodeBackgroundColor(QColor color) { NodeBackgroundColor = color; }
	void setShowNameOrID(bool bFlag)	{ m_bFlag = bFlag; }

	void InitColor();

public slots:
	void ClickedOK();
	void ClickedCancel();
	void ClickedDefault();

	void ClickedNodeNameRBTN();
	void ClickedNodeIDRBTN();

	void ClickedBackgroundColor();
	void ClickedNodeTextColor();
	void ClickedNodeLineColor();
	void ClickedNodeBackgroundColor();

protected:
	void SetLineEditColor(QRgb qRgb, int nType);

private:
	Ui_DrawKillTreeSetWgt ui_WgtDrawKillTreeSet;

//	DrawKillTree *m_pDrawKillTree;

	QColor NodeTextColor;
	QColor NodeLineColor;
	QColor NodeBackgroundColor;
	QColor KillTreeBackgroundColor;

	bool			m_bFlag;
};