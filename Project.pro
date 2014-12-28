#-------------------------------------------------
#
# Project created by QtCreator 2014-11-11T22:18:18
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project
TEMPLATE = app

DEPENDPATH += .
INCLUDEPATH += .

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    openglwindow.cpp \
    renderwindow.cpp \
    tiny_obj_loader.cc \
    scenehandler.cpp \
    camera.cpp \
    objectmodel.cpp \
    light.cpp

HEADERS  += mainwindow.h \
    openglwindow.h \
    renderwindow.h \
    tiny_obj_loader.h \
    scenehandler.h \
    camera.h \
    objectmodel.h \
    light.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    scene.json \
    chair.obj \
    desk.obj \
    gouraud.vert \
    gouraud.frag \
    flat.frag \
    flat.vert \
    phong.frag \
    phong.vert \
    simple.frag \
    simple.vert
