#include "OSGWidget.h"
#include <QWindow>
#include <QScreen>
#include <QApplication>
OSGWidget::OSGWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    ,m_renderer(nullptr)
{
}

OSGWidget::~OSGWidget()
{
}
void OSGWidget::initializeGL()
{
    m_renderer = new OSGRenderer(this);
    m_renderer->setup(this);
    QScreen *screen = windowHandle() && windowHandle()->screen() ? windowHandle()->screen() : qApp->screens().front();
    m_renderer->setupOSG(width(), height(), screen->devicePixelRatio());
    emit initialized();
}
void OSGWidget::resizeGL(int w, int h)
{
    QScreen *screen = windowHandle() && windowHandle()->screen() ? windowHandle()->screen() : qApp->screens().front();
    m_renderer->resize(w, h, screen->devicePixelRatio());
}

void OSGWidget::paintGL()
{
    m_renderer->render();
}

void OSGWidget::keyPressEvent(QKeyEvent *event)
{
    m_renderer->keyPressEvent(event);
}

void OSGWidget::keyReleaseEvent(QKeyEvent *event)
{
    m_renderer->keyReleaseEvent(event);
}

void OSGWidget::mousePressEvent(QMouseEvent *event)
{
    m_renderer->mousePressEvent(event);
}

void OSGWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_renderer->mouseReleaseEvent(event);
}

void OSGWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_renderer->mouseDoubleClickEvent(event);
}

void OSGWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_renderer->mouseMoveEvent(event);
}

void OSGWidget::wheelEvent(QWheelEvent *event)
{
    m_renderer->wheelEvent(event);
}
