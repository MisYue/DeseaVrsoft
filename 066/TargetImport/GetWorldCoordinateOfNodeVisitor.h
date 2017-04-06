#pragma once
#include <osg/nodevisitor>
#include <osg/MatrixTransform>


//��ȡ�ڵ����������
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
			//������ڵ㣬��ʱ�ڵ�·��Ҳ�Ѽ�¼����
			if(0 == node.getNumParents())
			{
				wcMatrix->set(osg::computeLocalToWorld(this->getNodePath()));
				done = true;
			}
			//��������
			traverse(node);
		}
	  }
	  //���������������
	  osg::Matrixd* giveUpDaMat()
	  {
		return wcMatrix;
	  }
	  //���㳡����ĳ���ڵ���������꣬����osg::Matrix��ʽ����������
	  //�������ڸ��������������ķ������󣬼���ȡ�þ���

	  static osg::Matrixd* getWorldCoords(osg::Node* node)
	  {
		  GetWorldCoordinateOfNodeVisitor* ncv = new GetWorldCoordinateOfNodeVisitor();
		  if(node && ncv)
		  {
			  //���÷�����
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


