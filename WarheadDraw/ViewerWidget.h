#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H 1
#ifdef _DEBUG
#pragma comment(lib, "osgd.lib")
#pragma comment(lib, "osgViewerd.lib")
#pragma comment(lib, "osgGAd.lib")
#pragma comment(lib, "osgDBd.lib")
#pragma comment(lib, "osgTextd.lib")
#pragma comment(lib, "osgQtd.lib")
#pragma comment(lib, "osgUtild.lib")
//#pragma comment(lib, "Qt5OpenGLd.lib")
#pragma comment(lib, "OpenThreadsd.lib")
//#pragma comment(lib, "osgFxd.lib")

#else
#pragma comment(lib, "osg.lib")
#pragma comment(lib, "osgViewer.lib")
#pragma comment(lib, "osgGA.lib")
#pragma comment(lib, "osgDB.lib")
#pragma comment(lib, "osgText.lib")
#pragma comment(lib, "osgQt.lib")
#pragma comment(lib, "osgUtil.lib")
#pragma comment(lib, "Qt5OpenGL.lib")
#pragma comment(lib, "OpenThreads.lib")
#pragma comment(lib, "osgFx.lib")

#endif
#include <osgQt/GraphicsWindowQt>
#include <osgViewer/ViewerBase>

#include <QtCore/QTimer>


/**
 * Qt widget that encapsulates an osgViewer::Viewer.
 */
class  ViewerWidget : public osgQt::GLWidget
{
public:
    /**
     * Constructs a new ViewerWidget, creating an underlying viewer.
     * @param[in ] scene Scene graph to attach to the viewer (optional)
     */
    ViewerWidget(osg::Node* scene=0L);

    /**
     * Constructs a new ViewerWidget, attaching an existing viewer.
     * @param[in ] viewer Viewer to attach to this widget. The widget will install
     *             a new camera in the viewer. (NOTE: this widget does not take
     *             ownership of the Viewer. You are still respsonsile for its
     *             destruction)
     */
    ViewerWidget(osgViewer::ViewerBase* viewer);

    /**
     * Access the underlying viewer.
     */
    osgViewer::ViewerBase* getViewer() { return _viewer.get(); }

    /**
     * Populates the incoming collection with the views comprising this viewer.
     */
    template<typename T>
    void getViews( T& views ) const {
        osgViewer::ViewerBase::Views temp;
        _viewer->getViews(temp);
        views.insert(views.end(), temp.begin(), temp.end());
    }

    virtual ~ViewerWidget();

	void setScene(osg::Node* scene);

protected:

    QTimer _timer;

    void createViewer();
    void reconfigure( osgViewer::View* );
    void installFrameTimer();
    void paintEvent( QPaintEvent* );

    osg::observer_ptr<osgViewer::ViewerBase> _viewer;
    osg::ref_ptr<osg::GraphicsContext>       _gc;
};

#endif // VIEWERWIDGET_H
