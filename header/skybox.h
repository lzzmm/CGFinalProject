#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include <QSet>
#include <QVector3D>
#include <QEvent>
#include <QtGui>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QtMath>

class Skybox {
public:
	Skybox(QWidget* widget);
	~Skybox();
	void drawSkybox(QMatrix4x4 model, QMatrix4x4 projection);
	void init();
	QOpenGLShaderProgram shaderProgram;

private:
	QVector<float> SkyboxVertices;
	QOpenGLVertexArrayObject SkyboxVAO;	// 顶点数组对象
	QOpenGLBuffer SkyboxVBO;	// 顶点缓冲对象
	QOpenGLTexture SkyboxTexture;	// 纹理

};



#endif // __SKYBOX_H__#pragma once
