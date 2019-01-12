#include "headers/mainwindow.h"
#include <QApplication>
#include "QStyleFactory"
#include "QDebug"
#include "QDir"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    QPixmap bkgnd(":/images/images/background.png");
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    w.setPalette(palette);
    w.show();

    return a.exec();
}
