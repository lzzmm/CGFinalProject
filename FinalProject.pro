QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console qt c++11

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += "Libraries\Includes"
    

LIBS += \
	Glu32.lib \
	OpenGL32.lib
LIBS += \
    "Libraries\Libs\glew32.lib"\
    "Libraries\Libs\assimp-vc142-mt.lib"

SOURCES += \
    main.cpp \
    myglwidget.cpp
    

HEADERS += \
    myglwidget.h
    