#-------------------------------------------------
#
# Project created by QtCreator 2013-03-22T09:57:25
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 452-p3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvas.cpp

HEADERS  += mainwindow.h \
    canvas.h \
    Utils.h

FORMS    += mainwindow.ui

CONFIG += qtestlib
