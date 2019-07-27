#include <iostream>
#include <QtCore/QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>

#include "connection.h"
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QSqlDatabase d=QSqlDatabase::addDatabase("QMYSQL");
	d.setHostName("127.0.0.1");
	d.setDatabaseName("navshipmodel");
	d.setUserName("westshellShip");
	d.setPassword("11111111");
	d.setPort(3306);

	if(d.open())
		std::cout<<"Hi mysql!����"<<std::endl;
	else
		std::cout<<"����ʧ��"<<std::endl;
	qDebug()<<QSqlDatabase::drivers();
	return a.exec();
}
