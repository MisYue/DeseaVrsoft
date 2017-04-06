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

	//�ļ�·��,�ļ�����
	void PaintStart(const QString& strKillTreeText/*QString strPathName, QString strFileName*/);
	void DelArray();			//ɾ���ڵ����

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

	//����ͼƬ
	bool SaveKillTreePic(QString strPath);

public slots:
	//����
	void RefreshNode();

protected:
	void InitArray();			//��ʼ���ڵ����
	
	void ParseKTInfo();			//������������Ϣ

	void CreateNodeParentInfo();
	void EditKTInfoListInfo(int nLine, QString strNodeID, QString strParentNodeID);
	KTSubEvent GetSubEventNum(int nLine, int nNum);								//��ȡ�ڵ����¼�����

	//���������ڵ�λ����Ϣ
	void CreateKillTreeNdoeInfo();
	//�ݹ��ƶ��ڵ�λ��
	void MoveNodePoint(QString strID, int nX, int nY);

	//////////////////////////////////////////////////////////////////////////
	bool IsSeatOccupy(int nX, int nY);											//�ж�λ���Ƿ�ռ��
	void EditKTInfo(QString strID, int nLine, int nX, int nY);					//�޸Ľڵ�λ��

	//ͨ���к���X,Y������Ϣ�����ҽڵ�ID
	QString FindNodeID(int nLine, int nX, int nY);
	//ͨ���к���ڵ�ID�����ҽڵ���Ϣ
	KTInfo FindKTInfo(int nLine, QString strID);
	KTInfo FindKTInfo(int nLine, int nNum);

	//ͨ���ڵ�ID�����ҽڵ���Ϣ
	KTInfo FindKTInfo(QString strID);

	//////////////////////////////////////////////////////////////////////////
	//���½ڵ�ID��ڵ�������Ϣ
	void RefreshKTInfoMap();

	double FindChildLenght(QString strID);
	void CalcNodePosition();
	int FindMaxCol();
	//////////////////////////////////////////////////////////////////////////
	//����
	void addNode(KTInfo ktInfo);
	void DrawLine(QString strID, double fLineDistance, double dX, double dY);

public:
	QGraphicsScene* scene;

private:
	int** pNodeArray;			//�ڵ��������

	QString m_strPathName;
	QString m_strFileName;
	QString m_strKillTreeText;

	double nWidth;
	double nHeight;
	double m_fSingleHeight;
	double m_fSingleWidth;
	double m_fLineDistance;

	//�ڵ��ϵ
	QList<KTInfo>		  listKT;
	QMap<int, QList<KTInfo> >    mapTempKT;
	QMap<int, QList<KTInfo> >    mapFirstKT;
	QMap<int, QList<KTInfo> >    mapSecondKT;

	QMap<QString, KTInfo>		 mapKTInfo;			//�ڵ�ID��ڵ�������Ϣ

	//�ڵ��¼�����
	QList<KTSubEvent>		listSubEvent;
	QMap<int, QList<KTSubEvent>> mapKTSubEvent;
	int		m_nSubEventFlag;	//���ڵ��¼���

	//���ڵ����ӽڵ��ϵ
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