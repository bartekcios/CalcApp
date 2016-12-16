#-------------------------------------------------
#
# Project created by QtCreator 2016-11-20T21:58:56
#
#-------------------------------------------------

QT       += quick testlib

QT       -= gui

TARGET = tst_calcapptesttest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app


SOURCES += tst_calcapptesttest.cpp\
        ../CalcApp/calc.cpp
HEADERS  += ../CalcApp/calc.h
DEFINES += SRCDIR=\\\"$$PWD/\\\"
