#-------------------------------------------------
#
# Project created by QtCreator 2014-12-27T21:25:53
#
#-------------------------------------------------

QT       += core gui
LIBS += -lws2_32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScreenShot
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    settingdialog.cpp \
    settings.cpp \
    screenshot.cpp \
    save.cpp
HEADERS  += mainwindow.h \
    settingdialog.h \
    settings.h \
    screenshot.h \
    save.h 

FORMS    += mainwindow.ui \
    settingdialog.ui

RESOURCES += \
    resource.qrc
