#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    InitVRCom();
    CreateServer();
    ui->setupUi(this);

}

Dialog::~Dialog()
{
    ClearVRCom();
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    std::string str="Hello world!";
    qDebug()<<str.c_str();
    VR_CUSTOM_CMDDATA cd;
    strcpy(cd.szCmd, str.c_str());
    SendVRCommandSvr2Clt(cd);
}
