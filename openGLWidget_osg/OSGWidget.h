#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include "osgrenderer.h"
class OSGWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    OSGWidget(QWidget *parent = nullptr);
    ~OSGWidget();

        OSGRenderer *m_renderer;
signals:
    void initialized();

protected:
     virtual void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void keyPressEvent( QKeyEvent* event ) override;
    void keyReleaseEvent( QKeyEvent* event ) override;
    void mousePressEvent( QMouseEvent* event ) override;
    void mouseReleaseEvent( QMouseEvent* event ) override;
    void mouseDoubleClickEvent( QMouseEvent* event ) override;
    void mouseMoveEvent( QMouseEvent* event ) override;
    void wheelEvent( QWheelEvent* event ) override;
};

#endif // WIDGET_H
