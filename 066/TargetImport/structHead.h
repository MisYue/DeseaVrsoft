//***************************************
//	创建时间:	2015:10:26   17:37
//	文件名称: 	structHead.h
//	文件作者:	皮敏
//	
//	功能说明:	定义相关结构
//***************************************

#pragma once
#include <osg/Referenced>
#include <string>
#include <QtCore/QVariant>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/NodeVisitor>
#include <osgDB/WriteFile>
#include <osgViewer/Viewer>
#include <iostream> 
#include <fstream>
#include <QStringList>
#include <osgDB/ReadFile>
#include <osg/Node> 
#include <osgAnimation/AnimationManagerBase>
#include <osgAnimation/BasicAnimationManager>
#include <osg/AnimationPath>
#include <osgUtil/Statistics>
#include <osgSim/DOFTransform>
#include <osgSim/MultiSwitch>
#include <osg/Texture2D>
#include <osg/Material>

class FindNamedNodeVisitor : public osg::NodeVisitor
{
public:
	FindNamedNodeVisitor::FindNamedNodeVisitor(const std::string &name)
		: osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN),
		_name(name)
	{}
	virtual void FindNamedNodeVisitor::apply(osg::Node& node)
	{
		if(node.getName() == _name)
		{
			_foundNodes.push_back(&node);
		}
		traverse(node);
	}
	typedef std::vector< osg::ref_ptr<osg::Node> >  NodeList;
	std::string _name;
	NodeList	_foundNodes;
};
class WindowCaptureCallback : public osg::Camera::DrawCallback
{
public:    
	WindowCaptureCallback(GLenum readBuffer, const std::string& name):
	  _readBuffer(readBuffer),
		  _fileName(name)
	  {
		  _image = new osg::Image;
	  }

	  virtual void operator () (osg::RenderInfo& renderInfo) const
	  {
		  glReadBuffer(_readBuffer);
		  //OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
		  osg::GraphicsContext* gc = renderInfo.getState()->getGraphicsContext();
		  if (gc->getTraits())
		  {
			  GLenum pixelFormat;
			  if (gc->getTraits()->alpha)
				  pixelFormat = GL_RGBA;
			  else 
				  pixelFormat = GL_RGB;

			  int width = gc->getTraits()->width;
			  int height = gc->getTraits()->height;

			  std::cout<<"Capture: size="<<width<<"x"<<height<<", format="<<(pixelFormat == GL_RGBA ? "GL_RGBA":"GL_RGB")<<std::endl;

			  _image->readPixels(0, 0, width, height, pixelFormat, GL_UNSIGNED_BYTE);
		  }

		  if (!_fileName.empty())
		  {
			  std::cout << "Writing to: " << _fileName << std::endl;
			  bool bSuc = osgDB::writeImageFile(*_image, _fileName);

			  if (bSuc)
			  { 
				  //_mutex.unlock();

				  renderInfo.getCurrentCamera()->setFinalDrawCallback(NULL);
			  } 
		  }
	  }
protected:    
	GLenum                      _readBuffer;
	std::string                 _fileName;
	osg::ref_ptr<osg::Image>    _image;
	mutable OpenThreads::Mutex  _mutex;
};

class NodeBuf : public std::basic_streambuf<char, std::char_traits<char>>
{
public:
	NodeBuf(char * mem, int sz)
	{
		//参数意义：起始位置，当前位置，最后的位置 
		setg(mem, mem, mem + sz);
	}
	~NodeBuf(void)
	{

	}
};

class ModelNodeVisitor : public osg::NodeVisitor
{
public:
	ModelNodeVisitor()
		: osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
	{
		_amCBs.clear();
		_lods.clear();
		_dofs.clear();
		_mswitchs.clear();
		_geometrys.clear();
		_fastGeometrys.clear();
		_drawables.clear();

		_am = NULL;

		_instancedStats.reset();
	}

	virtual void apply(osg::Group& node)
	{
		if (node.getUpdateCallback()) 
		{
			osgAnimation::AnimationManagerBase* b = 
				dynamic_cast<osgAnimation::AnimationManagerBase*>(node.getUpdateCallback());

			if (b)
			{
				_am = new osgAnimation::BasicAnimationManager(*b);
			}

			osg::ref_ptr<osg::AnimationPathCallback> animation = 
				dynamic_cast<osg::AnimationPathCallback *>(node.getUpdateCallback());
			if (animation)
			{
				_amCBs.push_back(&node);

				osg::AnimationPath *animPath = animation->getAnimationPath();
				animation->setPause(true);
				if (animPath)
				{
					animPath->setLoopMode(osg::AnimationPath::NO_LOOPING);
				}

				animation->setTimeMultiplier(1.0);
			}
		}

		osgSim::MultiSwitch *pSwitch = 
			dynamic_cast<osgSim::MultiSwitch *>(&node);

		if (pSwitch)
		{
			_mswitchs.push_back(&node);
		}

		traverse(node);
	}

	virtual void apply(osg::Transform& node)
	{
		if (node.getUpdateCallback()) 
		{
			osgAnimation::AnimationManagerBase* b = 
				dynamic_cast<osgAnimation::AnimationManagerBase*>(node.getUpdateCallback());

			if (b)
			{
				_am = new osgAnimation::BasicAnimationManager(*b);
			}

			osg::ref_ptr<osg::AnimationPathCallback> animation = 
				dynamic_cast<osg::AnimationPathCallback *>(node.getUpdateCallback());
			if (animation)
			{
				_amCBs.push_back(&node);

				osg::AnimationPath *animPath = animation->getAnimationPath();
				animation->setPause(true);
				if (animPath)
				{
					animPath->setLoopMode(osg::AnimationPath::NO_LOOPING);
				}

				animation->setTimeMultiplier(1.0);
			}
		}

		osgSim::DOFTransform *pDof = 
			dynamic_cast<osgSim::DOFTransform *>(&node);

		if (pDof)
		{
			_dofs.push_back(&node);
		}

		traverse(node);
	}

	virtual void apply(osg::LOD& node)
	{
		if (node.getUpdateCallback()) 
		{
			osgAnimation::AnimationManagerBase* b = 
				dynamic_cast<osgAnimation::AnimationManagerBase*>(node.getUpdateCallback());

			if (b)
			{
				_am = new osgAnimation::BasicAnimationManager(*b);
			}

			osg::ref_ptr<osg::AnimationPathCallback> animation = 
				dynamic_cast<osg::AnimationPathCallback *>(node.getUpdateCallback());
			if (animation)
			{
				_amCBs.push_back(&node);

				osg::AnimationPath *animPath = animation->getAnimationPath();
				animation->setPause(true);
				if (animPath)
				{
					animPath->setLoopMode(osg::AnimationPath::NO_LOOPING);
				}

				animation->setTimeMultiplier(1.0);
			}
		}

		_lods.push_back(&node);

		traverse(node);
	}

	virtual void apply(osg::Geode& node)
	{
		if (node.getUpdateCallback()) 
		{
			osgAnimation::AnimationManagerBase* b = 
				dynamic_cast<osgAnimation::AnimationManagerBase*>(node.getUpdateCallback());

			if (b)
			{
				_am = new osgAnimation::BasicAnimationManager(*b);
			}

			osg::ref_ptr<osg::AnimationPathCallback> animation = 
				dynamic_cast<osg::AnimationPathCallback *>(node.getUpdateCallback());
			if (animation)
			{
				_amCBs.push_back(&node);

				osg::AnimationPath *animPath = animation->getAnimationPath();
				animation->setPause(true);
				if (animPath)
				{
					animPath->setLoopMode(osg::AnimationPath::NO_LOOPING);
				}

				animation->setTimeMultiplier(1.0);
			}
		}

		for(unsigned int i=0; i<node.getNumDrawables();++i)
		{
			apply(*node.getDrawable(i));
		}

		traverse(node);
	}

	virtual void apply(osg::Drawable& drawable)
	{
		drawable.accept(_instancedStats);

		_drawables.push_back(&drawable);

		osg::Geometry* geometry = drawable.asGeometry();
		if (geometry)
		{
			_geometrys.push_back(geometry);

			//if (geometry->areFastPathsUsed())
			//{
			//	_fastGeometrys.push_back(geometry);
			//}
		}
	}

	virtual void apply(osg::Node& node)
	{
		if (node.getUpdateCallback()) 
		{
			osgAnimation::AnimationManagerBase* b = 
				dynamic_cast<osgAnimation::AnimationManagerBase*>(node.getUpdateCallback());

			if (b)
			{
				_am = new osgAnimation::BasicAnimationManager(*b);
			}

			osg::ref_ptr<osg::AnimationPathCallback> animation = 
				dynamic_cast<osg::AnimationPathCallback *>(node.getUpdateCallback());
			if (animation)
			{
				_amCBs.push_back(&node);

				osg::AnimationPath *animPath = animation->getAnimationPath();
				animation->setPause(true);
				if (animPath)
				{
					animPath->setLoopMode(osg::AnimationPath::NO_LOOPING);
				}

				animation->setTimeMultiplier(1.0);
			}
		}

		traverse(node);
	}


	typedef std::vector< osg::AnimationPathCallback * >  AnimationPathCBList;
	typedef std::vector< osg::Node* > NodeList;
	typedef std::vector< osg::Drawable* > DrawableList;
	
	osgUtil::Statistics _instancedStats;
	osg::ref_ptr<osgAnimation::BasicAnimationManager> _am;

	//AnimationPathCBList _amCBs;
	NodeList _amCBs;
	NodeList _lods;
	NodeList _dofs;
	NodeList _mswitchs;

	DrawableList _geometrys;
	DrawableList _fastGeometrys;
	DrawableList _drawables;
};

class FindTextureVisitor : public osg::NodeVisitor
{
public:
	FindTextureVisitor(osg::Node *node)
		: osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
	{
		_pNode = node;

		_strTextList.clear();
	}

	virtual void apply(osg::Geode& geode)
	{
		apply(geode.getStateSet());

		for(unsigned int i=0;i<geode.getNumDrawables();++i)
		{
			apply(geode.getDrawable(i)->getStateSet());
		}

		traverse(geode);
	}

	virtual void apply(osg::Group& node)
	{
		apply(node.getStateSet());

		traverse(node);
	}

	virtual void apply(osg::Node& node)
	{
		apply(node.getStateSet());

		traverse(node);
	}

	inline void apply(osg::StateSet* stateset)
	{
		if (!stateset) 
			return;

		osg::StateSet::TextureAttributeList textureLists = 
			stateset->getTextureAttributeList();

		for( size_t i = 0; i < textureLists.size(); i++ ) 
		{
			osg::StateAttribute* attr = stateset->getTextureAttribute(i,osg::StateAttribute::TEXTURE);
			if (attr)
			{
				osg::Texture2D* texture2D = dynamic_cast<osg::Texture2D*>(attr);
				if (texture2D)
				{
					std::string strFile = texture2D->getImage()->getFileName();

					QString str = QString::fromLocal8Bit(strFile.c_str());

					if (!_strTextList.contains(str))
					{
						_strTextList.push_back(str);
					}

					if (_pNode)
					{
						_pNode->getOrCreateStateSet()->addUniform( new osg::Uniform( "TexUnit", i ) );
					}
				}
			}
		}

		{
			osg::StateAttribute* attr = stateset->getAttribute(osg::StateAttribute::MATERIAL);
			if (attr)
			{
				osg::Material* material = dynamic_cast<osg::Material *>(attr);
				if (material)
				{

				}
			}
		}

	}

	QStringList GetTextureList()
	{
		return _strTextList;
	}

private:
	osg::Node *_pNode;

	QStringList _strTextList;
};

class ShaderCallback: public osg::Uniform::Callback
{
public:
	ShaderCallback(osg::Vec4 color)
	{
		_color = color;
	}

	void SetCurrColor(osg::Vec4 color)
	{
		_color = color;
	}

	osg::Vec4 GetCurrColor()
	{
		return _color;
	}

	virtual void operator() ( osg::Uniform* uniform, osg::NodeVisitor* nv )
	{
		uniform->set( _color );
	}

private:
	osg::Vec4 _color;
};

#pragma once

#include <QList>
#include <QMap>
#include <QMetaType>
#include <QString>
#include <osg/Matrix>
#include <osg/Vec3>

struct PointValue
{
	double x;
	double y;
	double z;

	PointValue()
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}

	PointValue operator=(const PointValue &lhs)
	{
		x = lhs.x;
		y = lhs.y;
		z = lhs.z;

		return *this;
	}
};

struct PointSum
{
	QList<PointValue> pointList;

	PointSum()
	{
		pointList.clear();
	}

	PointSum operator=(const PointSum &lhs)
	{
		pointList.clear();

		QList<PointValue>::const_iterator ite = lhs.pointList.begin();
		while (ite != lhs.pointList.end())
		{
			PointValue pValue = *ite;

			pointList.push_back(pValue);

			++ite;
		}

		return *this;
	}
};

struct PointIndexSum
{
	QList<int> pointIndexList;

	PointIndexSum()
	{
		pointIndexList.clear();
	}

	PointIndexSum operator=(const PointIndexSum &lhs)
	{
		pointIndexList.clear();

		QList<int>::const_iterator ite = lhs.pointIndexList.begin();
		while (ite != lhs.pointIndexList.end())
		{
			int value = *ite;

			pointIndexList.push_back(value);

			++ite;
		}

		return *this;
	}
};

class Component
{
public:
	QString strCode;                          //部件代码
	QString strName;                          //部件名称
	int nIndexStart;                          //当前部件的起始面元编号
	int nCount;                               //面元个数
	int nMaterialID;                          //材料ID
	double lfThickness;                       //等效厚度m，(ID为1-100为金属，ID>=101为液体，若为液体，厚度参数无意义，但必须占位)
	QList<PointIndexSum *> pointSumList;      //面元节点的坐标点序号

	Component()
	{
		strCode = "";
		strName = "";
		nCount = 0;
		nMaterialID = 0;
		lfThickness = 0.0;
		nIndexStart = 0;
	}

	~Component()
	{
		release();
	}

	bool release()
	{
		QList<PointIndexSum *>::iterator ite = pointSumList.begin();
		while (ite != pointSumList.end())
		{
			PointIndexSum *pPointIndexSum = *ite;

			if (pPointIndexSum)
			{
				delete pPointIndexSum;
				pPointIndexSum = NULL;
			}

			++ite;
		}

		return true;
	}

	Component &operator=(const Component &lhs)
	{
		release();

		strCode = lhs.strCode;
		strName = lhs.strName;
		nIndexStart = lhs.nIndexStart;
		nCount = lhs.nCount;
		nMaterialID = lhs.nMaterialID;
		lfThickness = lhs.lfThickness;

		QList<PointIndexSum *>::const_iterator ite = lhs.pointSumList.begin();
		while (ite != lhs.pointSumList.end())
		{
			PointIndexSum *pPointIndexSum = *ite;

			PointIndexSum *pPointIndexSumTemp = new PointIndexSum;

			pPointIndexSumTemp = pPointIndexSum;

			pointSumList.push_back(pPointIndexSumTemp);

			++ite;
		}

		return *this;
	}
};

class QuadModel
{
public:
	int nComponentNum;                      //部件个数
	int nPointNum;                          //坐标点数

	PointValue posCenterLine;               //瞄准中心的坐标xyz

	QList<Component *> componentList;
	PointSum pointSum;                     //坐标点xyz坐标m

	QuadModel()
	{
		nComponentNum = 0;
		nPointNum = 0;

		componentList.clear();
	}

	~QuadModel()
	{
		release();
	}

	bool release()
	{
		QList<Component *>::iterator ite = componentList.begin();
		while (ite != componentList.end())
		{
			Component *pShapeSum = *ite;

			if (pShapeSum)
			{
				delete pShapeSum;
				pShapeSum = NULL;
			}

			++ite;
		}
		
		return true;
	}

	QuadModel &operator=(const QuadModel &lhs)
	{
		release();

		nComponentNum = lhs.nComponentNum;
		nPointNum = lhs.nPointNum;
		posCenterLine = lhs.posCenterLine;
		pointSum = lhs.pointSum;

		QList<Component *>::const_iterator ite = lhs.componentList.begin();
		while (ite != lhs.componentList.end())
		{
			Component *pShapeSum = *ite;

			Component *pShapeSumTemp = new Component;

			*pShapeSumTemp = *pShapeSum;

			componentList.push_back(pShapeSumTemp);

			++ite;
		}

		return *this;
	}
};

Q_DECLARE_METATYPE(QuadModel)

#include <osg/ComputeBoundsVisitor>
#include <osg/MatrixTransform>

class TexCoordGenerator : public osg::NodeVisitor
{
public:
	TexCoordGenerator() 
		: osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
	{

	}

	osg::Vec2Array *generate_coords(osg::Array *vx, osg::Array *nx, float scale)
	{
		osg::Vec2Array *v2a = dynamic_cast<osg::Vec2Array *>(vx);
		osg::Vec3Array *v3a = dynamic_cast<osg::Vec3Array *>(vx);
		osg::Vec4Array *v4a = dynamic_cast<osg::Vec4Array *>(vx);
		osg::Vec2Array *n2a = dynamic_cast<osg::Vec2Array *>(nx);
		osg::Vec3Array *n3a = dynamic_cast<osg::Vec3Array *>(nx);
		osg::Vec4Array *n4a = dynamic_cast<osg::Vec4Array *>(nx);

		osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;

		for (int nI=0; nI<vx->getNumElements(); ++nI)
		{
			osg::Vec3 P;

			if (v2a)
			{
				P.set( (*v2a)[nI].x(), (*v2a)[nI].y(), 0 );
			}

			if (v3a)
			{
				P.set( (*v3a)[nI].x(), (*v3a)[nI].y(), (*v3a)[nI].z() );
			}

			if (v4a)
			{
				P.set( (*v4a)[nI].x(), (*v4a)[nI].y(), (*v4a)[nI].z());
			}

			osg::Vec3 N(0, 0, 1);

			if (n2a)
			{
				N.set( (*n2a)[nI].x(), (*n2a)[nI].y(), 0 );
			}

			if (n3a)
			{
				N.set( (*n3a)[nI].x(), (*n3a)[nI].y(), (*n3a)[nI].z() );
			}

			if (n4a)
			{
				N.set( (*n4a)[nI].x(), (*n4a)[nI].y(), (*n4a)[nI].z() );
			}

			int axis = 0;

			if (N.y() > N.x() && N.y() > N.z())
			{
				axis = 1;
			}

			if (-N.y() > N.x() && -N.y() > N.z())
			{
				axis = 1;
			}

			if (N.z() > N.x() && N.z() > N.y())
			{
				axis = 2;
			}

			if (-N.z() > N.x() && -N.z() > N.y())
			{
				axis = 2;
			}

			osg::Vec2 uv;
			switch (axis)
			{
			case 0:
				{
					uv.set(P.y(), P.z());
				}
				break;

			case 1:
				{
					uv.set(P.x(), P.z());
				}
				break;

			case 2:
				{
					uv.set(P.x(), P.y());
				}
				break;

			default:
				break;
			}

			tc->push_back(uv * scale);
		}

		return tc.release();
	}

	void apply(osg::Geode& geode)
	{
		for (int nI=0; nI<geode.getNumDrawables(); ++nI)
		{
			osg::Geometry *geo = dynamic_cast<osg::Geometry *>( geode.getDrawable(nI) );

			if (geo)
			{
				//多边形的法向量
				osg::Vec3Array *n3a = dynamic_cast<osg::Vec3Array *>(geo->getNormalArray());

				//计算多边形与面的夹角
				float cosAng = (*n3a)[0] * osg::Vec3f(0.0, 0.0, 1.0); //与xoy平面的夹角
				float radAng = acosf(cosAng);
				float ang = osg::RadiansToDegrees(radAng);

				//计算多边形与面的交线同方向的向量
				osg::Vec3f intersection = (*n3a)[0] ^ osg::Vec3f(0.0, 0.0, 1.0); //与xoy平面,即多边形投影xoy平面

				float ang2 = 0.0;
				if (intersection == osg::Vec3f(0.0, 0.0, 0.0)) //不存在交线，与xoy平面平行
				{

				}
				else
				{
					float cosAng2 = intersection * osg::Vec3f(0.0, 1.0, 0.0); //与Y轴的夹角
					float radAng2 = acosf(cosAng2);
					ang2 = osg::RadiansToDegrees(radAng2);
				}

				const osg::BoundingBox &bb= geo->getBound();
				osg::Vec3f center = bb.center();

				osg::Geode *geodeTemp = new osg::Geode;
				geodeTemp->addDrawable(geo);
				osg::MatrixTransform *mt = new osg::MatrixTransform;
				mt->addChild(geodeTemp);

				//处在1，2象限的时候正常
				//处在3，4象限的时候角度取反
				if (intersection.x() > 0.0)  
				{
					ang2 = -ang2;
				}

				{
					mt->setMatrix( osg::Matrix::rotate(osg::DegreesToRadians(-ang2), osg::Vec3d(0.0, 0.0, 1.0)) *
						osg::Matrix::rotate(osg::DegreesToRadians(-ang), osg::Vec3d(0.0, 1.0, 0.0)) );
				}

				osg::ComputeBoundsVisitor cbv;    //调用计算包围盒访问器类   
				mt->accept(cbv);

				osg::BoundingBox &box = cbv.getBoundingBox();

				osg::Vec3f origPoint(box.xMin(), box.yMin(), 0.0);

				mt->postMult(osg::Matrix::translate(-origPoint));

				osg::ComputeBoundsVisitor cbv2;
				mt->accept(cbv2);

				box = cbv2.getBoundingBox();

				float s = box.xMax() - box.xMin();
				float t = box.yMax() - box.yMin();

				osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;

				const osg::Matrixd &matrix = mt->getMatrix();

				osg::Vec3Array *v3a = dynamic_cast<osg::Vec3Array *>(geo->getVertexArray());
				for (int nI=0; nI<v3a->getNumElements(); ++nI)
				{
					osg::Vec3f P;

					P.set( (*v3a)[nI].x(), (*v3a)[nI].y(), (*v3a)[nI].z() );

					osg::Matrix matrixtemp  = matrix;
					matrixtemp.preMultTranslate(P);
					P = matrixtemp.getTrans();

					osg::Vec2 uv;

					uv.set( P.x() / s, P.y() / t );
					tc->push_back( uv );
				}

				geo->setTexCoordArray(0, tc);
			}
		}

		NodeVisitor::apply(geode);
	}
};

//毁伤树
struct KTInfo
{
	int nEventLevel;
	QString strID;
	QString strEventName;
	int		nSubEventNum;
	int		nDoorType;
	int		nPrepare;
	QString strParentID;
	double	nRow;		//行号
	double	nCol;		//列号

	KTInfo()
	{
		nEventLevel = 0;
		strID = "";
		strEventName = "";
		nSubEventNum = 0;
		nDoorType = 0;
		nPrepare = 0;
		strParentID = "";
		nRow = 0.0;
		nCol = 0.0;
	}

	KTInfo &operator =(KTInfo & info)
	{
		if (this!=&info)
		{
			nEventLevel = info.nEventLevel;
			strID = info.strID;
			strEventName = info.strEventName;
			nSubEventNum = info.nSubEventNum;
			nDoorType = info.nDoorType;
			nPrepare = info.nPrepare;
			strParentID = info.strParentID;
			nRow = info.nRow;
			nCol =info.nCol;
		}

		return *this;
	}
};

//节点事件个数
struct KTSubEvent
{
	QString strNodeID;
	int nSubEventNum;

	KTSubEvent()
	{
		strNodeID = "";
		nSubEventNum = 0;
	}

	KTSubEvent &operator =(KTSubEvent & info)
	{
		if (this!=&info)
		{
			strNodeID = info.strNodeID;
			nSubEventNum = info.nSubEventNum;
		}
		return *this;
	}
};
