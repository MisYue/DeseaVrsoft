#include "KillTreeRenderer.h"
#include "killTree/DrawKillTreeWgt.h"
#include <QHBoxLayout>
#include <QToolBar>

KillTreeRenderer::KillTreeRenderer(QWidget* parent /* = NULL */)
: QMainWindow(parent)
{
	m_drawWgt = new DrawKillTreeWgt(this);
	QWidget* central = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout;
	layout->addWidget(m_drawWgt);
	central->setLayout(layout);
	setCentralWidget(central);


	QAction* zoomIn = new QAction(QIcon(":/MainWindow/Resources/images/zoomIn.PNG"), QString::fromLocal8Bit("放大"), this);
	QAction* zoomOut = new QAction(QIcon(":/MainWindow/Resources/images/zoomOut.PNG"), QString::fromLocal8Bit("缩小"), this);
	QAction* save = new QAction(QIcon(":/MainWindow/Resources/images/save.PNG"), QString::fromLocal8Bit("保存"), this);
	QAction* set = new QAction(QIcon(":/MainWindow/Resources/images/set.PNG"), QString::fromLocal8Bit("设置"), this);

	QToolBar* toolBar = new QToolBar;
	toolBar->setObjectName("ktrToolBar");
	addToolBar(toolBar);
	toolBar->addAction(zoomIn);
	toolBar->addAction(zoomOut);
	toolBar->addAction(save);
	//toolBar->addAction(set);

	connect(zoomIn, SIGNAL(triggered()), m_drawWgt, SLOT(ClickedZoomIn()));
	connect(zoomOut, SIGNAL(triggered()), m_drawWgt, SLOT(ClickedZoomOut()));
	connect(save, SIGNAL(triggered()), m_drawWgt, SLOT(ClickedSave()));
	connect(set, SIGNAL(triggered()), m_drawWgt, SLOT(ClickedSet()));

	

}
void KillTreeRenderer::UpdateDraw(const QString& text)
{
	m_drawWgt->UpdateDraw(text);
}
