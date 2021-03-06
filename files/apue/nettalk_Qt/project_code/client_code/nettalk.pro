#-------------------------------------------------
#
# Project created by QtCreator 2020-03-20T14:52:39
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nettalk
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
        main.cpp \
        nettalk.cpp \
    n_register.cpp \
    n_chat.cpp \
    addfriend.cpp \
    n_modify.cpp

HEADERS += \
        nettalk.h \
    n_register.h \
    n_chat.h \
    addfriend.h \
    proto.h \
    n_modify.h

FORMS += \
        nettalk.ui \
    n_register.ui \
    n_chat.ui \
    addfriend.ui \
    n_modify.ui

RESOURCES += \
    images.qrc

RC_ICONS += icon.ico
