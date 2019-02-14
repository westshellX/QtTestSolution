#include "OSGWidget.h"
#include "commLibSet.h"
#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow view;

    OSGWidget* w;
    QObject::connect(w, &OSGWidget::initialized, [w]() {
        QString sample = "cow.osg";
        osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(sample.toStdString());
        if (model)
            w->m_renderer->viewer()->setSceneData(model);
        else
            qDebug() << "Failed to load " << sample;

        w->m_renderer->viewer()->setCameraManipulator(new osgGA::TrackballManipulator());
    });
    view.setCentralWidget(w);
    view.resize(1024, 768);
    view.show();
    return a.exec();
}
