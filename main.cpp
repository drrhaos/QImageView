#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QStyle>
#include <QDebug>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    QSettings t_set("settings.ini", QSettings::IniFormat);
    QTranslator myTranslator;
    myTranslator.load("language/" + t_set.value("language").toString());
    a.installTranslator(&myTranslator);

    QString fileName("");
    QStringList list = a.arguments();
    if (list.size() > 1)
         fileName = list.at(1);


    MainWindow w(0, fileName);
    w.show();
    return a.exec();
}
