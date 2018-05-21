#-------------------------------------------------
#
# Project created by QtCreator 2018-05-21T12:29:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KURSACH_v2_0
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dir.cpp \
    file.cpp \
    deletedir.cpp \
    deletefile.cpp \
    copydir.cpp

HEADERS  += mainwindow.h \
    dir.h \
    file.h \
    deletedir.h \
    deletefile.h \
    copydir.h

FORMS    += mainwindow.ui
