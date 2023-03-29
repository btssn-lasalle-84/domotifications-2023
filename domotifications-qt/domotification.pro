QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    Communication.cpp \
    Domotification.cpp \
    IhmDomotifications.cpp \
    Module.cpp \
    main.cpp

HEADERS += \
    Communication.h \
    Domotification.h \
    IhmDomotifications.h \
    Module.h

FORMS += \
    IhmDomotifications.ui

#RESOURCES += \
#    images.qrc
