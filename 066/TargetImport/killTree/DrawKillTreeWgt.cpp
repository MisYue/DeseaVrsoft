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

	QString strTitle = QString::fromLocal8Bit("������");

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
	drawKillTreeSetWgt->setWindowTitle("����");
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
	QFileDialog *fileDialog = new QFileDialog(this);//����һ��QFileDialog���󣬹��캯���еĲ�������������ӡ�
	fileDialog->setWindowTitle(tr("Save As"));//�����ļ�����Ի���ı���
	fileDialog->setAcceptMode(QFileDialog::AcceptSave);//�����ļ��Ի���Ϊ����ģʽ
	fileDialog->setFileMode(QFileDialog::AnyFile);//�����ļ��Ի��򵯳���ʱ����ʾ�κ��ļ����������ļ��л����ļ�
//	fileDialog->setViewMode(QFileDialog::Detail);//�ļ�����ϸ����ʽ��ʾ����ʾ�ļ�������С���������ڵ���Ϣ��
	fileDialog->setFilter(tr("Image Files(*.jpg *.png)"));//�����ļ����͹�����
	if(fileDialog->exec() == QDialog::Accepted) {//ע��ʹ�õ���QFileDialog::Accepted����QDialog::Accepted,����QFileDialog::Accept
 		QString path = fileDialog->selectedFiles()[0];//�õ��û�ѡ����ļ���
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
		m_pDrawKillTree->scene->render(&painter);   //�ؼ�����

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
