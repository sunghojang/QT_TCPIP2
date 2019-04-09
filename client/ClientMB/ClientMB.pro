#-------------------------------------------------
#
# Project created by QtCreator 2018-08-22T17:55:54
#
#-------------------------------------------------

QT       += core gui testlib

QT           += network


CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClientMB
TEMPLATE = app


SOURCES += main.cpp\
        client.cpp

HEADERS  += client.h

FORMS    += client.ui
