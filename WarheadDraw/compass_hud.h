#pragma once

namespace osgViewer { class Viewer; }
namespace osg { class Camera; }
namespace osgText { class Text; }
class CompassHud
{
public:
	CompassHud(osgViewer::Viewer* viewer);
	osg::Camera* CreateAxisHud(int x, int y, int width, int height);
	osg::Camera* CreateTextHud(int x, int y, int width, int height, osgText::Text* update_text);
private:
	osgViewer::Viewer* viewer_;
};