#pragma once
#include <QMainWindow>
class DrawKillTreeWgt;

class KillTreeRenderer : public QMainWindow
{
	Q_OBJECT
public:
	KillTreeRenderer(QWidget* parent = NULL);
	void Reset();
public slots:
	void UpdateDraw(const QString& text);
private:
	DrawKillTreeWgt* m_drawWgt;
};