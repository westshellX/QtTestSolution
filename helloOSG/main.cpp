#include "dialog.h"
#include "commLibSet.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;


    w.setGeometry( 100, 100, 800, 600 );
    w.show();

    return a.exec();
}
