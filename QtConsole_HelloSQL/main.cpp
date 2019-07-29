#include <QtCore/QCoreApplication>
#include <iostream>
#include <QSqlDatabase>
#include <QDebug>
#include <QtWidgets>
#include "connection.h"
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	std::cout << "Hello SQL world!" << std::endl;

	QSqlDatabase d = QSqlDatabase::addDatabase("QODBC");
	d.setHostName("localhost");
	d.setDatabaseName("navshipmodel");
	d.setUserName("root");
	d.setPassword("rootlove");
	d.setPort(3306);

	if (d.open())
		std::cout << "Hi mysql!Á¬½Ó" << std::endl;
	else
		std::cout << "Ê§°Ü" << std::endl;
	//createConnection();
	QPluginLoader loader;
	qDebug() << loader.load();
	qDebug() << loader.errorString();
	qDebug() << QSqlDatabase::drivers();

	return a.exec();
}
