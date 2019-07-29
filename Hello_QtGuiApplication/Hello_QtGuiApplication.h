#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Hello_QtGuiApplication.h"

class Hello_QtGuiApplication : public QMainWindow
{
	Q_OBJECT

public:
	Hello_QtGuiApplication(QWidget *parent = Q_NULLPTR);

private:
	Ui::Hello_QtGuiApplicationClass ui;
};
