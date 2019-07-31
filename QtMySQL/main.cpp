#include <QCoreApplication>
#include <iostream>
#include <QSqlDatabase>
#include <QPluginLoader>
#include <QDebug>
#include "connection.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout<<"Hello world!"<<std::endl;
    QSqlDatabase d=QSqlDatabase::addDatabase("QMYSQL");
    d.setHostName("localhost");
    d.setDatabaseName("navshipmodel");
    d.setUserName("westshell");
    d.setPassword("love_mysql");
    d.setPort(3306);
    if(d.open())
        std::cout<<"Hi mysql!����"<<std::endl;
    else
        std::cout<<"failed!"<<std::endl;

//    createConnection();
    QPluginLoader loader;
    qDebug()<<loader.load();
    qDebug()<<loader.errorString();
    qDebug()<<QSqlDatabase::drivers();
    return a.exec();
}
