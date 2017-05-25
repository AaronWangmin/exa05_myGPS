#-------------------------------------------------
#
# Project created by QtCreator 2017-05-12T10:43:36
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = exa05_myGPS
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app


SOURCES += main.cpp \
    rinex3x.cpp \
    satpos.cpp \
    gpshead.cpp \
    gstring.cpp \
    gtime.cpp

HEADERS += \
    gpshead.h \
    rinex3x.h \
    satpos.h \
    gstring.h \
    gtime.h
