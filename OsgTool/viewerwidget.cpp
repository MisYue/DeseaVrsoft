#include "ViewerWidget.h"
#include <osgGA/StateSetManipulator>
#include <osgGA/TrackballManipulator>
#include <osgQt/GraphicsWindowQt>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <QtGui>
#include <QtCore>
#include <QtWidgets>

ViewerWidget::ViewerWidget(osg::Node* scene)
{

    // create a new viewer (a simple osgViewer::Viewer)
    createViewer();

    // attach the scene graph provided by the user
    if (scene)
    {
        dynamic_cast<osgViewer::Viewer*>(_viewer.get())->setSceneData( scene );
    }

    // start up the paint event timer.
    installFrameTimer();
	
}

ViewerWidget::ViewerWidget(osgViewer::ViewerBase* viewer) :
_viewer( viewer )
{
    if ( !_viewer.valid() )
    {
        // create a viewer if the user passed in NULL
        createViewer();
    }

    else
    {
        // reconfigure all the viewer's views to use a Qt graphics context.
        osgViewer::ViewerBase::Views views;
        getViews( views );
        for( osgViewer::ViewerBase::Views::iterator v = views.begin(); v != views.end(); ++v )
        {
            reconfigure( *v );
        }

        // disable event setting on the viewer.
        viewer->setKeyEventSetsDone(0);
        viewer->setQuitEventSetsDone(false);
    }

    // start up the paint event timer.
    installFrameTimer();
}

ViewerWidget::~ViewerWidget()
{
    _timer.stop();
    if ( _viewer.valid() )
    {
        _viewer->stopThreading();
        _viewer = 0L;
    }
}


void ViewerWidget::installFrameTimer()
{    
    // start the frame timer.
    connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer.start(15);
}


void ViewerWidget::createViewer()
{
    // creates a simple basic viewer.
    osgViewer::Viewer* viewer = new osgViewer::Viewer();

    viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
    viewer->setCameraManipulator(new osgGA::TrackballManipulator);

    viewer->addEventHandler(new osgViewer::StatsHandler());
    viewer->addEventHandler(new osgGA::StateSetManipulator());
    viewer->addEventHandler(new osgViewer::ThreadingHandler());
	// add the state manipulator
	viewer->addEventHandler( new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()) );

    viewer->setKeyEventSetsDone(0);
    viewer->setQuitEventSetsDone(false);

    reconfigure( viewer );

    _viewer = viewer;
}

void ViewerWidget::reconfigure( osgViewer::View* view )
{
    if ( !_gc.valid() )
    {
        // create the Qt graphics context if necessary; it will be shared across all views.
        osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
        osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits(ds);

        traits->readDISPLAY();
        if (traits->displayNum<0) traits->displayNum = 0;

        traits->windowName = "ViewerQt";
        traits->windowDecoration = false;
        traits->x = x();
        traits->y = y();
        traits->width = width();
        traits->height = height();
        traits->doubleBuffer = true;
        traits->inheritedWindowData = new osgQt::GraphicsWindowQt::WindowData(this);

        _gc = new osgQt::GraphicsWindowQt( traits.get() );
    }

    // reconfigure this view's camera to use the Qt GC if necessary.
    osg::Camera* camera = view->getCamera();
    if ( camera->getGraphicsContext() != _gc.get() )
    {
        camera->setGraphicsContext( _gc.get() );
        if ( !camera->getViewport() )
        {
            camera->setViewport(new osg::Viewport(0, 0, _gc->getTraits()->width, _gc->getTraits()->height));
        }
        camera->setProjectionMatrixAsPerspective(
            30.0f, camera->getViewport()->width()/camera->getViewport()->height(), 1.0f, 10000.0f );
		//camera->setClearColor(osg::Vec4(0.184, 0.184, 0.368, 1.0));
		camera->setClearColor(osg::Vec4(65/255.0, 99/255.0, 146/255.0, 1.0));

    }
}

      
void ViewerWidget::paintEvent(QPaintEvent* e)
{
    if (_viewer->getRunFrameScheme() == osgViewer::ViewerBase::CONTINUOUS || 
        _viewer->checkNeedToDoFrame() )
    {
        _viewer->frame();
    }
}

void ViewerWidget::setScene(osg::Node* scene)
{
	if (scene)
	{
		dynamic_cast<osgViewer::Viewer*>(_viewer.get())->setSceneData( scene );
	}
}
