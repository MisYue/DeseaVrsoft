#include <QTimer>
#include <QApplication>
#include <QGridLayout>

#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/TrackballManipulator>

#include <osgDB/ReadFile>

#include <osgQt/GraphicsWindowQt>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/Camera>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/PositionAttitudeTransform>
#include <osgText/Text>
#include <osgViewer/View>
#include <iostream>

class OsgBase
{
public:
	static osgViewer::View* addViewWidget( osgQt::GraphicsWindowQt* gw, osg::Node* scene )
	{
		osgViewer::View* view = new osgViewer::View;

		osg::Camera* camera = view->getCamera();
		camera->setGraphicsContext( gw );

		const osg::GraphicsContext::Traits* traits = gw->getTraits();

		camera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );
		camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
		camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f );

		view->setSceneData( scene );
		view->addEventHandler( new osgViewer::StatsHandler );
		view->setCameraManipulator( new osgGA::TrackballManipulator );

		return view;
	}

	static osgQt::GraphicsWindowQt* createGraphicsWindow( int x, int y, int w, int h, const std::string& name="", bool windowDecoration=false )
	{
		osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
		osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
		traits->windowName = name;
		traits->windowDecoration = windowDecoration;
		traits->x = x;
		traits->y = y;
		traits->width = w;
		traits->height = h;
		traits->doubleBuffer = true;
		traits->alpha = ds->getMinimumNumAlphaBits();
		traits->stencil = ds->getMinimumNumStencilBits();
		traits->sampleBuffers = ds->getMultiSamples();
		traits->samples = ds->getNumMultiSamples();

		return new osgQt::GraphicsWindowQt(traits.get());
	}

	//求解 平面的法向量
	static osg::Vec3d solvePlaneNormal(const osg::Vec3d &p1, 
		const osg::Vec3d &p2, const osg::Vec3d &p3)
	{

		double x = 0;
		double y = 0;
		double z = 0;

		if ( ( p1[0] == p2[0] ) && ( p2[0] == p3[0] ) )//三个点的x坐标一致
		{
			x = 1;
			y = 0;
			z = 0;

		}else if ( ( p1[1]==p2[1] ) && ( p2[1]==p3[1] ) )//三个点的y坐标一致
		{
			x = 0;
			y = 1;
			z = 0;

		}else if (  ( p1[2]==p2[2] ) && ( p2[2]==p3[2] ) )//三个点的z坐标一致
		{
			x = 0;
			y = 0;
			z = 1;

		}else{

			double A = p2[0] - p1[0];
			double B = p2[1] - p1[1];
			double C = p2[2] - p1[2];

			double D = p3[0] - p1[0];
			double E = p3[1] - p1[1];
			double F = p3[2] - p1[2];

			double X = (B*F - C*E)/(A*E - B*D);
			double Y = (A*F - C*D)/(B*D - A*E);
			double Z = 1;

			x = X/( X + Y + Z );
			y = Y/( X + Y + Z );
			z = Z/( X + Y + Z );
		}

		return osg::Vec3d(x, y, z);

	}

};


//绘制模型坐标系
osg::ref_ptr<osg::Geometry> DrawObjectAxis(double len, osg::Matrix matrix);

class CompassHUD
{
public:
	CompassHUD(osgViewer::View *pView = NULL);
	~CompassHUD(void);

	osg::Camera *createCamera( int x,int y,int width,int height );

private:
	osg::Geode *createAxis();
	osg::Geode *createLables(const osg::Vec3& pos, float size, osg::Vec4 color, const std::string& label);

	osg::Node *createPosPAT(osg::Vec3 pos);

private:
	osg::ref_ptr< osg::Camera > m_pCamera;

	osg::PositionAttitudeTransform *_posPAT;
	osg::ref_ptr<osgViewer::View> m_pView;
};