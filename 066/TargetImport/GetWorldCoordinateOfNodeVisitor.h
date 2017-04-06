#pragma once
#include <osg/nodevisitor>
#include <osg/MatrixTransform>


//获取节点的世界坐标
class GetWorldCoordinateOfNodeVisitor : public osg::NodeVisitor
{
public:
	GetWorldCoordinateOfNodeVisitor() :
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
		  GetWorldCoordinateOfNodeVisitor* ncv = new GetWorldCoordinateOfNodeVisitor();
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


