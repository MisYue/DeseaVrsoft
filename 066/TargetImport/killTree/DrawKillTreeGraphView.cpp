#include "DrawKillTreeGraphView.h"

#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>

DrawKillTree::DrawKillTree(QWidget *parent)
{
	nWidth = 1000;
	nHeight = 800;
	
	scene = new QGraphicsScene(this);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	scene->setSceneRect(0, 0, nWidth, nHeight);
	setScene(scene);
	setCacheMode(CacheBackground);
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(AnchorUnderMouse);

	myBackgroundColor = Qt::white;
	myNodeTextColor = Qt::darkGreen;
	myNodeLineColor = QColor(225, 238, 245);/*Qt::darkBlue;*/
	myNodeBackgroundColor = /*Qt::blue;*/QColor(225, 238, 245);
	myTextFlag = true;
	//setAttribute(Qt::WA_DeleteOnClose);
	m_fSingleWidth = 0.0;
	m_fSingleHeight = 0.0;
	m_fLineDistance = 0.0;

	m_strPathName = "";
	m_strFileName = "";
	m_strKillTreeText = "";
	InitArray();

	m_Timer = new QTimer(this);
	ConnectEvent();
}

void DrawKillTree::ConnectEvent()
{
	connect(m_Timer, SIGNAL(timeout()), this, SLOT(RefreshNode()));
}

//初始化节点矩阵
void DrawKillTree::InitArray()
{
	pNodeArray = new int*[512];
	for(int i = 0; i < 512; i++)
	{
		pNodeArray[i] = new int[50];
	}

	for(int i = 0; i < 512; i++)
	{
		for(int j = 0; j < 50; j++)
		{
			pNodeArray[i][j] = 0;
		}
	}
}

//删除节点矩阵
void DrawKillTree::DelArray()
{
	for (int i = 0 ; i < 512; ++i)
	{
		delete [] pNodeArray[i];
	}
	delete [] pNodeArray;
}

void DrawKillTree::PaintStart(const QString& strKillTreeText/*QString strPathName, QString strFileName*/)
{
	//m_strPathName = strPathName;
	//m_strFileName = strFileName;

	m_strKillTreeText = strKillTreeText;
	ParseKTInfo();

	CreateKillTreeNdoeInfo();

	int nMaxCol = FindMaxCol();
	int nLine = mapTempKT.size();
	m_fSingleHeight = 150;
	m_fSingleWidth = 150;
	nWidth = nMaxCol*m_fSingleWidth + 250;
	nHeight = m_fSingleHeight*nLine + 60;
	scene->setSceneRect(0,0, nWidth, nHeight);

	RefreshNode();
}

//解析文件
void DrawKillTree::ParseKTInfo()
{
	mapTempKT.clear();
	mapFirstKT.clear();
	mapSecondKT.clear();
	mapKTInfo.clear();
	mapKTSubEvent.clear();
	listKT.clear();
	listSubEvent.clear();
	listChildren.clear();
	mapNodeChildren.clear();
	listPoint.clear();
	mapItemPoint.clear();
	m_nSubEventFlag = 0;

	InitArray();
	//QString strTemp = m_strPathName + "/"+ m_strFileName;
	//QFile File(strTemp);
	//if(File.open(QIODevice::ReadOnly))
	if(m_strKillTreeText.size()>0)
	{
		//QTextStream stream( &File );
		QTextStream stream( &m_strKillTreeText );

		QString str;
		stream>>str;
		int nKillTreeFlag = str.toInt();

		while (!stream.atEnd())
		{

			KTInfo ktInfo;
			stream>>str;
			ktInfo.nEventLevel = str.toInt();

			stream>>str;
			ktInfo.strID = str;

			stream>>str;
			ktInfo.strEventName = str;

			stream>>str;
			ktInfo.nSubEventNum = str.toInt();

			stream>>str;
			ktInfo.nDoorType = str.toInt();

			stream>>str;
			ktInfo.nPrepare = str.toInt();

			//毁伤树信息
			if(ktInfo.nEventLevel > 0)
			{
				QMap<int, QList<KTInfo>>::iterator it = mapTempKT.find(ktInfo.nEventLevel);
				if(it != mapTempKT.end())
				{
					it.value().push_back(ktInfo);
				}
				else
				{
					listKT.clear();
					listKT.push_back(ktInfo);
					mapTempKT[ktInfo.nEventLevel] = listKT;
				}
			}

			//节点事件个数
			KTSubEvent ktSubEvnet;
			if(ktInfo.nSubEventNum > 0 && ktInfo.nEventLevel > 0)
			{
				ktSubEvnet.strNodeID = ktInfo.strID;
				ktSubEvnet.nSubEventNum = ktInfo.nSubEventNum;
				QMap<int, QList<KTSubEvent> >::iterator itSubEvent = mapKTSubEvent.find(ktInfo.nEventLevel);
				if(itSubEvent != mapKTSubEvent.end())
				{
					itSubEvent.value().push_back(ktSubEvnet);
				}
				else
				{
					listSubEvent.clear();
					listSubEvent.push_back(ktSubEvnet);
					mapKTSubEvent[ktInfo.nEventLevel] = listSubEvent;
				}
			}
		}
		//File.close();
	}
	CreateNodeParentInfo();
}

//分析父子关系
void DrawKillTree::CreateNodeParentInfo()
{
	m_nSubEventFlag = 0;
	KTSubEvent ktSubEvent;
	int nSubEventFlag = 0;
	//////////////////////////////////////////////////////////////////////////
	QMap<int, QList<KTInfo>>::iterator it = mapTempKT.begin();
	for(int i = 0; it != mapTempKT.end() && i < mapTempKT.size(); it++, i++)
	{
		nSubEventFlag = 0;
		if(i == 0)
		{
			KTInfo ktInfo = it.value().at(0);
			listKT.clear();
			listKT.push_back(ktInfo);
			mapFirstKT[ktInfo.nEventLevel] = listKT;
		}
		else
		{
			int nItemCount = it.value().size();
			ktSubEvent = GetSubEventNum(i, 0);
			m_nSubEventFlag = ktSubEvent.nSubEventNum;
			for(int j = 0; j < nItemCount; j++)
			{
				KTInfo ktInfo = it.value().at(j);
				if(m_nSubEventFlag > 0)
				{
					EditKTInfoListInfo(i+1, ktInfo.strID, ktSubEvent.strNodeID);
					m_nSubEventFlag--;
				}
				else
				{
					nSubEventFlag++;
					ktSubEvent = GetSubEventNum(i, nSubEventFlag);
					m_nSubEventFlag = ktSubEvent.nSubEventNum;
					EditKTInfoListInfo(i+1, ktInfo.strID, ktSubEvent.strNodeID);
					m_nSubEventFlag--;
				}
			}
		}
	}
}

void DrawKillTree::EditKTInfoListInfo(int nLine, QString strNodeID,QString strParentNodeID)
{
	QMap<int, QList<KTInfo>>::iterator it = mapTempKT.find(nLine);
	if(it != mapTempKT.end())
	{
		int nCount = it.value().size();
		for(int i = 0; i < nCount; i++)
		{
			KTInfo ktInfo = it.value().at(i);
			if(strNodeID == ktInfo.strID)
			{
				ktInfo.strParentID = strParentNodeID;

				QMap<int, QList<KTInfo>>::iterator it = mapFirstKT.find(ktInfo.nEventLevel);
				if(it != mapFirstKT.end())
				{
					it.value().push_back(ktInfo);
				}
				else
				{
					listKT.clear();
					listKT.push_back(ktInfo);
					mapFirstKT[ktInfo.nEventLevel] = listKT;
				}
			}
		}
	}

	//节点下的子节点ID
	QMap<QString, QList<QString>>::iterator itChild = mapNodeChildren.find(strParentNodeID);
	if(itChild != mapNodeChildren.end())
	{
		itChild.value().push_back(strNodeID);
	}
	else
	{
		listChildren.clear();
		listChildren.push_back(strNodeID);
		mapNodeChildren[strParentNodeID] = listChildren;
	}
}

KTSubEvent DrawKillTree::GetSubEventNum(int nLine, int nNum)
{
	KTSubEvent ktSubEvent;
	QMap<int, QList<KTSubEvent>>::iterator itSubEvent = mapKTSubEvent.find(nLine);
	if(itSubEvent != mapKTSubEvent.end())
	{
		KTSubEvent ktSubEvent = itSubEvent.value().at(nNum);
		return ktSubEvent;
	}
	return ktSubEvent;
}

//////////////////////////////////////////////////////////////////////////
//创建解析节点位子信息
void DrawKillTree::CreateKillTreeNdoeInfo()
{
	int nParentX = 0;
	int x = 0;
	int y = 0;
	//////////////////////////////////////////////////////////////////////////
	QMap<int, QList<KTInfo>>::iterator it = mapFirstKT.begin();
	for(int i = 0; it != mapFirstKT.end() && i < mapFirstKT.size(); it++, i++)
	{
		int nItemCount = it.value().size();
		for(int j = 0; j < nItemCount; j++)
		{
			KTInfo ktInfo = it.value().at(j);
			if(i == 0)
			{
				x = i;
				y = j;
				pNodeArray[x][y] = 1;
				EditKTInfo(ktInfo.strID, i, x, y);
			}
			else
			{
				if(j == 0)
				{
					KTInfo parentKtInfo = FindKTInfo(i, ktInfo.strParentID);
					nParentX = parentKtInfo.nCol;
					x = nParentX;
				}
				else
				{
					x = nParentX + j;
				}
				y = i;

				if(!IsSeatOccupy(x,y))
				{
					pNodeArray[x][y] = 1;
					EditKTInfo(ktInfo.strID, i, x, y);

					if(IsSeatOccupy(x, y-1))
					{
						QString strID = FindNodeID(y-1, x, y-1);
						if(strID != ktInfo.strParentID)
						{
							MoveNodePoint(strID, x, y-1);
						}
					}
				}
				else
				{
					while(IsSeatOccupy(x, y))
					{
						x = x + 1;
					}

					pNodeArray[x][y] = 1;
					EditKTInfo(ktInfo.strID, i, x, y);

					if(IsSeatOccupy(x, y-1))
					{
						QString strID = FindNodeID(y-1, x, y-1);
						if(strID != ktInfo.strParentID)
						{
							MoveNodePoint(strID, x, y-1);
						}
					}
				}
			}
		}
	}
	//更新节点ID与节点所有信息
	RefreshKTInfoMap();
	CalcNodePosition();
}

//////////////////////////////////////////////////////////////////////////
//递归移动节点位子
void DrawKillTree::MoveNodePoint(QString strID, int nX, int nY)
{
	if(!IsSeatOccupy(nX, nY-1))
	{	
		if(!IsSeatOccupy(nX+1, nY))
		{
			pNodeArray[nX+1][nY] = 1;
			pNodeArray[nX][nY] = 0;
			EditKTInfo(strID, nY, nX+1, nY);
		}
		else
		{
			QString strRightID = FindNodeID(nY, nX+1, nY);
			MoveNodePoint(strRightID, nX+1, nY);
			MoveNodePoint(strID, nX, nY);
		}
	}
	else
	{
		QString strParentID = FindNodeID(nY-2, nX, nY-1);
		MoveNodePoint(strParentID, nX, nY-1);
	}
}

//////////////////////////////////////////////////////////////////////////
//修改节点位子
void DrawKillTree::EditKTInfo(QString strID, int nLine, int nX, int nY)
{
	bool bFlag = true;
	QMap<int, QList<KTInfo>>::iterator it = mapFirstKT.find(nLine+1);
	if(it != mapFirstKT.end())
	{
		int nItemCount = it.value().size();
		for(int i = 0; i < nItemCount; i++)
		{
			KTInfo editKTinfo = it.value().at(i);
			if(editKTinfo.strID == strID)
			{
				editKTinfo.nCol = nX;
				editKTinfo.nRow = nY;

				QMap<int, QList<KTInfo>>::iterator itSecond = mapSecondKT.find(nLine+1);
				if(itSecond != mapSecondKT.end())
				{
					int nItemCount = itSecond.value().size();
					for(int i = 0; i < nItemCount; i++)
					{
						KTInfo secondKTinfo = itSecond.value().at(i);
						if(secondKTinfo.strID == strID)
						{
							itSecond.value().removeAt(i);
							itSecond.value().push_back(editKTinfo);
							bFlag = false;
						}
					}
					if(bFlag)
					{
						itSecond.value().push_back(editKTinfo);
					}
				}
				else
				{
					listKT.clear();
					listKT.push_back(editKTinfo);
					mapSecondKT[editKTinfo.nEventLevel] = listKT;
				}
				break;
			}
		}
	}
}

//判断位置是否被占用
bool DrawKillTree::IsSeatOccupy(int nX, int nY)
{
	if(nX > 0)
	{
		int k  = nX;
	}
	int nFlag = pNodeArray[nX][nY];
	if(nFlag == 1)
	{
		return true;
	}
	return false;
}

//通过行号与节点ID，查找节点信息
KTInfo DrawKillTree::FindKTInfo(int nLine, QString strID)
{
	KTInfo ktInfo;
	QMap<int, QList<KTInfo> > ::iterator it = mapSecondKT.find(nLine);
	if(it != mapSecondKT.end())
	{
		int nIndex = it.value().size();
		for(int i = 0; i < nIndex; i++)
		{
			ktInfo = (KTInfo)(it.value().at(i));
			if(strID == ktInfo.strID)
			{
				return ktInfo;
			}
		}
	}
	return ktInfo;
}

//通过行号与X,Y坐标信息，查找节点ID
QString DrawKillTree::FindNodeID(int nLine, int nX, int nY)
{
	QString strID = "";
	QMap<int, QList<KTInfo>>::iterator it = mapSecondKT.find(nLine+1);
	if(it != mapSecondKT.end())
	{
		int nItemCount = it.value().size();
		for(int i = 0; i < nItemCount; i++)
		{
			KTInfo ktInfo = it.value().at(i);
			if((ktInfo.nCol == nX) && (ktInfo.nRow == nY))
			{
				strID = ktInfo.strID;
			}
		}
	}
	return strID;
}

KTInfo DrawKillTree::FindKTInfo(int nLine, int nNum)
{
	KTInfo ktInfo;
	QMap<int, QList<KTInfo> > ::iterator it = mapSecondKT.find(nLine);
	if(it != mapSecondKT.end())
	{
		ktInfo = (KTInfo)(it.value().at(nNum));
	}
	return ktInfo;
}

//通过节点ID，查找节点信息
KTInfo DrawKillTree::FindKTInfo(QString strID)
{
	KTInfo ktInfo;
	QMap<QString, KTInfo>::iterator it = mapKTInfo.find(strID);
	if(it != mapKTInfo.end())
	{
		ktInfo = it.value();
	}
	return ktInfo;
}

//更新节点ID与节点所有信息
void DrawKillTree::RefreshKTInfoMap()
{
	QMap<int, QList<KTInfo> > ::iterator it = mapSecondKT.begin();
	for(; it != mapSecondKT.end(); it++)
	{
		for(int i = 0; i < it.value().size(); i++)
		{
			KTInfo ktInfo = it.value().at(i);
			QMap<QString, KTInfo>::iterator itKTInfo = mapKTInfo.find(ktInfo.strID);
			if(itKTInfo != mapKTInfo.end())
			{
				itKTInfo.value() = ktInfo;
			}
			else
			{
				mapKTInfo[ktInfo.strID] = ktInfo;
			}
		}
	}
}

double DrawKillTree::FindChildLenght(QString strID)
{
	double dLenght = 0.0;
	int dMin = 0.0;
	int dMax = 0.0;
	QMap<QString, QList<QString>>::iterator it = mapNodeChildren.find(strID);
	if(it != mapNodeChildren.end())
	{
		for(int i = 0; i < it.value().size(); i++)
		{
			QString strNodeID = it.value().at(i);
			KTInfo ktInfo = FindKTInfo(strNodeID);
			if(i == 0)
			{
				dMax = ktInfo.nCol;
				dMin = ktInfo.nCol;
			}
			if(dMax < ktInfo.nCol)
			{
				dMax = ktInfo.nCol;
			}
			if(dMin > ktInfo.nCol)
			{
				dMin = ktInfo.nCol;
			}
		}
		dLenght = dMax - dMin;
		dLenght = dMin + dLenght/2;
	}
	return dLenght;
}

void DrawKillTree::CalcNodePosition()
{
	//////////////////////////////////////////////////////////////////////////
	//计算节点放置位置
	int nCount = mapSecondKT.size();
	QMap<int, QList<KTInfo>>::iterator itKT = mapSecondKT.end();
	itKT = itKT - 1;
	for(int i = nCount - 1; i >= 0; --itKT, i--)
	{
		int nItemCount = itKT.value().size();
		for(int j = 0; j < nItemCount; j++)
		{
			KTInfo ktInfo = itKT.value().at(j);
			if(!ktInfo.strParentID.isEmpty())
			{
				double dLength = FindChildLenght(ktInfo.strParentID);
				QMap<QString, KTInfo>::iterator  itNode = mapKTInfo.find(ktInfo.strParentID);
				if(itNode != mapKTInfo.end())
				{
					itNode.value().nCol = dLength;
				}
			}
		}
	}
}

int DrawKillTree::FindMaxCol()
{
	int nMaxCol = 0;
	QMap<QString, KTInfo>::iterator  itNode = mapKTInfo.begin();
	for(; itNode != mapKTInfo.end(); itNode++)
	{
		if(nMaxCol < itNode.value().nCol)
		{
			nMaxCol = itNode.value().nCol;
		}
	}
	return nMaxCol;
}
//////////////////////////////////////////////////////////////////////////
//绘制
void DrawKillTree::RefreshNode()
{
	scene->clear();
	scene->setBackgroundBrush(myBackgroundColor);
	//////////////////////////////////////////////////////////////////////////
	//绘制图像
	QMap<int, QList<KTInfo> > ::iterator it = mapSecondKT.begin();
	for(; it != mapSecondKT.end(); it++)
	{
		for(int i = 0; i < it.value().size(); i++)
		{
			addNode(it.value().at(i));
		}
	}
}

void DrawKillTree::addNode(KTInfo ktInfo)
{
	KTInfo DrawKTInfo = FindKTInfo(ktInfo.strID);
	Node* node=new Node();
	if(myTextFlag)
	{
		node->setText(DrawKTInfo.strEventName);
	}
	else
	{
		node->setText(DrawKTInfo.strID);
	}
	node->SetNodeSubEvent(DrawKTInfo.nSubEventNum);

	node->setTextColor(myNodeTextColor);
	node->setOutlineColor(myNodeLineColor);
	node->setBackgroundColor(myNodeBackgroundColor);

	double dX = 0.0;
	double dY = 0.0;

	dX = m_fSingleWidth*DrawKTInfo.nCol + 50;
	dY = m_fSingleHeight*DrawKTInfo.nRow + 30;

	node->setPos(dX, dY);

	LogicalGate* logicalGate = new LogicalGate(DrawKTInfo.nDoorType);
	if(DrawKTInfo.nDoorType == 3)
	{
		QString strName;
		strName = QString::number(DrawKTInfo.nPrepare) + QString::fromLocal8Bit("/") + QString::number(DrawKTInfo.nSubEventNum);
		logicalGate->setText(strName);
	}
	logicalGate->setPos(dX-22.5,dY+20);

	scene->addItem(node);
	scene->addItem(logicalGate);

	if(DrawKTInfo.nSubEventNum > 0)
	{
		Link* link1=new Link(QPointF(dX, dY + 15.0), QPointF(dX, dY + 40));
		scene->addItem(link1);

		m_fLineDistance = 55;
		Link* link2=new Link(QPointF(dX, dY + 80), QPointF(dX, dY + 80 + m_fLineDistance/2));
		scene->addItem(link2);
		DrawLine(DrawKTInfo.strID, m_fLineDistance, dX, dY + 80 + m_fLineDistance/2);
	}

	//scene->clearSelection();
	//node->setSelected(true);
}



//////////////////////////////////////////////////////////////////////////
void DrawKillTree::DrawLine(QString strID, double fLineDistance, double dX, double dY)
{
	QMap<QString, QList<QString>>::iterator it = mapNodeChildren.find(strID);
	if(it != mapNodeChildren.end())
	{
		for(int i = 0; i < it.value().size(); i++)
		{
			KTInfo ktInfo = FindKTInfo(it.value().at(i));
			double dChildX = ktInfo.nCol*m_fSingleWidth + 50;
			double dChildY = ktInfo.nRow*m_fSingleHeight + 30;

			Link* link1=new Link(QPointF(dChildX, dChildY - 15.0), QPointF(dChildX, dChildY - 15.0 - fLineDistance/2));
			scene->addItem(link1);

 			Link* link2=new Link(QPointF(dX, dY), QPointF(dChildX, dChildY - 15.0 - fLineDistance/2));
 			scene->addItem(link2);
		}
	}
}

//保存图片
bool DrawKillTree::SaveKillTreePic(QString strPath)
{
	bool bResult = false;
	int x = 0;
	int y = 0;
	int w = scene->width();
	int h = scene->height();

	QImage image(w, h, QImage::Format_ARGB32);
	QRgb qRgb = myBackgroundColor.rgb();
	image.fill(qRgb);

	QPainter painter(&image);
 	painter.setRenderHint(QPainter::Antialiasing);
 	scene->render(&painter);   //关键函数

	bResult = image.save(strPath, "PNG");
	return bResult;
}