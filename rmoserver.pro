QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = rmoserver
TEMPLATE = app

SOURCES += main.cpp \
    src/Server.cpp \
    src/LocalServer.cpp \
    src/HTTPServer.cpp \
    qhttpserver/src/qhttpconnection.cpp \
    qhttpserver/src/qhttprequest.cpp \
    qhttpserver/src/qhttpresponse.cpp \
    qhttpserver/src/qhttpserver.cpp \
    qhttpserver/http-parser/http_parser.c \
    riot_os_cbor/cbor.c \
    structs/cmd_data_packer.c \
    structs/cmd_data_debug.c \
    src/MainWindow.cpp

HEADERS += \
    src/Server.h \
    src/LocalServer.h \
    src/HTTPServer.h \
    qhttpserver/src/qhttpconnection.h \
    qhttpserver/src/qhttprequest.h \
    qhttpserver/src/qhttpresponse.h \
    qhttpserver/src/qhttpserver.h \
    qhttpserver/src/qhttpserverapi.h \
    qhttpserver/src/qhttpserverfwd.h \
    riot_os_cbor/cbor.h \
    structs/cmd_data_packer.h \
    structs/cmd_data_debug.h \
    src/MainWindow.h
    src/commandType.h

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH = src/ qhttpserver/src/ qhttpserver/http-parser/ riot_os_cbor/ structs/

#include(cbor-qt/cbor.pri)

#LIBS += -lqhttpserver

FORMS += \
    src/mainwindow.ui
