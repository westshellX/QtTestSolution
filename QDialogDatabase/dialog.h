#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "st_shipTypeData.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
private:
    ST_SHIPTYPE m_stShipType[SHIPTYPE_NUM];
private slots:
    void on_openShipXXXButton_clicked();

    void on_saveShipDataButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
