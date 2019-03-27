#-------------------------------------------------
#
# Project created by QtCreator 2018-11-12T11:35:46
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Njupt
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        loginwindow.cpp \
    check.cpp \
    input.cpp \
    out_stock.cpp \
    stock_system.cpp \
    change.cpp \
    journal.cpp \
    mypaint.cpp \
    warning_line.cpp \
    zhuce.cpp

HEADERS += \
        loginwindow.h \
    check.h \
    check.h \
    input.h \
    out_stock.h \
    stock_system.h \
    change.h \
    journal.h \
    mypaint.h \
    warning_line.h \
    zhuce.h

FORMS += \
        loginwindow.ui \
    input.ui \
    out_stock.ui \
    stock_system.ui \
    change.ui \
    Journal.ui \
    warning_line.ui \
    zhuce.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    img.qrc
