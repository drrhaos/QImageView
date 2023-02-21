#-------------------------------------------------
#
# Project created by QtCreator 2016-11-22T21:22:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QImageView
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mgraphicsview.cpp \
    msettings.cpp \
    mgraphicsscene.cpp \
    mresize.cpp

HEADERS  += mainwindow.h \
    mgraphicsview.h \
    msettings.h \
    mgraphicsscene.h \
    mresize.h

FORMS    += mainwindow.ui \
    msettings.ui \
    mresize.ui

RESOURCES += \
    res.qrc

TRANSLATIONS += language/English.ts \
                language/Russian.ts

DISTFILES +=
