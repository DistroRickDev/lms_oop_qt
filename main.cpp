#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    /* CAN'T TOUCH THIS (MCHAMMER CIRCA 1990's) */
    w.setFixedSize(QSize(1280,720)); //GOD FORBBIS YOU FROM TOUCHING THIS LINE OF CODE
    /* GOOD BOI/GURL */
    w.show();
    return a.exec();
}
