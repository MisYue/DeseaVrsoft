//***************************************
//	创建时间:	2015:11:3   17:39
//	文件名称: 	ImportTargetWnd.h
//	文件作者:	岳群磊
//	
//	功能说明:	定义主窗口类
//***************************************

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "TargetImportGlobal.h"


#include <QtWidgets>

class PartEditor;
class KillTreeEditor;
class KillTreeRenderer;
class DDTreeWidget;
namespace osg
{
	class Group;
	class Node;
}
namespace Ui
{
	class MainWindowClass;
}
namespace TIMP
{
	class TargetVisual;
	class TargetInfo;

	class TARGETIMPORT_API ImportTargetWnd : public QMainWindow
	{
		Q_OBJECT
	public:
		ImportTargetWnd(QWidget *parent = 0, Qt::WindowFlags flags = 0);
		~ImportTargetWnd();
		void HideToolBar();
		bool SaveTarget(const QString& fileName);
		bool OpenTarget(const QString& fileName);
		bool ImportTarget(const QString& fileName);
		void Reset();
		bool DeleteTarget();
private slots:
	void OnOpenTarget();
	void OnImportTarget();
	void OnSaveTarget();
	void OnSetPartKeyOrLessKey();
	void OnPartNameChanged(const QString& name);
	void OnItemClicked(QTreeWidgetItem* item, int column);
	void OnTreeWidgetCustomContextMenu(QPoint);
	void onExit();

	private:
		Ui::MainWindowClass* ui;
		void CreateActions();
		QTreeWidgetItem* NewPartListItem();
		QTreeWidgetItem* NewPartEditorItem(const QString& text);
		void InitPartEditorTree();
		void UpdatePartTree();
		TargetInfo* m_targetInfo;
		DDTreeWidget* m_partTree;
		PartEditor* m_partEditor;
		TargetVisual* m_targetVisual;
		KillTreeEditor* m_killTreeEditor;
		KillTreeRenderer* m_killTreeRender;
		QString m_lastDrawPart;
		QString m_lastKeyPart;
	};
}
#endif // MAINWINDOW_H
