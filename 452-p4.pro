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
    Link.cpp \
    canvas.cpp \
    connector.cpp

HEADERS  += mainwindow.h \
    Link.h \
    canvas.h \
    Utils.h \
    network.h

FORMS    += mainwindow.ui

CONFIG += qtestlib
