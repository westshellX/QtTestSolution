#include "Hello_QtGuiApplication.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Hello_QtGuiApplication w;
	w.show();
	return a.exec();
}
