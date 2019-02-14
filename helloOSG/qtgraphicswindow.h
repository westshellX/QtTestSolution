#ifndef QTGRAPHICSWINDOW_H
#define QTGRAPHICSWINDOW_H
#include <osgViewer/GraphicsWindow>
#include <osg/GraphicsContext>
#include <osg/observer_ptr>
#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <osgViewer/ViewerBase>
#include <QMutex>
#include <QQueue>
#include <QKeyEvent>

//提前声明

class QtGraphicsWindow;

void setViewer( osgViewer::ViewerBase *viewer );

class QtWidget: public QOpenGLWidget
{
public:
    QtWidget(QWidget* parent=nullptr);
    ~QtWidget();


    virtual void keyPressEvent( QKeyEvent* event ) override;
    virtual void keyReleaseEvent( QKeyEvent* event ) override;

    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void wheelEvent( QWheelEvent* event );

    virtual void paintGL() override;
    virtual void resizeGL(int w,int h) override;
    virtual void initializeGL() override;

    int getNumDeferredEvents()
    {
        QMutexLocker lock(&_deferredEventQueueMutex);
        return _deferredEventQueue.count();
    }
    void enqueueDeferredEvent(QEvent::Type eventType, QEvent::Type removeEventType = QEvent::None)
    {
        QMutexLocker lock(&_deferredEventQueueMutex);

        if (removeEventType != QEvent::None)
        {
            if (_deferredEventQueue.removeOne(removeEventType))
                _eventCompressor.remove(eventType);
        }

        if (_eventCompressor.find(eventType) == _eventCompressor.end())
        {
            _deferredEventQueue.enqueue(eventType);
            _eventCompressor.insert(eventType);
        }
    }
    void processDeferredEvents();
protected:
    virtual void closeEvent(QCloseEvent *event) override;
    virtual bool event(QEvent* event) override;


public:
    qreal _devicePixelRatio;
    QtGraphicsWindow* _gw;
    QMutex _deferredEventQueueMutex;
    QQueue<QEvent::Type> _deferredEventQueue;
    QSet<QEvent::Type> _eventCompressor;
};

//编写一个简单的GraphicsWindow
class QtGraphicsWindow: public osgViewer::GraphicsWindow
{
public:
    QtGraphicsWindow(osg::GraphicsContext::Traits* traits);
    ~QtGraphicsWindow();

    //主要是通过traits来设置state
    void init();


    inline QtWidget* getGLWidget() { return _widget; }
    inline const QtWidget* getGLWidget() const { return _widget; }
    void setGLWidget(QtWidget* w=0);
    void useCursor(bool cursorOn);

    virtual bool setWindowRectangleImplementation( int x, int y, int width, int height );
    virtual void getWindowRectangle( int& x, int& y, int& width, int& height );

    virtual bool valid() const;
    virtual bool realizeImplementation();
    virtual bool isRealizedImplementation() const;
    virtual void closeImplementation();
    virtual bool makeCurrentImplementation();
    virtual bool releaseContextImplementation();
    virtual void swapBuffersImplementation();
    virtual void runOperations();

protected:
    QtWidget* _widget;
    bool _realized;
    QCursor _currentCursor;
};

#endif // QTGRAPHICSWINDOW_H
