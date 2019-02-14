#include "dialog.h"

#include <QHBoxLayout>

Dialog::Dialog(QWidget *parent) :
    QWidget (parent)
{


    QHBoxLayout* layout=new QHBoxLayout();


    _viewer=new osgViewer::Viewer;

    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowName = "";
    traits->windowDecoration = false;
    traits->x = 0;
    traits->y = 0;
    traits->width = 800;
    traits->height = 600;
    traits->doubleBuffer = true;
    traits->alpha = ds->getMinimumNumAlphaBits();
    traits->stencil = ds->getMinimumNumStencilBits();
    traits->sampleBuffers = ds->getMultiSamples();
    traits->samples = ds->getNumMultiSamples();
traits->useCursor=true;
    osg::ref_ptr<QtGraphicsWindow> gw = new QtGraphicsWindow(traits.get());


    osg::ref_ptr<osg::Camera> _camera = _viewer->getCamera();
    _camera->setGraphicsContext(gw);
    _camera->setClearColor(osg::Vec4(0.2, 0.2, 0.6, 1.0));
    _camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));

    // set the draw and read buffers up for a double buffered window with rendering going to back buffer
    _camera->setDrawBuffer(GL_BACK);
    _camera->setReadBuffer(GL_BACK);

    _camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width) / static_cast<double>(traits->height), 1.0f, 10000.0f);



//    gw->setTouchEventsEnabled(true);

    _viewer->setSceneData(osgDB::readNodeFile("cow.osg"));
    _viewer->addEventHandler(new osgViewer::StatsHandler);
    _viewer->setCameraManipulator(new osgGA::TrackballManipulator);

#if QT_VERSION >= 0x050000
    // Qt5 is currently crashing and reporting "Cannot make QOpenGLContext current in a different thread" when the viewer is run multi-threaded, this is regression from Qt4
    osgViewer::ViewerBase::ThreadingModel threadingModel = osgViewer::ViewerBase::SingleThreaded;
#endif
    _viewer->setThreadingModel(threadingModel);

    setViewer(_viewer.get());



        layout->addWidget(gw->getGLWidget());

      setLayout(layout);
}

Dialog::~Dialog()
{

}
