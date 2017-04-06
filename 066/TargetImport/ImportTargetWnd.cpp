//***************************************
//	创建时间:	2015:11:3   17:39
//	文件名称: 	ImportTargetWnd.h
//	文件作者:	岳群磊
//	
//	功能说明:	实现主窗口类
//***************************************
#include "ImportTargetWnd.h"
#include "ui_mainwindow.h"
#include "targetInfo.h"
#include "partEditor.h"
#include "TargetVisual.h"
#include "KillTreeEditor.h"
#include "KillTreeRenderer.h"
#include "DDTreeWidget.h"
#include <QVBoxLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QShowEvent>
#include <QFileDialog>
#include <QCursor>
#include <osg/Vec4>
#include <QMessageBox>

namespace TIMP
{
	ImportTargetWnd::ImportTargetWnd(QWidget *parent, Qt::WindowFlags flags)
		: QMainWindow(parent, flags), 
		  ui(new Ui::MainWindowClass), 
		  m_targetInfo(new TargetInfo)
	{
		ui->setupUi(this);
		setWindowTitle(QString::fromLocal8Bit("目标易损性建模"));
		statusBar()->setMaximumHeight(10);
		statusBar()->setStyleSheet("QStatusBar{background: rgb(112, 179, 214);}");
		setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
		setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
		m_targetVisual = new TargetVisual;
		setCentralWidget(m_targetVisual);
		ui->dockWidget->hide();
		ui->dockWidget_2->hide();
		ui->dockWidget_3->hide();
		ui->dockWidget_4->hide();
		m_partTree = new DDTreeWidget;
		m_partTree->setAcceptDrops(false);
		m_partTree->setHeaderLabel(QString::fromLocal8Bit("部件名称"));
		connect(m_partTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(OnItemClicked(QTreeWidgetItem*, int)));
		connect(m_partTree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(OnTreeWidgetCustomContextMenu(QPoint)));
		m_partTree->setContextMenuPolicy(Qt::CustomContextMenu);
		ui->dockWidget->setWidget(m_partTree);
		m_partEditor = new PartEditor;
		ui->dockWidget_2->setWidget(m_partEditor);
		m_killTreeEditor = new KillTreeEditor;
		ui->dockWidget_3->setWidget(m_killTreeEditor);
		m_killTreeRender = new KillTreeRenderer;
		ui->dockWidget_4->setWidget(m_killTreeRender);
		CreateActions();
		connect(m_killTreeEditor, SIGNAL(KillTreeTextChanged(const QString&)), m_killTreeRender, SLOT(UpdateDraw(const QString&)));
		connect(m_partEditor, SIGNAL(partNameChanged(const QString&)), this, SLOT(OnPartNameChanged(const QString&)));
	}

	ImportTargetWnd::~ImportTargetWnd()
	{
		if(m_targetInfo)
		{
			delete m_targetInfo;
			m_targetInfo = NULL;
		}
	}
	void ImportTargetWnd::HideToolBar()
	{
		ui->mainToolBar->hide();
	}
	void ImportTargetWnd::Reset()
	{
		ui->dockWidget->hide();
		ui->dockWidget_2->hide();
		ui->dockWidget_3->hide();
		ui->dockWidget_4->hide();
		m_lastDrawPart.clear();
		m_lastKeyPart.clear();
		m_targetInfo->Reset();
	}
	bool ImportTargetWnd::DeleteTarget()
	{
		m_targetInfo->DeleteTarget();
		m_targetVisual->Reset();
		Reset();
		return true;
	}
	void ImportTargetWnd::CreateActions()
	{
		ui->menu_3->addAction(ui->dockWidget->toggleViewAction());
		ui->menu_3->addAction(ui->dockWidget_2->toggleViewAction());
		ui->menu_3->addAction(ui->dockWidget_3->toggleViewAction());
		ui->menu_3->addAction(ui->dockWidget_4->toggleViewAction());
		connect(ui->action_Open, SIGNAL(triggered()), this, SLOT(OnOpenTarget()));
		connect(ui->action_Import, SIGNAL(triggered()), this, SLOT(OnImportTarget()));
		connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(OnSaveTarget()));
		connect(ui->action_Wireframe, SIGNAL(triggered()), m_targetVisual, SLOT(ShowWireframe()));
		connect(ui->action_WireframeAndFace, SIGNAL(triggered()), m_targetVisual, SLOT(ShowWireframeAndFace()));
		connect(ui->action_Face, SIGNAL(triggered()), m_targetVisual, SLOT(ShowFace()));
		connect(ui->action_BoundBox, SIGNAL(triggered()), m_targetVisual, SLOT(ShowBoundBox()));
		connect(ui->action_Key, SIGNAL(triggered()), this, SLOT(OnSetPartKeyOrLessKey()));
		connect(ui->action_LessKey, SIGNAL(triggered()), this, SLOT(OnSetPartKeyOrLessKey()));
		connect(ui->action_Exit, SIGNAL(triggered()), SLOT(onExit()));
	}
	void ImportTargetWnd::UpdatePartTree()
	{
		m_partTree->clear();
		QTreeWidgetItem* keyPart = new QTreeWidgetItem;
		keyPart->setText(0, QString::fromLocal8Bit("关键部件"));
		m_partTree->addTopLevelItem(keyPart);
		QTreeWidgetItem* lessKeyPart = new QTreeWidgetItem;
		lessKeyPart->setText(0, QString::fromLocal8Bit("非关键部件"));
		m_partTree->addTopLevelItem(lessKeyPart);
		const QStringList& partsName = m_targetInfo->GetPartsName();
		foreach(QString name, partsName)
		{
			QTreeWidgetItem* item = new QTreeWidgetItem;
			item->setText(0, name);
			PartExtraInfo& partInfo = m_targetInfo->GetPartExtraInfo(name.toLocal8Bit().data());
			bool bKey = partInfo.GetPropertyValue("keyPart") == "0" ? false : true;
			if(bKey)
				keyPart->addChild(item);
			else
				lessKeyPart->addChild(item);
		}
		m_killTreeEditor->SetPartsName(partsName);
	}
	void ImportTargetWnd::OnItemClicked(QTreeWidgetItem* item, int column)
	{
		if(item->parent())
		{
			if(m_lastKeyPart.size()>0)
			{
				m_partEditor->GetProperties(m_targetInfo->GetPartExtraInfo(m_lastKeyPart.toLocal8Bit().data()));
				m_lastKeyPart.clear();
			}
			if(m_lastDrawPart.size()>0)
			{
				m_targetVisual->ShowPartGrid(m_lastDrawPart.toLocal8Bit().data(), false);
				m_targetVisual->SetPartDefaultColor(m_lastDrawPart.toLocal8Bit().data());
			}
			QString text = item->text(0);
			if(item->parent()->text(0) == QString::fromLocal8Bit("关键部件"))
			{
				if(ui->dockWidget_2->isHidden())
					ui->dockWidget_2->show();
				PartExtraInfo& partInfo = m_targetInfo->GetPartExtraInfo(text.toLocal8Bit().data());
				m_partEditor->SetProperties(partInfo);
				m_lastKeyPart = text;
			}
			else
			{
				if(!ui->dockWidget_2->isHidden())
					ui->dockWidget_2->hide();
			}
			m_targetVisual->ShowPartGrid(text.toLocal8Bit().data());
			m_targetVisual->SetPartColor(text.toLocal8Bit().data(), osg::Vec4(71/255.0, 160/255.0, 156/255.0, 0.9));
			m_lastDrawPart = text;
		}
	}
	void ImportTargetWnd::OnTreeWidgetCustomContextMenu(QPoint pos)
	{
		QTreeWidgetItem* curItem = m_partTree->itemAt(pos);
		if(curItem->parent() != NULL)
		{
			QMenu* pMenu = new QMenu(this);
			if(curItem->parent()->text(0) == QString::fromLocal8Bit("关键部件"))
			{
				pMenu->addAction(ui->action_LessKey);
			}
			else
			{
				pMenu->addAction(ui->action_Key);
			}
			pMenu->exec(QCursor::pos());
		}
	}
	void ImportTargetWnd::OnSetPartKeyOrLessKey()
	{
		QAction* action = qobject_cast<QAction*>(sender());
		QTreeWidgetItem* currentItem = m_partTree->currentItem();
		QTreeWidgetItem* item = currentItem->clone();
		PartExtraInfo& partInfo = m_targetInfo->GetPartExtraInfo(item->text(0).toLocal8Bit().data());
		if(action == ui->action_Key)
		{
			m_partTree->topLevelItem(0)->addChild(item);
			m_killTreeEditor->AddPartName(item->text(0));
			partInfo.SetPropertyValue("keyPart", "1");
		}
		else
		{
			m_partTree->topLevelItem(1)->addChild(item);
			ui->dockWidget_2->hide();
			m_killTreeEditor->DeletePartName(item->text(0));
			partInfo.SetPropertyValue("keyPart", "0");
		}
		delete currentItem;
	}
	void ImportTargetWnd::OnPartNameChanged(const QString& name)
	{
		QTreeWidgetItem* item = m_partTree->currentItem();
		if(item)
		{
			QString oldName = item->text(0);
			item->setText(0, name);
			m_killTreeEditor->UpdatePartName(oldName, name);
			m_targetInfo->UpdatePartName(oldName.toLocal8Bit().data(), name.toLocal8Bit().data());
			m_targetVisual->UpdatePartName(oldName.toLocal8Bit().data(), name.toLocal8Bit().data());
			m_lastKeyPart = name;
			m_lastDrawPart = name;
		}
	}
	bool ImportTargetWnd::OpenTarget(const QString& fileName)
	{
		bool bResult = false;
		if(m_targetVisual->LoadFile(fileName.toLocal8Bit().data(), m_targetInfo))
		{
			UpdatePartTree();
			m_killTreeEditor->SetTargetKillTree(m_targetInfo->GetKillTreeText());
			ui->dockWidget->show();
			m_lastDrawPart.clear();
			m_lastKeyPart.clear();
			ui->dockWidget_2->hide();
			bResult = true;
		}
		return bResult;
	}
	void ImportTargetWnd::OnOpenTarget()
	{
		QString fileName = 
			QFileDialog::getOpenFileName(
			this,
			QString::fromLocal8Bit("打开目标"), QDir::currentPath(),
			QString::fromLocal8Bit("文件(*.vrs)") );
		if(fileName.right(4).toLower() == QString::fromLocal8Bit(".vrs"))
		{
			if(!OpenTarget(fileName))
			{
				QMessageBox::question(this, QString::fromLocal8Bit("打开目标"), QString::fromLocal8Bit("打开失败！"));
			}
		}
		else if(fileName.size()>0)
		{
			QMessageBox::question(this, QString::fromLocal8Bit("打开目标"), QString::fromLocal8Bit("目标类型不支持！"));
		}
	}
	bool ImportTargetWnd::ImportTarget(const QString& fileName)
	{
		bool bResult = false;
		if(m_targetVisual->LoadFile(fileName.toLocal8Bit().data(), m_targetInfo))
		{
			UpdatePartTree();
			m_killTreeEditor->SetTargetKillTree(m_targetInfo->GetKillTreeText());
			ui->dockWidget->show();
			m_lastDrawPart.clear();
			m_lastKeyPart.clear();
			ui->dockWidget_2->hide();
			bResult = true;
		}
		return bResult;
	}

	void ImportTargetWnd::OnImportTarget()
	{
		QString fileName = 
			QFileDialog::getOpenFileName(
			this,
			QString::fromLocal8Bit("导入目标"), QDir::currentPath(),
			QString::fromLocal8Bit("文件(*.fbx *.*)") );
		if (!fileName.isEmpty())	
		{
			if(ImportTarget(fileName))
			{
				UpdatePartTree();
				ui->dockWidget->show();
				m_lastDrawPart.clear();
				m_lastKeyPart.clear();
				ui->dockWidget_2->hide();
			}
			else
			{
				QMessageBox::question(this, QString::fromLocal8Bit("导入目标"), QString::fromLocal8Bit("导入目标失败！"));
			}
		}
	}
	void ImportTargetWnd::OnSaveTarget()
	{
		QString fileName = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("保存目标"), "./target.vrs", tr("文件(*.vrs)"));
		if(fileName.size()>0)
		{
			 if(!SaveTarget(fileName.toLocal8Bit().data()))
			 {
				 QMessageBox::question(this, QString::fromLocal8Bit("保存目标"), QString::fromLocal8Bit("保存失败！"));
			 }
		}
	}
	bool ImportTargetWnd::SaveTarget(const QString& fileName)
	{
		QTreeWidgetItem* item = m_partTree->currentItem();
		if(item)
			OnItemClicked(item, 0);
		m_targetInfo->SetKillTreeText(m_killTreeEditor->GetTargetKillTree());
		return m_targetInfo->SaveTarget(fileName.toLocal8Bit().data());
	}
	QTreeWidgetItem* ImportTargetWnd::NewPartListItem()
	{
		QTreeWidgetItem* item = new QTreeWidgetItem;
		return item;
	}

	QTreeWidgetItem* ImportTargetWnd::NewPartEditorItem(const QString& text)
	{
		QTreeWidgetItem* item = new QTreeWidgetItem;
		item->setText(0, text);
		return item;
	}

	void ImportTargetWnd::InitPartEditorTree()
	{

	}

	void ImportTargetWnd::onExit()
	{
		QApplication::quit();
	}

}