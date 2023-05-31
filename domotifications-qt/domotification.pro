QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Communication.cpp \
    Domotification.cpp \
    IhmDomotifications.cpp \
    Module.cpp \
    main.cpp


HEADERS += \
    Communication.h \
    Constantes.h \
    Domotification.h \
    IhmDomotifications.h \
    Module.h

FORMS += \
    IhmDomotifications.ui

RESOURCES += \
    images.qrc

COPIES += configuration
configuration.files = config.ini
configuration.path = $$OUT_PWD/
configuration.base = $$PWD/

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
