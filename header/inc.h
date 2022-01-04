#ifndef __INC_H__
#define __INC_H__

#ifdef MAC_OS
#include <QtOpenGL/QtOpenGL>
#else
#include <GL/glew.h>
#endif

#include <QEvent>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QSet>
#include <QTime>
#include <QVector3D>
#include <QWidget>
#include <QtGui>
#include <QtMath>

#define PI 3.1415926535897932384626433832795028841971693993751f
// camera
#define ACC_RATE 10.0f
#define CAM_SPEED 1.5f
#define SENSITIVITY 0.001f

#endif // __INC_H__