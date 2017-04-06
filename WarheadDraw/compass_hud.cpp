#include "compass_hud.h"
#include "osg_tool.h"
#include <osg/Camera>
#include <osgText/Text>
#include <osgViewer/Viewer>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/PositionAttitudeTransform>
#include <osg/NodeCallback>
#include <osgGA/CameraManipulator>
#include <osg/LineWidth>


class UpdateCompassCallback : public osg::NodeCallback
{
public:
	UpdateCompassCallback(osgGA::CameraManipulator *pMainCameraManipulator)
	{
		m_pMainCameraManipulator = pMainCameraManipulator;
	}
	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv )
	{
		if(nv->getVisitorType() == osg::NodeVisitor::UPDATE_VISITOR )
		{
			osg::PositionAttitudeTransform* pat = dynamic_cast<osg::PositionAttitudeTransform*>(node);

			if (pat)
			{
				osg::Matrix matrix = m_pMainCameraManipulator->getMatrix();
				matrix = osg::Matrix::inverse( matrix );

				osg::Quat quat = matrix.getRotate();

				pat->setAttitude(quat);
			}
		}
		traverse( node, nv );
	}
private:
	osgGA::CameraManipulator *m_pMainCameraManipulator;
};

CompassHud::CompassHud(osgViewer::Viewer* viewer) : viewer_(viewer)
{

}
osg::Camera* CompassHud::CreateAxisHud(int x, int y, int width, int height)
{
	osg::Camera* camera = new osg::Camera;

	camera->setProjectionMatrixAsOrtho(x,x+width,y,y+height, -500.0, 500.0);
	camera->setViewport(x,y,width,height); 
	camera->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
	camera->setViewMatrix(osg::Matrix::identity());

	camera->setRenderOrder(osg::Camera::POST_RENDER);
	camera->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
	camera->getOrCreateStateSet()->setMode( GL_DEPTH_TEST , osg::StateAttribute::OFF ) ;
	camera->getOrCreateStateSet()->setRenderBinDetails( 5000, "RenderBin" ) ;
	camera->setClearMask(GL_DEPTH_BUFFER_BIT);

	osg::PositionAttitudeTransform* pos_pat = CreatePosPAT(osg::Vec3(70.0, 70.0, -100.0));
	pos_pat->setUpdateCallback( new UpdateCompassCallback(viewer_->getCameraManipulator()) );
	camera->addChild(pos_pat);

	return camera;
}
osg::Camera* CompassHud::CreateTextHud(int x, int y, int width, int height, osgText::Text* update_text)
{
	return NULL;
}
