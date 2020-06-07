#-------------------------------------------------
#
# Project created by QtCreator 2020-05-05T10:56:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bilantafang
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    beifeng.cpp \
    dao.cpp \
    diren.cpp \
    kedie.cpp \
        main.cpp \
        mainwindow.cpp \
    qiye.cpp \
    selectionbox.cpp \
    shipParent.cpp \
    startfrom.cpp \
    wuqi.cpp

HEADERS += \
    beifeng.h \
    dao.h \
    diren.h \
    kedie.h \
        mainwindow.h \
    qiye.h \
    selectionbox.h \
    globalstruct.h \
    shipParent.h \
    startfrom.h \
    wuqi.h

FORMS += \
    startfrom.ui

RESOURCES += \
    image.qrc
