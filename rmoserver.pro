QT += core network
QT -= gui

CONFIG += c++11

TARGET = rmoserver
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
    src/Server.h \
    src/LocalServer.h \
    src/HTTPServer.h \
    qhttpserver/src/qhttpconnection.h \
    qhttpserver/src/qhttprequest.h \
    qhttpserver/src/qhttpresponse.h \
    qhttpserver/src/qhttpserver.h \
    qhttpserver/src/qhttpserverapi.h \
    qhttpserver/src/qhttpserverfwd.h

SOURCES += main.cpp \
    src/Server.cpp \
    src/LocalServer.cpp \
    src/HTTPServer.cpp \
    qhttpserver/src/qhttpconnection.cpp \
    qhttpserver/src/qhttprequest.cpp \
    qhttpserver/src/qhttpresponse.cpp \
    qhttpserver/src/qhttpserver.cpp \
    qhttpserver/http-parser/http_parser.c

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH = src/ qhttpserver/src/ qhttpserver/http-parser/

include(cbor-qt/cbor.pri)

#LIBS += -lqhttpserver
