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
#define ACC_RATE 10.0f	// Shift 加速移动倍数
#define CAM_SPEED 1.5f	// 相机速度
#define SENSITIVITY 0.001f	 // 鼠标灵敏度
#define PLANET_AMBI 0.5f		 // 行星环境光强度
#define PLANET_DIFF 1.0f		 // 行星漫反射光强度
#define PLANET_SPEC 0.6f		 // 行星镜面反射光强度
#define PLANET_SHININESS 32.0f	 // 镜面反射强度

#define SEMI_AXIS_SCALE 0.3f // 行星半长轴距离倍数
#define DEFAULT_SOLAR_SYSTEM_RUN_SPEED 0.1f // 默认太阳系运转速度，1为每帧一地球日

#endif // __INC_H__