#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    MainWindow w;
    w.setStyleSheet("QMainWindow{border-image: url(:/image/background.jpg)}");//设置背景图片
    w.show();
    return a.exec();
}
