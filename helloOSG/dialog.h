#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>

class Dialog : public QWidget
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

public:

};

#endif // DIALOG_H
