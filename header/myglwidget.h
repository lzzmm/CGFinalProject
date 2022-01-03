#ifndef __MYGLWIDGET_H__
#define __MYGLWIDGET_H__

#ifdef MAC_OS
#include <QtOpenGL/QtOpenGL>
#else
#include <GL/glew.h>
#endif
#include <QtGui>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QtMath>

#include "GLFW/glfw3.h"

#include "mycamera.h"
#include "solarSystem.h"
// #include "textRender.h"

class MyGLWidget : public QOpenGLWidget {
	Q_OBJECT

public:
	MyGLWidget(QWidget* parent = nullptr);
	~MyGLWidget();

protected:
	void initializeGL();
	virtual void paintGL();
	void resizeGL(int width, int height);
	void keyPressEvent(QKeyEvent* e);
	virtual bool event(QEvent* e) override;
	//void mouseMoveEvent(QMouseEvent* e);
	//void wheelEvent(QWheelEvent* e);
	//void paintEvent(QPaintEvent* e);

	void calcFPS();

private:
	int scene_id;
	int fps;
	void scene_0();
	void scene_1();

	//QVector<GLfloat> vertices;
	//QVector<unsigned int> indices;
	QOpenGLShaderProgram shaderProgram;
	//QOpenGLBuffer VBO;	// 顶点缓冲对象
	//QOpenGLBuffer IBO;  // 索引缓冲对象
	//QOpenGLVertexArrayObject VAO;	// 顶点数组对象
	//QOpenGLTexture texture;	// 纹理
	QTimer* timer;
	SolarSystem* solarSystem;

	Camera camera;
};
#endif // __MYGLWIDGET_H__
