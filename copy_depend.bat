set OSG_DIR_BIN=E:\yuequnlei\null\OpenSceneGraph-3.2.1-rc3_2\bin
set QT_DIR_BIN=D:\Qt\Qt5.4.0\5.4\msvc2010_opengl\bin
set OSG_3rdParty_BIN=E:\yuequnlei\new\Program Files (x86)\3rdParty\3rdParty\bin
set QT_DIR_PLUGINS=D:\Qt\Qt5.4.0\5.4\msvc2010_opengl\plugins

copy /y "%OSG_DIR_BIN%\osg100-osg.dll" "./bin"
copy /y "%OSG_DIR_BIN%\osg100-osgDB.dll" "./bin"
copy /y "%OSG_DIR_BIN%\osg100-osgFX.dll" "./bin"
copy /y "%OSG_DIR_BIN%\osg100-osgGA.dll" "./bin"
copy /y "%OSG_DIR_BIN%\osg100-osgManipulator.dll" "./bin"
copy /y "%OSG_DIR_BIN%\osg100-osgGA.dll" "./bin"
copy /y "%OSG_DIR_BIN%\osg100-osgGA.dll" "./bin"
copy /y "%OSG_DIR_BIN%\osg100-osgUtil.dll" "./bin"
copy /y "%OSG_DIR_BIN%\osg100-osgParticle.dll" "./bin"
copy /y "%OSG_DIR_BIN%\osg100-osgViewer.dll" "./bin"
copy /y "%OSG_DIR_BIN%\osg100-osgAnimation.dll" "./bin"
copy /y "%OSG_DIR_BIN%\osg100-osgText.dll" "./bin"
copy /y "%OSG_DIR_BIN%\osg100-osgQt.dll" "./bin"
copy /y "%OSG_DIR_BIN%\ot20-OpenThreads.dll" "./bin"
copy /y "%OSG_3rdParty_BIN%\zlib1.dll" "./bin"


copy /y "%QT_DIR_BIN%\Qt5Core.dll" "./bin"
copy /y "%QT_DIR_BIN%\Qt5Xml.dll" "./bin"
copy /y "%QT_DIR_BIN%\Qt5Widgets.dll" "./bin"
copy /y "%QT_DIR_BIN%\Qt5OpenGL.dll" "./bin"
copy /y "%QT_DIR_BIN%\Qt5Svg.dll" "./bin"
copy /y "%QT_DIR_BIN%\Qt5Gui.dll" "./bin"
copy /y "%QT_DIR_BIN%\icuin53.dll" "./bin"
copy /y "%QT_DIR_BIN%\icuuc53.dll" "./bin"
copy /y "%QT_DIR_BIN%\icudt53.dll" "./bin"

xcopy  "%QT_DIR_PLUGINS%\platforms"  "./bin/platforms" /s /exclude:EXCLUDE.txt /y