#include "qtgraphicswindow.h"
#include <osgViewer/ViewerBase>
#include <QPointer>

class QtKeyboardMap
{

public:
    QtKeyboardMap()
    {
        mKeyMap[Qt::Key_Escape     ] = osgGA::GUIEventAdapter::KEY_Escape;
        mKeyMap[Qt::Key_Delete   ] = osgGA::GUIEventAdapter::KEY_Delete;
        mKeyMap[Qt::Key_Home       ] = osgGA::GUIEventAdapter::KEY_Home;
        mKeyMap[Qt::Key_Enter      ] = osgGA::GUIEventAdapter::KEY_KP_Enter;
        mKeyMap[Qt::Key_End        ] = osgGA::GUIEventAdapter::KEY_End;
        mKeyMap[Qt::Key_Return     ] = osgGA::GUIEventAdapter::KEY_Return;
        mKeyMap[Qt::Key_PageUp     ] = osgGA::GUIEventAdapter::KEY_Page_Up;
        mKeyMap[Qt::Key_PageDown   ] = osgGA::GUIEventAdapter::KEY_Page_Down;
        mKeyMap[Qt::Key_Left       ] = osgGA::GUIEventAdapter::KEY_Left;
        mKeyMap[Qt::Key_Right      ] = osgGA::GUIEventAdapter::KEY_Right;
        mKeyMap[Qt::Key_Up         ] = osgGA::GUIEventAdapter::KEY_Up;
        mKeyMap[Qt::Key_Down       ] = osgGA::GUIEventAdapter::KEY_Down;
        mKeyMap[Qt::Key_Backspace  ] = osgGA::GUIEventAdapter::KEY_BackSpace;
        mKeyMap[Qt::Key_Tab        ] = osgGA::GUIEventAdapter::KEY_Tab;
        mKeyMap[Qt::Key_Space      ] = osgGA::GUIEventAdapter::KEY_Space;
        mKeyMap[Qt::Key_Delete     ] = osgGA::GUIEventAdapter::KEY_Delete;
        mKeyMap[Qt::Key_Alt      ] = osgGA::GUIEventAdapter::KEY_Alt_L;
        mKeyMap[Qt::Key_Shift    ] = osgGA::GUIEventAdapter::KEY_Shift_L;
        mKeyMap[Qt::Key_Control  ] = osgGA::GUIEventAdapter::KEY_Control_L;
        mKeyMap[Qt::Key_Meta     ] = osgGA::GUIEventAdapter::KEY_Meta_L;

        mKeyMap[Qt::Key_F1             ] = osgGA::GUIEventAdapter::KEY_F1;
        mKeyMap[Qt::Key_F2             ] = osgGA::GUIEventAdapter::KEY_F2;
        mKeyMap[Qt::Key_F3             ] = osgGA::GUIEventAdapter::KEY_F3;
        mKeyMap[Qt::Key_F4             ] = osgGA::GUIEventAdapter::KEY_F4;
        mKeyMap[Qt::Key_F5             ] = osgGA::GUIEventAdapter::KEY_F5;
        mKeyMap[Qt::Key_F6             ] = osgGA::GUIEventAdapter::KEY_F6;
        mKeyMap[Qt::Key_F7             ] = osgGA::GUIEventAdapter::KEY_F7;
        mKeyMap[Qt::Key_F8             ] = osgGA::GUIEventAdapter::KEY_F8;
        mKeyMap[Qt::Key_F9             ] = osgGA::GUIEventAdapter::KEY_F9;
        mKeyMap[Qt::Key_F10            ] = osgGA::GUIEventAdapter::KEY_F10;
        mKeyMap[Qt::Key_F11            ] = osgGA::GUIEventAdapter::KEY_F11;
        mKeyMap[Qt::Key_F12            ] = osgGA::GUIEventAdapter::KEY_F12;
        mKeyMap[Qt::Key_F13            ] = osgGA::GUIEventAdapter::KEY_F13;
        mKeyMap[Qt::Key_F14            ] = osgGA::GUIEventAdapter::KEY_F14;
        mKeyMap[Qt::Key_F15            ] = osgGA::GUIEventAdapter::KEY_F15;
        mKeyMap[Qt::Key_F16            ] = osgGA::GUIEventAdapter::KEY_F16;
        mKeyMap[Qt::Key_F17            ] = osgGA::GUIEventAdapter::KEY_F17;
        mKeyMap[Qt::Key_F18            ] = osgGA::GUIEventAdapter::KEY_F18;
        mKeyMap[Qt::Key_F19            ] = osgGA::GUIEventAdapter::KEY_F19;
        mKeyMap[Qt::Key_F20            ] = osgGA::GUIEventAdapter::KEY_F20;

        mKeyMap[Qt::Key_hyphen         ] = '-';
        mKeyMap[Qt::Key_Equal         ] = '=';

        mKeyMap[Qt::Key_division      ] = osgGA::GUIEventAdapter::KEY_KP_Divide;
        mKeyMap[Qt::Key_multiply      ] = osgGA::GUIEventAdapter::KEY_KP_Multiply;
        mKeyMap[Qt::Key_Minus         ] = '-';
        mKeyMap[Qt::Key_Plus          ] = '+';
        //mKeyMap[Qt::Key_H              ] = osgGA::GUIEventAdapter::KEY_KP_Home;
        //mKeyMap[Qt::Key_                    ] = osgGA::GUIEventAdapter::KEY_KP_Up;
        //mKeyMap[92                    ] = osgGA::GUIEventAdapter::KEY_KP_Page_Up;
        //mKeyMap[86                    ] = osgGA::GUIEventAdapter::KEY_KP_Left;
        //mKeyMap[87                    ] = osgGA::GUIEventAdapter::KEY_KP_Begin;
        //mKeyMap[88                    ] = osgGA::GUIEventAdapter::KEY_KP_Right;
        //mKeyMap[83                    ] = osgGA::GUIEventAdapter::KEY_KP_End;
        //mKeyMap[84                    ] = osgGA::GUIEventAdapter::KEY_KP_Down;
        //mKeyMap[85                    ] = osgGA::GUIEventAdapter::KEY_KP_Page_Down;
        mKeyMap[Qt::Key_Insert        ] = osgGA::GUIEventAdapter::KEY_KP_Insert;
        //mKeyMap[Qt::Key_Delete        ] = osgGA::GUIEventAdapter::KEY_KP_Delete;
    }

    ~QtKeyboardMap()
    {
    }

    int remapKey(QKeyEvent* event)
    {
        KeyMap::iterator itr = mKeyMap.find(event->key());
        if (itr == mKeyMap.end())
        {
            return int(*(event->text().toLatin1().data()));
        }
        else
            return itr->second;
    }

private:
    typedef std::map<unsigned int, int> KeyMap;
    KeyMap mKeyMap;
};

static QtKeyboardMap s_QtKeyboardMap;

// The object responsible for the scene re-rendering.
class HeartBeat : public QObject {
public:
    int _timerId;
    osg::Timer _lastFrameStartTime;
    osg::observer_ptr< osgViewer::ViewerBase > _viewer;

    virtual ~HeartBeat();

    void init( osgViewer::ViewerBase *viewer );
    void stopTimer();
    void timerEvent( QTimerEvent *event );

    static HeartBeat* instance();
private:
    HeartBeat();

    static QPointer<HeartBeat> heartBeat;
};

QPointer<HeartBeat> HeartBeat::heartBeat;

void setViewer( osgViewer::ViewerBase *viewer )
{
    HeartBeat::instance()->init( viewer );
}


/// Constructor. Must be called from main thread.
HeartBeat::HeartBeat() : _timerId( 0 )
{
}


/// Destructor. Must be called from main thread.
HeartBeat::~HeartBeat()
{
    stopTimer();
}

HeartBeat* HeartBeat::instance()
{
    if (!heartBeat)
    {
        heartBeat = new HeartBeat();
    }
    return heartBeat;
}

void HeartBeat::stopTimer()
{
    if ( _timerId != 0 )
    {
        killTimer( _timerId );
        _timerId = 0;
    }
}


/// Initializes the loop for viewer. Must be called from main thread.
void HeartBeat::init( osgViewer::ViewerBase *viewer )
{
    if( _viewer == viewer )
        return;

    stopTimer();

    _viewer = viewer;

    if( viewer )
    {
        _timerId = startTimer( 0 );
        _lastFrameStartTime.setStartTick( 0 );
    }
}


void HeartBeat::timerEvent( QTimerEvent * /*event*/ )
{
    osg::ref_ptr< osgViewer::ViewerBase > viewer;
    if( !_viewer.lock( viewer ) )
    {
        // viewer has been deleted -> stop timer
        stopTimer();
        return;
    }

    // limit the frame rate
    if( viewer->getRunMaxFrameRate() > 0.0)
    {
        double dt = _lastFrameStartTime.time_s();
        double minFrameTime = 1.0 / viewer->getRunMaxFrameRate();
        if (dt < minFrameTime)
            OpenThreads::Thread::microSleep(static_cast<unsigned int>(1000000.0*(minFrameTime-dt)));
    }
    else
    {
        // avoid excessive CPU loading when no frame is required in ON_DEMAND mode
        if( viewer->getRunFrameScheme() == osgViewer::ViewerBase::ON_DEMAND )
        {
            double dt = _lastFrameStartTime.time_s();
            if (dt < 0.01)
                OpenThreads::Thread::microSleep(static_cast<unsigned int>(1000000.0*(0.01-dt)));
        }

        // record start frame time
        _lastFrameStartTime.setStartTick();

        // make frame
        if( viewer->getRunFrameScheme() == osgViewer::ViewerBase::ON_DEMAND )
        {
            if( viewer->checkNeedToDoFrame() )
            {
                viewer->frame();
            }
        }
        else
        {
            viewer->frame();
        }
    }
}

QtWidget::QtWidget(QWidget* parent)
    :QOpenGLWidget(parent)
{
    _devicePixelRatio=devicePixelRatio();
}
QtWidget::~QtWidget()
{
    if(_gw)
    {
        _gw->close();
        _gw->setGLWidget(0);
        _gw=0;
    }
}
void QtWidget::keyPressEvent(QKeyEvent *event)
{
    int value = s_QtKeyboardMap.remapKey( event );
    _gw->getEventQueue()->keyPress( value );
}
void QtWidget::keyReleaseEvent(QKeyEvent *event)
{
    if( event->isAutoRepeat() )
    {
        event->ignore();
    }
    else
    {
        int value = s_QtKeyboardMap.remapKey( event );
        _gw->getEventQueue()->keyRelease( value );
    }

}
void QtWidget::mouseMoveEvent(QMouseEvent *event)
{
        _gw->getEventQueue()->mouseMotion( event->x()*_devicePixelRatio, event->y()*_devicePixelRatio );
}
void QtWidget::wheelEvent(QWheelEvent *event)
{
    //    _gw->getEventQueue()->mouseScroll(
    //        event->orientation() == Qt::Vertical ?
    //            (event->delta()>0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN) :
    //            (event->delta()>0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT) );
}
void QtWidget::resizeGL(int w, int h)
{
    if (!_gw)
        return;
    int scaled_width = static_cast<int>(w*_devicePixelRatio);
    int scaled_height = static_cast<int>(h*_devicePixelRatio);
//    _gw->resized( x(), y(), scaled_width,  scaled_height);
//    _gw->getEventQueue()->windowResize( x(), y(), scaled_width, scaled_height );
}
void QtWidget::paintGL()
{
//    if(_gw)
//    _gw->requestRedraw();
}
void QtWidget::initializeGL()
{
//    if(_gw)
//    {
//        if(!_gw->isRealized())
//            _gw->realize();
//    }
}
void QtWidget::closeEvent(QCloseEvent *event)
{
    if(_gw)
    {
        double eventTime  = _gw->getEventQueue()->getTime();
        _gw->getEventQueue()->closeWindow(eventTime);
    }
}
void QtWidget::processDeferredEvents()
{
    QQueue<QEvent::Type> deferredEventQueueCopy;
    {
        QMutexLocker lock(&_deferredEventQueueMutex);
        deferredEventQueueCopy = _deferredEventQueue;
        _eventCompressor.clear();
        _deferredEventQueue.clear();
    }

    while (!deferredEventQueueCopy.isEmpty())
    {
        QEvent event(deferredEventQueueCopy.dequeue());
        QOpenGLWidget::event(&event);
    }
}
bool QtWidget::event(QEvent *event)
{

    if (event->type() == QEvent::Hide)
    {
        // enqueue only the last of QEvent::Hide and QEvent::Show
        enqueueDeferredEvent(QEvent::Hide, QEvent::Show);
        return true;
    }
    else if (event->type() == QEvent::Show)
    {
        // enqueue only the last of QEvent::Show or QEvent::Hide
        enqueueDeferredEvent(QEvent::Show, QEvent::Hide);
        return true;
    }
    else if (event->type() == QEvent::ParentChange)
    {
        // enqueue only the last QEvent::ParentChange
        enqueueDeferredEvent(QEvent::ParentChange);
        return true;
    }

    // perform regular event handling
    return QOpenGLWidget::event( event );
}
QtGraphicsWindow::QtGraphicsWindow(osg::GraphicsContext::Traits* traits)
    :_realized(false)
{
    _traits=traits;
    init();
}
QtGraphicsWindow::~QtGraphicsWindow()
{

}
void QtGraphicsWindow::init()
{
    //先利用_traits设置界面
    _widget=new QtWidget;
    _widget->setWindowTitle( _traits->windowName.c_str() );
    _widget->move( _traits->x, _traits->y );
    if ( !_traits->supportsResize )
        _widget->setFixedSize( _traits->width, _traits->height );
    else
        _widget->resize( _traits->width, _traits->height );

    _widget->setMouseTracking(true);
    useCursor( _traits->useCursor );

    // initialize State
    setState( new osg::State );
    getState()->setGraphicsContext(this);

    // initialize contextID
    if ( _traits.valid() && _traits->sharedContext.valid() )
    {
        getState()->setContextID( _traits->sharedContext->getState()->getContextID() );
        incrementContextIDUsageCount( getState()->getContextID() );
    }
    else
    {
        getState()->setContextID( osg::GraphicsContext::createNewContextID() );
    }

    // make sure the event queue has the correct window rectangle size and input range
    getEventQueue()->syncWindowRectangleWithGraphicsContext();
}
void QtGraphicsWindow::useCursor(bool cursorOn)
{
    if(_widget)
    {
        if ( !cursorOn ) _widget->setCursor( Qt::BlankCursor );
        else _widget->setCursor( _currentCursor );
    }
}
void QtGraphicsWindow::closeImplementation()
{
    if(_widget)
    {
        _widget->close();
    }
    _realized=false;
}
void QtGraphicsWindow::setGLWidget(QtWidget* w)
{
    _widget=w;
}
bool QtGraphicsWindow::valid() const
{
    return _widget && _widget->isValid();
}
bool QtGraphicsWindow::realizeImplementation()
{
    if(!_widget)
        return false;
    // save the current context
    // note: this will save only Qt-based contexts
    QOpenGLContext *savedContext =QOpenGLContext::currentContext();

    // initialize GL context for the widget
    if ( !valid() )
        _widget->initializeGL();

    // make current
    _realized = true;
    bool result = makeCurrent();
    _realized = false;

    // fail if we do not have current context
    if ( !result )
    {
        if ( savedContext )
            savedContext->makeCurrent(savedContext->surface());

        OSG_WARN << "Window realize: Can make context current." << std::endl;
        return false;
    }

    _realized = true;

    // make sure the event queue has the correct window rectangle size and input range
    getEventQueue()->syncWindowRectangleWithGraphicsContext();

    // make this window's context not current
    // note: this must be done as we will probably make the context current from another thread
    //       and it is not allowed to have one context current in two threads
    if( !releaseContext() )
        OSG_WARN << "Window realize: Can not release context." << std::endl;

    // restore previous context
    if ( savedContext )
        savedContext->makeCurrent(savedContext->surface());

    return true;
}
bool QtGraphicsWindow::makeCurrentImplementation()
{
    if(!_widget)
        return false;
    if (_widget->getNumDeferredEvents() > 0)
        _widget->processDeferredEvents();

    _widget->makeCurrent();

    return true;
}
bool QtGraphicsWindow::isRealizedImplementation() const
{
    return _realized;
}
bool QtGraphicsWindow::releaseContextImplementation()
{
    if(!_widget)
        return false;
    _widget->doneCurrent();
    return true;
}
void QtGraphicsWindow::runOperations()
{
    if(!_widget)
        return;
    if(_widget->getNumDeferredEvents()>0)
    {
        _widget->processDeferredEvents();
    }
    if(QOpenGLContext::currentContext()!=_widget->context())
        _widget->makeCurrent();
    osg::GraphicsContext::runOperations();
}
void QtGraphicsWindow::swapBuffersImplementation()
{
    if(!_widget)
        return;
    if (_widget->getNumDeferredEvents() > 0)
        _widget->processDeferredEvents();
    if(QOpenGLContext::currentContext()!=_widget->context())
        _widget->makeCurrent();
    QOpenGLContext* currentContext=QOpenGLContext::currentContext();
    currentContext->swapBuffers(currentContext->surface());
}
bool QtGraphicsWindow::setWindowRectangleImplementation(int x, int y, int width, int height)
{
    if(!_widget)
        return false;
    _widget->setGeometry(x,y,width,height);
}
void QtGraphicsWindow::getWindowRectangle(int &x, int &y, int &width, int &height)
{
    if(!_widget)
    {
        const QRect& geom=_widget->geometry();
        x=geom.x();
        y=geom.y();
        width=geom.width();
        height=geom.height();
    }
}
