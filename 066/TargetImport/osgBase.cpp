#include "osgBase.h"

#include <osgGA/CameraManipulator>
#include <osg/LineWidth>
osg::ref_ptr<osg::Geometry> DrawObjectAxis(double len, osg::Matrix matrix)
{
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();

	{
		osg::Vec3 pos = osg::Vec3(0.0, 0.0, 0.0);//centerInverse;

		osg::Vec4 temp = osg::Vec4(pos, 1.0);
		temp = matrix * temp;
		pos.x() = temp.x();
		pos.y() = temp.y();
		pos.z() = temp.z();

		vertices->push_back (pos);
	}

	{
		osg::Vec3 pos = osg::Vec3(len, 0.0, 0.0);//osg::Vec3(centerInverse.x() + len, centerInverse.y(), centerInverse.z());

		osg::Vec4 temp = osg::Vec4(pos, 1.0);
		temp = matrix * temp;
		pos.x() = temp.x();
		pos.y() = temp.y();
		pos.z() = temp.z();

		vertices->push_back (pos);
	}

	{
		osg::Vec3 pos = osg::Vec3(0.0, 0.0, 0.0);//centerInverse;

		osg::Vec4 temp = osg::Vec4(pos, 1.0);
		temp = matrix * temp;
		pos.x() = temp.x();
		pos.y() = temp.y();
		pos.z() = temp.z();

		vertices->push_back (pos);
	}

	{
		osg::Vec3 pos = osg::Vec3(0.0, len, 0.0);//osg::Vec3(centerInverse.x(), centerInverse.y() + len, centerInverse.z());

		osg::Vec4 temp = osg::Vec4(pos, 1.0);
		temp = matrix * temp;
		pos.x() = temp.x();
		pos.y() = temp.y();
		pos.z() = temp.z();

		vertices->push_back (pos);
	}

	{
		osg::Vec3 pos = osg::Vec3(0.0, 0.0, 0.0);//centerInverse;

		osg::Vec4 temp = osg::Vec4(pos, 1.0);
		temp = matrix * temp;
		pos.x() = temp.x();
		pos.y() = temp.y();
		pos.z() = temp.z();

		vertices->push_back (pos);
	}

	{
		osg::Vec3 pos = osg::Vec3(0.0, 0.0, len);//osg::Vec3(centerInverse.x(), centerInverse.y(), centerInverse.z() + len);

		osg::Vec4 temp = osg::Vec4(pos, 1.0);
		temp = matrix * temp;
		pos.x() = temp.x();
		pos.y() = temp.y();
		pos.z() = temp.z();

		vertices->push_back (pos);
	}

	geometry->setVertexArray (vertices.get());

	osg::ref_ptr<osg::Vec4Array> colors (new osg::Vec4Array());
	colors->push_back (osg::Vec4 (1.0f, 0.0f, 0.0f, 1.0f));
	colors->push_back (osg::Vec4 (1.0f, 0.0f, 0.0f, 1.0f));
	colors->push_back (osg::Vec4 (0.0f, 1.0f, 0.0f, 1.0f));
	colors->push_back (osg::Vec4 (0.0f, 1.0f, 0.0f, 1.0f));
	colors->push_back (osg::Vec4 (0.0f, 0.0f, 1.0f, 1.0f));
	colors->push_back (osg::Vec4 (0.0f, 0.0f, 1.0f, 1.0f));
	geometry->setColorArray (colors.get());

	geometry->setColorBinding (osg::Geometry::BIND_PER_VERTEX);    
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,0,6));

	//设置线宽
	osg::ref_ptr<osg::LineWidth> lw = new osg::LineWidth(2.0);
	geometry->getOrCreateStateSet()->setAttribute(lw.get());

	geometry->getOrCreateStateSet()->setMode(GL_LIGHTING, false);
	geometry->getOrCreateStateSet()->setMode( GL_DEPTH_TEST, osg::StateAttribute::OFF );

	geometry->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );

	geometry->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	geometry->getOrCreateStateSet()->setRenderBinDetails( 5000, "RenderBin" ) ;

	return geometry;
}
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

CompassHUD::CompassHUD(osgViewer::View *pView)
{
	m_pView = pView;
}

CompassHUD::~CompassHUD(void)
{
}

osg::Camera *CompassHUD::createCamera( int x,int y,int width,int height )
{
	m_pCamera = new osg::Camera;

	m_pCamera->setProjectionMatrixAsOrtho(x,x+width,y,y+height, -500.0, 500.0);
	m_pCamera->setViewport(x,y,width,height); 
	m_pCamera->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
	m_pCamera->setViewMatrix(osg::Matrix::identity());

	m_pCamera->setRenderOrder(osg::Camera::POST_RENDER);
	m_pCamera->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
	m_pCamera->getOrCreateStateSet()->setMode( GL_DEPTH_TEST , osg::StateAttribute::OFF ) ;
	m_pCamera->getOrCreateStateSet()->setRenderBinDetails( 5000, "RenderBin" ) ;
	m_pCamera->setClearMask(GL_DEPTH_BUFFER_BIT);

	m_pCamera->addChild( createPosPAT(osg::Vec3(70.0, 70.0, -100.0)) );

	return m_pCamera.get();
}

osg::Geode *CompassHUD::createAxis()
{
	osg::Geode* geode  = new osg::Geode; 

	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();
	vertices->push_back (osg::Vec3 ( 0.0, 0.0, 0.0));
	vertices->push_back (osg::Vec3 ( 50.0, 0.0, 0.0));
	vertices->push_back (osg::Vec3 ( 0.0, 0.0, 0.0));
	vertices->push_back (osg::Vec3 ( 0.0, 50.0, 0.0));
	vertices->push_back (osg::Vec3 ( 0.0, 0.0, 0.0));
	vertices->push_back (osg::Vec3 ( 0.0, 0.0, 50.0));
	geometry->setVertexArray (vertices.get());

	osg::ref_ptr<osg::Vec4Array> colors (new osg::Vec4Array());
	colors->push_back (osg::Vec4 (1.0f, 0.0f, 0.0f, 1.0f));
	colors->push_back (osg::Vec4 (1.0f, 0.0f, 0.0f, 1.0f));
	colors->push_back (osg::Vec4 (0.0f, 1.0f, 0.0f, 1.0f));
	colors->push_back (osg::Vec4 (0.0f, 1.0f, 0.0f, 1.0f));
	colors->push_back (osg::Vec4 (0.0f, 0.0f, 1.0f, 1.0f));
	colors->push_back (osg::Vec4 (0.0f, 0.0f, 1.0f, 1.0f));
	geometry->setColorArray (colors.get());

	geometry->setColorBinding (osg::Geometry::BIND_PER_VERTEX);    
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,0,6));

	//设置线宽
	osg::ref_ptr<osg::LineWidth> lw = new osg::LineWidth(2.0);
	geometry->getOrCreateStateSet()->setAttribute(lw.get());

	geode->addDrawable( geometry.get() );
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, false);

	return geode;
}

osg::Geode *CompassHUD::createLables(const osg::Vec3& pos, float size, osg::Vec4 color, const std::string& label)
{
	osg::Geode* geode = new osg::Geode();
	geode->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
	geode->getOrCreateStateSet()->setMode( GL_DEPTH_TEST , osg::StateAttribute::OFF ) ;
	geode->getOrCreateStateSet()->setRenderBinDetails( 5000, "RenderBin" ) ;

	std::string timesFont("fonts/simhei.ttf");

	{
		osgText::Text* text = new  osgText::Text;
		geode->addDrawable( text );

		text->setFont(timesFont);
		text->setPosition(pos);
		text->setCharacterSize(size);
		text->setColor(color);
		text->setAutoRotateToScreen(true);
		text->setBackdropType(osgText::Text::OUTLINE);
		text->setBackdropColor(color);
		text->setAxisAlignment(osgText::Text::SCREEN);
		text->setAlignment(osgText::Text::CENTER_CENTER);
		text->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);
		text->setText(label);
	}

	return geode;
}

osg::Node *CompassHUD::createPosPAT(osg::Vec3 pos)
{
	_posPAT = new osg::PositionAttitudeTransform;
	_posPAT->setPosition( pos );
	_posPAT->addChild( createAxis() );
	_posPAT->addChild( createLables(osg::Vec3(51.0, 0.0, 1.0), 15.0, osg::Vec4 (1.0f, 0.0f, 0.0f, 1.0f), "X") );
	_posPAT->addChild( createLables(osg::Vec3(0.0, 51.0, 1.0), 15.0, osg::Vec4 (0.0f, 1.0f, 0.0f, 1.0f), "Y") );
	_posPAT->addChild( createLables(osg::Vec3(0.0, 0.0, 51.0), 15.0, osg::Vec4 (0.0f, 0.0f, 1.0f, 1.0f), "Z") );

	_posPAT->setUpdateCallback( new UpdateCompassCallback(m_pView->getCameraManipulator()) );

	return _posPAT;
}