#pragma once

#include <QDialog>

#include "ui_DrawKillTree.h"
#include "DrawKillTreeGraphView.h"

class DrawKillTreeWgt : public  QDialog
{
	Q_OBJECT

public:
	DrawKillTreeWgt(QWidget *parent = 0, QString strPathName = "", QString strFileName = "");
	~DrawKillTreeWgt(void);
	void UpdateDraw(const QString& text);
public slots:
	void ClickedSet();
	void ClickedSave();
	void ClickedClose();

	void ClickedZoomIn();
	void ClickedZoomOut();

protected:
// 	void ParseKTInfo();
// 	void CreateKillTree();
// 	void addNode(KTInfo ktInfo, double dX, double dY);
// 	void AddItemPoint(int nLevel, QPointF qPointf);
// 	void DrawItmeLine();


private:
	Ui_DrawKillTreeWgt ui_WgtDrawKillTree;

	DrawKillTree *m_pDrawKillTree;

	QColor NodeTextColor;
	QColor NodeLineColor;
	QColor NodeBackgroundColor;
	QColor KillTreeBackgroundColor;
	bool   bFlag;
};