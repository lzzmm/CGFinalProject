QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console qt c++11

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
    "include" \
    "header"


LIBS += \
	Glu32.lib \
	OpenGL32.lib
LIBS += \
    "lib\x64\glew32.lib"\
    "lib\x64\glfw3.lib" \
    "lib\x64\assimp-vc142-mt.lib"


SOURCES += \
    "src\main.cpp" \
    "src\myglwidget.cpp"    \
    "src\mycamera.cpp"      \
    "src\ball.cpp"          \
    "src\solarSystem.cpp"   \

    

HEADERS += \
    "header\myglwidget.h"   \
    "header\mycamera.h"     \
    "header\ball.h"         \
    "header\solarSystem.h"  \


RESOURCES += resource/resource.qrc

DEPENDPATH += .