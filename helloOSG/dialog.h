#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include <osg/ref_ptr>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include "qtgraphicswindow.h"

class Dialog : public QWidget
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

public:
    osg::ref_ptr<osgViewer::Viewer> _viewer;

};

#endif // DIALOG_H
