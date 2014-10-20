#-------------------------------------------------
#
# Project created by QtCreator 2014-10-17T21:09:58
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project1
TEMPLATE = app

DEPENDPATH += .
INCLUDEPATH += .

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    openglwindow.cpp \
    renderwindow.cpp \
    tiny_obj_loader.cc \
    scenehandler.cpp

HEADERS  += mainwindow.h \
    openglwindow.h \
    renderwindow.h \
    tiny_obj_loader.h \
    scenehandler.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    scene.json
