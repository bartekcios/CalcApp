#-------------------------------------------------
#
# Project created by QtCreator 2016-11-20T13:43:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalcApp
TEMPLATE = app
CONFIG += c++11
VERSION = 1.0.0

SOURCES += main.cpp\
        mainwindow.cpp \
    calc.cpp \
    memory.cpp

HEADERS  += mainwindow.h \
    calc.h \
    tst_calcapptesttest.h \
    memory.h \
    commontypedefs.h

FORMS    += mainwindow.ui
