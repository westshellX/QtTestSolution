#include "dialog.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QTextCodec>
#include <iostream>
bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setUserName("smuShipModel");
    db.setDatabaseName("navShipmodel");
    db.setPassword("12345678");
    db.setPort(3306);
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;
    //常用船灯参数配置表
    query.exec("create table if not exists shipCommonLightParam ( lightID int primary key, "
               "lightName varchar(20), "
               "lightMode int, "
               "lightColor int, "
               "view00 float, "
               "view01 float, "
               "view02 float, "
               "view10 float, "
               "view11 float, "
               "view12 float )");

    //船舶与船灯关系一一对应表
    query.exec("create table if not exists shipLightSet ( shipID int primary key, "
               "lightID int, "
               "lightPosX float, "
               "lightPosY float, "
               "lightPosZ float )");
    //船舶模型参数表
    query.exec("create table if not exists modelPm ( shipID int primary key, "
               "len float, "
               "breadth float, "
               "draft float,  "
               "osModelPath varchar, "
               "tsModelPath varchar )");
    return true;
}

int main(int argc, char *argv[])
{
    //解决汉字乱码的问题
    QTextCodec* codec=QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);
    createConnection();

    Dialog w;
    w.show();

    return a.exec();
}
