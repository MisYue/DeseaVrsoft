#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H 1
#include "osgtool_global.h"
#include <osgQt/GraphicsWindowQt>
#include <osgViewer/ViewerBase>

#include <QtCore>


/**
 * Qt widget that encapsulates an osgViewer::Viewer.
 */
class  OSGTOOL_EXPORT ViewerWidget : public osgQt::GLWidget
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
