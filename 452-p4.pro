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
    canvas.cpp \
    wheel.cpp \
    sensor.cpp \
    robotmanager.cpp \
    robot.cpp \
    lightsource.cpp

HEADERS  += mainwindow.h \
    canvas.h \
    Utils.h \
    wheel.h \
    sensor.h \
    robotmanager.h \
    robot.h \
    lightsource.h

FORMS    += mainwindow.ui

CONFIG += qtestlib
