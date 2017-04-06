#include "DrawKillTreeWgt.h"
#include "DrawKillTreeSetWgt.h"

#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtOpenGL/QGLWidget>

DrawKillTreeWgt::DrawKillTreeWgt(QWidget *parent, QString strPathName, QString strFileName)
: QDialog(parent)
{
	ui_WgtDrawKillTree.setupUi(this);

	Qt::WindowFlags flags=Qt::Dialog;
	flags |=Qt::WindowMinimizeButtonHint;
	flags |=Qt::WindowMaximizeButtonHint;
	setWindowFlags(flags);

	//ui_WgtDrawKillTree.graphicsView->PaintStart(strPathName, strFileName);

	QString strTitle = QString::fromLocal8Bit("毁伤树");

	strTitle += "--" + strFileName;

	setWindowTitle(strTitle);

	m_pDrawKillTree = new DrawKillTree(this);
	//m_pDrawKillTree->PaintStart(strPathName, strFileName);

	QGridLayout* grid = new QGridLayout;
 	grid->addWidget( m_pDrawKillTree );
 	grid->setContentsMargins(0,0,0,0);

	ui_WgtDrawKillTree.groupBox->setLayout(grid);

	bool bConnect = connect( ui_WgtDrawKillTree.Set_BTN, SIGNAL( clicked() ), this, SLOT( ClickedSet() ) );
	Q_ASSERT( bConnect );

	bConnect = connect( ui_WgtDrawKillTree.Save_BTN, SIGNAL( clicked() ), this, SLOT( ClickedSave() ) );
	Q_ASSERT( bConnect );

	bConnect = connect( ui_WgtDrawKillTree.Close_BTN, SIGNAL( clicked() ), this, SLOT( ClickedClose() ) );
	Q_ASSERT( bConnect );

	bConnect = connect( ui_WgtDrawKillTree.ZoomIn_BTN, SIGNAL( clicked() ), this, SLOT( ClickedZoomIn() ) );
	Q_ASSERT( bConnect );

	bConnect = connect( ui_WgtDrawKillTree.ZoomOut_BTN, SIGNAL( clicked() ), this, SLOT( ClickedZoomOut() ) );
	Q_ASSERT( bConnect );

	ui_WgtDrawKillTree.Set_BTN->setVisible(false);
	ui_WgtDrawKillTree.Save_BTN->setVisible(false);
	ui_WgtDrawKillTree.Close_BTN->setVisible(false);
	ui_WgtDrawKillTree.ZoomIn_BTN->setVisible(false);
	ui_WgtDrawKillTree.ZoomOut_BTN->setVisible(false);

	KillTreeBackgroundColor = Qt::white;
	NodeTextColor = Qt::darkGreen;
	NodeLineColor = Qt::darkBlue;
	NodeBackgroundColor = Qt::blue;
	bFlag = true;

	m_pDrawKillTree->setBackgroundColor(KillTreeBackgroundColor);
	m_pDrawKillTree->setNodeTextColor(NodeTextColor);
	m_pDrawKillTree->setNodeOutLineColor(NodeLineColor);
	m_pDrawKillTree->setNodeBackgroundColor(NodeBackgroundColor);
	m_pDrawKillTree->StartTimer();


}

DrawKillTreeWgt::~DrawKillTreeWgt(void)
{
}

void DrawKillTreeWgt::ClickedSet()
{
	DrawKillTreeSetWgt* drawKillTreeSetWgt = new DrawKillTreeSetWgt();
	drawKillTreeSetWgt->setWindowTitle("设置");
	drawKillTreeSetWgt->setKillTreeBackgroundColor(KillTreeBackgroundColor);
	drawKillTreeSetWgt->setNodeTextColor(NodeTextColor);
	drawKillTreeSetWgt->setNodeLineColor(NodeLineColor);
	drawKillTreeSetWgt->setNodeBackgroundColor(NodeBackgroundColor);
	drawKillTreeSetWgt->setShowNameOrID(bFlag);
	drawKillTreeSetWgt->InitColor();
	if(drawKillTreeSetWgt->exec() == QDialog::Accepted)
	{
		KillTreeBackgroundColor = drawKillTreeSetWgt->getKillTreeBackgroundColor();
		NodeTextColor = drawKillTreeSetWgt->getNodeTextColor();
		NodeLineColor = drawKillTreeSetWgt->getNodeLineColor();
		NodeBackgroundColor = drawKillTreeSetWgt->getNodeBackgroundColor();
		bFlag = drawKillTreeSetWgt->getShowNameOrID();
		m_pDrawKillTree->setBackgroundColor(KillTreeBackgroundColor);
		m_pDrawKillTree->setNodeTextColor(NodeTextColor);
		m_pDrawKillTree->setNodeOutLineColor(NodeLineColor);
		m_pDrawKillTree->setNodeBackgroundColor(NodeBackgroundColor);
		m_pDrawKillTree->setNodeNameOrID(bFlag);
		m_pDrawKillTree->RefreshNode();
	}
}

void DrawKillTreeWgt::ClickedSave()
{
	QFileDialog *fileDialog = new QFileDialog(this);//创建一个QFileDialog对象，构造函数中的参数可以有所添加。
	fileDialog->setWindowTitle(tr("Save As"));//设置文件保存对话框的标题
	fileDialog->setAcceptMode(QFileDialog::AcceptSave);//设置文件对话框为保存模式
	fileDialog->setFileMode(QFileDialog::AnyFile);//设置文件对话框弹出的时候显示任何文件，不论是文件夹还是文件
//	fileDialog->setViewMode(QFileDialog::Detail);//文件以详细的形式显示，显示文件名，大小，创建日期等信息；
	fileDialog->setFilter(tr("Image Files(*.jpg *.png)"));//设置文件类型过滤器
	if(fileDialog->exec() == QDialog::Accepted) {//注意使用的是QFileDialog::Accepted或者QDialog::Accepted,不是QFileDialog::Accept
 		QString path = fileDialog->selectedFiles()[0];//得到用户选择的文件名
		path = path + QString::fromLocal8Bit(".jpg");

		m_pDrawKillTree->SaveKillTreePic(path);

/*		bool bResult;
		int x = 0;
		int y = 0;
		int w = m_pDrawKillTree->scene->width();
		int h = m_pDrawKillTree->scene->height();

		QImage image(w, h, QImage::Format_ARGB32);
		QRgb qRgb = m_pDrawKillTree->getBackgroundColor().rgb();
		image.fill(qRgb);
		QPainter painter(&image);
		painter.setRenderHint(QPainter::Antialiasing);
		m_pDrawKillTree->scene->render(&painter);   //关键函数

		bResult = image.save(path, "PNG");
		*/
	}
}

void DrawKillTreeWgt::ClickedClose()
{
	m_pDrawKillTree->StopTimer();
	m_pDrawKillTree->DelArray();

	close();
}

void DrawKillTreeWgt::ClickedZoomIn()
{
	m_pDrawKillTree->setZoomIn();
}

void DrawKillTreeWgt::ClickedZoomOut()
{
	m_pDrawKillTree->setZoomOut();
}
void DrawKillTreeWgt::UpdateDraw(const QString& text)
{
	m_pDrawKillTree->PaintStart(text);

}

//////////////////////////////////////////////////////////////////////////
