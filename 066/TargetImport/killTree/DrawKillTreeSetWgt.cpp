#include "DrawKillTreeSetWgt.h"

#include <QtGui>

DrawKillTreeSetWgt::DrawKillTreeSetWgt(QWidget *parent)
	: QDialog(parent)
{
	ui_WgtDrawKillTreeSet.setupUi(this);

	bool bConnect = connect( ui_WgtDrawKillTreeSet.OK_BTN, SIGNAL( clicked() ), this, SLOT( ClickedOK() ) );
	Q_ASSERT( bConnect );

	bConnect = connect( ui_WgtDrawKillTreeSet.Cancel_BTN, SIGNAL( clicked() ), this, SLOT( ClickedCancel() ) );
	Q_ASSERT( bConnect );

	bConnect = connect( ui_WgtDrawKillTreeSet.Default_BTN, SIGNAL( clicked() ), this, SLOT( ClickedDefault() ) );
	Q_ASSERT( bConnect );

	bConnect = connect( ui_WgtDrawKillTreeSet.Name_RBTN, SIGNAL( clicked() ), this, SLOT( ClickedNodeNameRBTN() ) );
	Q_ASSERT( bConnect );

	bConnect = connect( ui_WgtDrawKillTreeSet.ID_RBTN, SIGNAL( clicked() ), this, SLOT( ClickedNodeIDRBTN() ) );
	Q_ASSERT( bConnect );

	//////////////////////////////////////////////////////////////////////////
	bConnect = connect( ui_WgtDrawKillTreeSet.selBackgroundColor, SIGNAL( clicked() ), this, SLOT( ClickedBackgroundColor() ) );
	Q_ASSERT( bConnect );

	bConnect = connect( ui_WgtDrawKillTreeSet.selNodeTextColor, SIGNAL( clicked() ), this, SLOT( ClickedNodeTextColor() ) );
	Q_ASSERT( bConnect );

	bConnect = connect( ui_WgtDrawKillTreeSet.selNodeLineColor, SIGNAL( clicked() ), this, SLOT( ClickedNodeLineColor() ) );
	Q_ASSERT( bConnect );

	bConnect = connect( ui_WgtDrawKillTreeSet.selNodeBackgroundColor, SIGNAL( clicked() ), this, SLOT( ClickedNodeBackgroundColor() ) );
	Q_ASSERT( bConnect );
}

DrawKillTreeSetWgt::~DrawKillTreeSetWgt(void)
{
}

void DrawKillTreeSetWgt::InitColor()
{
	QRgb qRgb;
	qRgb = KillTreeBackgroundColor.rgb();
	SetLineEditColor(qRgb, 1);

	qRgb = NodeTextColor.rgb();
	SetLineEditColor(qRgb, 2);

	qRgb = NodeLineColor.rgb();
	SetLineEditColor(qRgb, 3);

	qRgb = NodeBackgroundColor.rgb();
	SetLineEditColor(qRgb, 4);

	if(m_bFlag)
	{
		ui_WgtDrawKillTreeSet.Name_RBTN->setChecked(true);
		ui_WgtDrawKillTreeSet.ID_RBTN->setChecked(false);
	}
	else
	{
		ui_WgtDrawKillTreeSet.Name_RBTN->setChecked(false);
		ui_WgtDrawKillTreeSet.ID_RBTN->setChecked(true);
	}
}

void DrawKillTreeSetWgt::ClickedOK()
{
	QDialog::accept();
}

void DrawKillTreeSetWgt::ClickedCancel()
{
	close();
}

void DrawKillTreeSetWgt::ClickedDefault()
{
	ui_WgtDrawKillTreeSet.Name_RBTN->setChecked(true);
	m_bFlag = true;
	KillTreeBackgroundColor = Qt::white;
	NodeTextColor = Qt::darkGreen;
	NodeLineColor = Qt::darkBlue;
	NodeBackgroundColor = Qt::blue;

	QRgb qRgb;
	qRgb = KillTreeBackgroundColor.rgb();
	SetLineEditColor(qRgb, 1);

	qRgb = NodeTextColor.rgb();
	SetLineEditColor(qRgb, 2);

	qRgb = NodeLineColor.rgb();
	SetLineEditColor(qRgb, 3);

	qRgb = NodeBackgroundColor.rgb();
	SetLineEditColor(qRgb, 4);
}

void DrawKillTreeSetWgt::ClickedNodeNameRBTN()
{
	ui_WgtDrawKillTreeSet.ID_RBTN->setChecked(false);
	m_bFlag = true;
}

void DrawKillTreeSetWgt::ClickedNodeIDRBTN()
{
	ui_WgtDrawKillTreeSet.Name_RBTN->setChecked(false);
	m_bFlag = false;
}

void DrawKillTreeSetWgt::ClickedBackgroundColor()
{
	bool ok=false;
	QRgb initRgba=ui_WgtDrawKillTreeSet.LEBackgroundColor->text().toUInt(&ok);
	if (ok)
	{
		ok=false;
	}

	QRgb selRgbr=QColorDialog::getRgba(initRgba,&ok,this);

	if (ok)
	{
		SetLineEditColor(selRgbr, 1);
	}
}

void DrawKillTreeSetWgt::ClickedNodeTextColor()
{
	bool ok=false;
	QRgb initRgba=ui_WgtDrawKillTreeSet.LENodetextColor->text().toUInt(&ok);
	if (ok)
	{
		ok=false;
	}

	QRgb selRgbr=QColorDialog::getRgba(initRgba,&ok,this);

	if (ok)
	{
		SetLineEditColor(selRgbr, 2);
	}
}

void DrawKillTreeSetWgt::ClickedNodeLineColor()
{
	bool ok=false;
	QRgb initRgba=ui_WgtDrawKillTreeSet.LENodeLineColor->text().toUInt(&ok);
	if (ok)
	{
		ok=false;
	}

	QRgb selRgbr=QColorDialog::getRgba(initRgba,&ok,this);

	if (ok)
	{
		SetLineEditColor(selRgbr, 3);
	}
}

void DrawKillTreeSetWgt::ClickedNodeBackgroundColor()
{
	bool ok=false;
	QRgb initRgba=ui_WgtDrawKillTreeSet.LENodeBackgroundColor->text().toUInt(&ok);
	if (ok)
	{
		ok=false;
	}

	QRgb selRgbr=QColorDialog::getRgba(initRgba,&ok,this);

	if (ok)
	{
		SetLineEditColor(selRgbr, 4);
	}
}

void DrawKillTreeSetWgt::SetLineEditColor(QRgb qRgb, int nType)
{
	QColor sendColor(qRgb);
	int alpha=qAlpha(qRgb);
	sendColor.setAlpha(alpha);

	QPalette pal=palette();	
	pal.setColor(QPalette::Base,sendColor);
	switch(nType)
	{
	case 1:
		{
			ui_WgtDrawKillTreeSet.LEBackgroundColor->setPalette(pal);
//			ui_WgtDrawKillTreeSet.LEBackgroundColor->setText(QString("%1").arg(qRgb));
			KillTreeBackgroundColor = sendColor;
		}
		break;

	case 2:
		{
			ui_WgtDrawKillTreeSet.LENodetextColor->setPalette(pal);
//			ui_WgtDrawKillTreeSet.LENodetextColor->setText(QString("%1").arg(qRgb));
			NodeTextColor = sendColor;
		}
		break;

	case 3:
		{
			ui_WgtDrawKillTreeSet.LENodeLineColor->setPalette(pal);
//			ui_WgtDrawKillTreeSet.LENodeLineColor->setText(QString("%1").arg(qRgb));
			NodeLineColor = sendColor;
		}
		break;

	case 4:
		{
			ui_WgtDrawKillTreeSet.LENodeBackgroundColor->setPalette(pal);
//			ui_WgtDrawKillTreeSet.LENodeBackgroundColor->setText(QString("%1").arg(qRgb));
			NodeBackgroundColor = sendColor;
		}
		break;
	}
}