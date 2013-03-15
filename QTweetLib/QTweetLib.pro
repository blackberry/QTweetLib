TEMPLATE = lib

APP_NAME = libQTwLib05

CONFIG += qt warn_on cascades10

DEFINES += Q_OS_QNX
DEFINES += CORE_LIBRARY
DEFINES += QTWEETLIB_MAKEDLL

include(config.pri)

CONFIG += qt warn_on cascades10
CONFIG += sharedlib

QMAKE_CXXFLAGS += -g
QMAKE_CFLAGS += -g

QT += network core gui xml

INCLUDEPATH += ../src/QTweetLib-0.5/src
INCLUDEPATH += ../src/QTweetLib-0.5/src/qjson

SOURCES += ../src/QTweetLib-0.5/src/*.cpp
SOURCES += ../src/QTweetLib-0.5/src/qjson/*.cpp
SOURCES += ../src/QTweetLib-0.5/src/qjson/*.cc
    
HEADERS += ../src/QTweetLib-0.5/src/*.h
HEADERS += ../src/QTweetLib-0.5/src/qjson/*.h
HEADERS += ../src/QTweetLib-0.5/src/qjson/*.hh

