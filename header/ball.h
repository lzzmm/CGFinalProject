#ifndef __BALL_H__
#define __BALL_H__

#include "inc.h"


class Ball {
public:
	Ball();
	Ball(GLint texId, GLfloat r, QVector3D pos, GLfloat revS, GLfloat rotS, GLfloat obliquity, QVector3D& ambi, QVector3D& diff, QVector3D& spec, GLfloat s, GLfloat angleSpan);
	~Ball();

	// 公转
	void revolute(GLfloat speed);
	// 自转
	void rotate(GLfloat speed);
	// 纹理绑定
	void textureBind(QString tex);
	// 画
	void drawBall(QOpenGLExtraFunctions* f, QMatrix4x4 view, QMatrix4x4 projection, QMatrix4x4 model, QOpenGLShaderProgram& shader);


private:
	GLint texId;        // 纹理 id
	GLfloat radius;     // 半径
	QVector3D pos;      // 位置
	GLfloat revSpeed;   // 公转速度
	GLfloat rotSpeed;   // 自转速度
	QVector3D ambient;   // 环境光
	QVector3D diffuse;   // 漫反射
	QVector3D specular;  // 镜面反射
	GLfloat shinniness; // 镜面反射强度
	GLfloat revAngle;     // 公转角度
	GLfloat rotAngle;     // 自转角度
	GLfloat obliquity;  // 转轴倾角
	GLfloat angleSpan; // 细分角度

	QOpenGLBuffer VBO;	// 顶点缓冲对象
	QOpenGLBuffer IBO;  // 索引缓冲对象
	QOpenGLVertexArrayObject VAO;	// 顶点数组对象
	QOpenGLTexture texture;	// 纹理
	QVector<GLfloat> vertices; // 顶点
	QVector<unsigned int> indices; // 索引
};

#endif // __BALL_H__