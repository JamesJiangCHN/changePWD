#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString strLibPath(QDir::toNativeSeparators(QApplication::applicationDirPath())+QDir::separator()+
    "plugins");
    a.addLibraryPath(strLibPath);

    MainWindow w;
    w.show();



    return a.exec();
}
