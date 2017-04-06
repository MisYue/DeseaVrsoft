#pragma once

#include <QtWidgets>
#include "Node.h"
#include "Link.h"
#include "LogicalGate.h"
#include "../structHead.h"

class DrawKillTree : public QGraphicsView
{
	Q_OBJECT

public:
	DrawKillTree(QWidget *parent = 0);

	void ConnectEvent();

	//文件路径,文件名称
	void PaintStart(const QString& strKillTreeText/*QString strPathName, QString strFileName*/);
	void DelArray();			//删除节点矩阵

	void setBackgroundColor(const QColor& color)		{ myBackgroundColor = color; }
	QColor getBackgroundColor()		{ return myBackgroundColor; }
	void setNodeTextColor(const QColor& color)			{ myNodeTextColor = color; }		
	void setNodeOutLineColor(const QColor& color)		{ myNodeLineColor = color; }
	void setNodeBackgroundColor(const QColor& color)	{ myNodeBackgroundColor = color; }
	void setNodeNameOrID(bool bFlag)		{ myTextFlag = bFlag; }

	void setZoomIn()		
	{
		
		scale( 1.05,  1.05);  
	}
	void setZoomOut()		
	{ 
		scale( 0.95, 0.95 ); 
	}

	void StartTimer()	{ m_Timer->start(200); }
	void StopTimer()	{ m_Timer->stop(); }

	//保存图片
	bool SaveKillTreePic(QString strPath);

public slots:
	//绘制
	void RefreshNode();

protected:
	void InitArray();			//初始化节点矩阵
	
	void ParseKTInfo();			//解析毁伤树信息

	void CreateNodeParentInfo();
	void EditKTInfoListInfo(int nLine, QString strNodeID, QString strParentNodeID);
	KTSubEvent GetSubEventNum(int nLine, int nNum);								//获取节点子事件个数

	//创建解析节点位子信息
	void CreateKillTreeNdoeInfo();
	//递归移动节点位子
	void MoveNodePoint(QString strID, int nX, int nY);

	//////////////////////////////////////////////////////////////////////////
	bool IsSeatOccupy(int nX, int nY);											//判断位置是否被占用
	void EditKTInfo(QString strID, int nLine, int nX, int nY);					//修改节点位子

	//通过行号与X,Y坐标信息，查找节点ID
	QString FindNodeID(int nLine, int nX, int nY);
	//通过行号与节点ID，查找节点信息
	KTInfo FindKTInfo(int nLine, QString strID);
	KTInfo FindKTInfo(int nLine, int nNum);

	//通过节点ID，查找节点信息
	KTInfo FindKTInfo(QString strID);

	//////////////////////////////////////////////////////////////////////////
	//更新节点ID与节点所有信息
	void RefreshKTInfoMap();

	double FindChildLenght(QString strID);
	void CalcNodePosition();
	int FindMaxCol();
	//////////////////////////////////////////////////////////////////////////
	//绘制
	void addNode(KTInfo ktInfo);
	void DrawLine(QString strID, double fLineDistance, double dX, double dY);

public:
	QGraphicsScene* scene;

private:
	int** pNodeArray;			//节点矩阵数组

	QString m_strPathName;
	QString m_strFileName;
	QString m_strKillTreeText;

	double nWidth;
	double nHeight;
	double m_fSingleHeight;
	double m_fSingleWidth;
	double m_fLineDistance;

	//节点关系
	QList<KTInfo>		  listKT;
	QMap<int, QList<KTInfo> >    mapTempKT;
	QMap<int, QList<KTInfo> >    mapFirstKT;
	QMap<int, QList<KTInfo> >    mapSecondKT;

	QMap<QString, KTInfo>		 mapKTInfo;			//节点ID与节点所有信息

	//节点事件数量
	QList<KTSubEvent>		listSubEvent;
	QMap<int, QList<KTSubEvent>> mapKTSubEvent;
	int		m_nSubEventFlag;	//单节点事件数

	//父节点与子节点关系
	QList<QString>					listChildren;
	QMap<QString, QList<QString>>   mapNodeChildren;

	QList<QPointF>				listPoint;
	QMap<int, QList<QPointF>>	mapItemPoint;

	QColor myNodeTextColor;
	QColor myNodeLineColor;
	QColor myNodeBackgroundColor;
	QColor myBackgroundColor;
	bool   myTextFlag;

	QTimer*			m_Timer;
};