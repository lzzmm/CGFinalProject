QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console qt c++11

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += "include"
    

LIBS += \
	Glu32.lib \
	OpenGL32.lib
LIBS += \
    "lib\x64\glew32.lib"\
    "lib\x64\assimp-vc142-mt.lib"

SOURCES += \
    "src\main.cpp" \
    "src\myglwidget.cpp"
    

HEADERS += \
    "src\myglwidget.h"
    