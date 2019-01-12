QT += core

CONFIG += c++11

TARGET = pasgen-cli
CONFIG += console
CONFIG -= app_bundle
LIBS += -lbsd

TEMPLATE = app

SOURCES += main.cpp ../common.cpp
