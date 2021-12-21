#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

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

#include "GLFW/glfw3.h"

class MyGLWidget : public QOpenGLWidget {
	Q_OBJECT

public:
	MyGLWidget(QWidget* parent = nullptr);
	~MyGLWidget();

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void keyPressEvent(QKeyEvent* e);
	//void mouseMoveEvent(QMouseEvent* e);
	//void wheelEvent(QWheelEvent* e);

private:
	int scene_id;
	void scene_0();
	void scene_1();

	QVector<float> vertices;
	QVector<unsigned int> indices;
	QOpenGLShaderProgram shaderProgram;
	QOpenGLBuffer VBO;	// 顶点缓冲对象
	QOpenGLBuffer IBO;  // 索引缓冲对象
	QOpenGLVertexArrayObject VAO;	// 顶点数组对象
};
#endif // MYGLWIDGET_H
