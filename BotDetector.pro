#-------------------------------------------------
#
# Project created by QtCreator 2017-10-04T12:17:59
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BotDetector
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    forms\mainwindow.cpp \
    utils\hexdump.cpp \
    utils\booleanbytewrapper.cpp \
    utils\byteorder.cpp \
    utils\logger.cpp \
    io\binaryreader.cpp \
    io\binarywriter.cpp \
    io\types\binary64.cpp \
    io\types\int64.cpp \
    io\types\uint64.cpp \
    forms/console.cpp \
    network/server.cpp \
    network/client.cpp \
    network/proxy.cpp \
    messages/imessage.cpp \
    network/packet.cpp

HEADERS += \
    forms\mainwindow.h \
    utils\hexdump.h \
    utils\booleanbytewrapper.h \
    utils\byteorder.h \
    utils\types.h \
    utils\logger.h \
    utils/signleton.h \
    io\binaryreader.h \
    io\binarywriter.h \
    io\types\binary64.h \
    io\types\int64.h \
    io\types\uint64.h \
    forms/console.h \
    network/server.h \
    network/client.h \
    network/proxy.h \
    messages/imessage.h \
    network/packet.h

FORMS += \
    forms\mainwindow.ui \
    forms/console.ui

RESOURCES += \
    resources.qrc

