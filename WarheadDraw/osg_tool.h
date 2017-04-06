#pragma once
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/nodevisitor>
#include <osg/MatrixTransform>
#include <osg/MatrixTransform>
#include <ostream>

namespace osg
{
	class Geode;
	class Shape;
	class Geometry;
	class Drawable;
}

enum GridType
{
	kXY,
	kXZ,
	kYZ,
};
std::ostream& operator << (std::ostream& out, const osg::Vec3& v);

osg::Geode* MakeGrid(GridType grid_type, 
						int num,
						double delta = 1.0, 
						const osg::Vec4& axis_color = osg::Vec4(0.9, 0.0, 0.0, 1.0), 
						const osg::Vec4& grid_color = osg::Vec4(0.4, 0.4, 0.4, 1.0)
						);

osg::Drawable* DrawPoint(const osg::Vec3& coord, const osg::Vec4& color, float size);

osg::Drawable* DrawLine(const osg::Vec3& first_vertex_coord, const osg::Vec3& second_vertex_coord, const osg::Vec4& color, float line_width = 1.0f);
//判断是否是规则体
osg::Shape* JudgeRegularShape(osg::Geometry* geom);
//去除冗余顶点
void makeMesh(osg::Geometry* geom);

//求向量夹角rad
double intersectionAngle(const osg::Vec3& p0, const osg::Vec3& p1);



osg::PositionAttitudeTransform* CreatePosPAT(const osg::Vec3& pos);
osg::Geode* CreateLables(const osg::Vec3& pos, float size, const osg::Vec4& color, const std::string& label);
osg::Geode* CreateAxis();

//获取节点的世界坐标
class WorldCoordGetter : public osg::NodeVisitor
{
public:
	WorldCoordGetter() :
	  osg::NodeVisitor(NodeVisitor::TRAVERSE_PARENTS), done(false)
	  {
		  wcMatrix = new osg::Matrixd();
	  }
	  virtual void apply(osg::Node & node)
	  {
		  if(!done)
		  {
			  //到达根节点，此时节点路径也已记录完整
			  if(0 == node.getNumParents())
			  {
				  wcMatrix->set(osg::computeLocalToWorld(this->getNodePath()));
				  done = true;
			  }
			  //继续遍历
			  traverse(node);
		  }
	  }
	  //返回世界坐标矩阵
	  osg::Matrixd* giveUpDaMat()
	  {
		  return wcMatrix;
	  }
	  //计算场景中某个节点的世界坐标，返回osg::Matrix格式的世界坐标
	  //创建用于更新世界坐标矩阵的访问器后，即获取该矩阵
	  static osg::Matrixd* getWorldCoords(osg::Node* node)
	  {
		  WorldCoordGetter* ncv = new WorldCoordGetter();
		  if(node && ncv)
		  {
			  //启用访问器
			  node->accept(*ncv);
			  return ncv->giveUpDaMat();
		  }
		  else
			  return NULL;
	  }
private:
	bool done;
	osg::Matrix* wcMatrix;
};
