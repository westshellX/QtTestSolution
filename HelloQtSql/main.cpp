#include <QCoreApplication>
#include <QTextCodec>
#include <iostream>
#include <QSqlDatabase>
#include <QSqlQuery>
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mydata");       //这里输入你的数据库名
    db.setUserName("westshell");
    db.setPassword("1ove_mysql");   //这里输入你的密码
    if (!db.open())
    {
       std::cout<<"database open failed!"<<std::endl;
        return false;
    }
    std::cout<<"open database succesfull!"<<std::endl;
    //下面来创建表
    // 如果 MySQL 数据库中已经存在同名的表， 那么下面的代码不会执行
    QSqlQuery query(db);
    // 使数据库支持中文
    query.exec("SET NAMES 'Latin1'");
    // 创建 course 表
    query.exec("create table if not exists course (id int primary key, "
               "name varchar(20), teacher varchar(20))");
    query.exec("insert into course values(0, '数学', '刘老师')");
    query.exec("insert into course values(1, '英语', '张老师')");
    query.exec("insert into course values(2, '计算机', '李老师')");
    return true;
}

int main(int argc, char *argv[])
{
    //解决汉字乱码的问题
    QTextCodec* codec=QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QCoreApplication a(argc, argv);
    std::cout<<"Hello Qt SQl!"<<std::endl;
    createConnection();
    return a.exec();
}
