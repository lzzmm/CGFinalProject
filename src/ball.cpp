﻿#include "ball.h"

Ball::Ball()
	: texId(0), radius(1), pos(10.0f, 0.0f, 0.0f), revSpeed(1.0f), rotSpeed(2.0f), ambient(1.0f, 1.0f, 1.0f), diffuse(1.0f, 1.0f, 1.0f), specular(1.0f, 1.0f, 1.0f), shinniness(1.0f), revAngle(0.0f), rotAngle(0.0f), obliquity(23.44f), angleSpan(0.5), VBO(QOpenGLBuffer::VertexBuffer), IBO(QOpenGLBuffer::IndexBuffer), texture(QOpenGLTexture::Target2D) {
	//GLint index = 0;
	//GLfloat x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3;
	//for (int vAngle = -90; vAngle < 90; vAngle += angleSpan) {
	//    for (int hAngle = 0; hAngle <= 360; hAngle += angleSpan) {
	//        x0 = radius * cos(vAngle * PI / 180) * cos(hAngle * PI * 180);
	//        y0 = radius * cos(vAngle * PI / 180) * sin(hAngle * PI * 180);
	//        z0 = radius * sin(vAngle * PI / 180);

	//        x1 = radius * cos(vAngle * PI / 180) * cos((hAngle + angleSpan) * PI / 180);
	//        y1 = radius * cos(vAngle * PI / 180) * sin((hAngle + angleSpan) * PI / 180);
	//        z1 = radius * sin(vAngle * PI / 180);

	//        x2 = radius * cos((vAngle + angleSpan) * PI / 180) * cos((hAngle + angleSpan) * PI / 180);
	//        y2 = radius * cos((vAngle + angleSpan) * PI / 180) * sin((hAngle + angleSpan) * PI / 180);
	//        z2 = radius * sin((vAngle + angleSpan) * PI / 180);

	//        x3 = radius * cos((vAngle + angleSpan) * PI / 180) * cos(hAngle * PI / 180);
	//        y3 = radius * cos((vAngle + angleSpan) * PI / 180) * sin(hAngle * PI / 180);
	//        z3 = radius * sin((vAngle + angleSpan) * PI / 180);

	//        // vertices << x0 << y0 << z0 << x1 << y1 << z1 << x2 << y2 << z2 << x3 << y3 << z3;
	//        vertices << x1 << y1 << z1 << x3 << y3 << z3 << x0 << y0 << z0 << x1 << y1 << z1 << x2 << y2 << z2 << x3 << y3 << z3;
	//        indices << index+1 << index + 3 << index << index + 1 << index + 2 << index + 3;
	//        index += 4;
	//    }
	//}

	GLfloat u = 0, v = 0;
	GLint uStepNum = 360 / angleSpan;
	GLint vStepNum = 360 / angleSpan;
	GLfloat uStep = 1.0f / uStepNum;
	GLfloat vStep = 1.0f / vStepNum;
	GLfloat x = sin(PI * v) * cos(2 * PI * u);
	GLfloat y = sin(PI * v) * sin(2 * PI * u);
	GLfloat z = cos(PI * v);
	vertices << x << y << z << 0.5f << 1.0f;
	for (int i = 1; i < vStepNum; i++)
	{
		for (int j = 0; j < uStepNum; j++)
		{
			u = uStep * j;
			v = vStep * i;
			x = sin(PI * v) * cos(2 * PI * u);
			y = sin(PI * v) * sin(2 * PI * u);
			z = cos(PI * v);
			vertices << x << y << z << 1.0f - u << v;
		}
	}

	u = 1.0f;
	v = 1.0f;
	x = sin(PI * v) * cos(2 * PI * u);
	y = sin(PI * v) * sin(2 * PI * u);
	z = cos(PI * v);
	vertices << x << y << z << 0.5f << 0.0f;

	for (int i = 0; i <= uStepNum; i++) // 球体上第一层
	{
		indices << 0 << i + 1 << i + 2; // 上顶点总是第一个点
	};

	for (int i = 1; i < vStepNum - 1; i++) {
		int start = 1 + (i - 1) * (uStepNum + 1);
		for (int j = start; j < start + (1 + uStepNum); j++) {

			/*
			*       j
			*       |\
			*       | \
			*       |__\
			* j+uStepn j + (uStepnum + 1) % vStepnum
			*/
			indices << j << j + uStepNum + 1 << start + (1 + uStepNum) + ((j + 1 - start) % (1 + uStepNum));
			/*
			*
			*         j ___ ��j + 1��% uStepnum
			*           \  |
			*		     \ |
			*		      \|
			*     j + (uStepnum + 1) % vStepnum
			*/
			indices << j << start + (j + 1 - start) % (1 + uStepNum) << start + uStepNum + 1 + (j + 1 - start) % (1 + uStepNum);

		}
	}

	int last = 1 + (uStepNum + 1) * (vStepNum - 1);
	int start = 1 + (uStepNum + 1) * (vStepNum - 2);
	for (int i = 1 + (uStepNum + 1) * (vStepNum - 2); i < 1 + uStepNum * (vStepNum - 1); i++) // 球体上最后一层
	{
		indices << i << last << (last + ((1 + i) - start) % (1 + uStepNum)); // 逆时针排列
	}

	VAO.create();
	VBO.create();
	IBO.create();

	QOpenGLVertexArrayObject::Binder{ &VAO };

	VBO.bind();
	VBO.allocate(vertices.data(), sizeof(GLfloat) * vertices.size());
	VBO.release();

	IBO.bind();
	IBO.allocate(indices.data(), sizeof(unsigned int) * indices.size());
	IBO.release();

	texture.create();
	texture.setData(QImage(":/resource/textures/earth.jpg").mirrored());
	texture.setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
	texture.setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);
	//texture.setBorderColor(QColor(1.0f, 1.0f, 1.0f, 1.0f));
	texture.setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Linear);
	texture.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);
}

Ball::~Ball() {
}

Ball::Ball(GLint texId, GLfloat r, QVector3D& pos, GLfloat revS, GLfloat rotS, GLfloat obliquity, QVector3D& ambi, QVector3D& diff, QVector3D& spec, GLfloat s, GLfloat angleSpan)
	: texId(texId), radius(r), pos(pos), revSpeed(revS), rotSpeed(rotS), ambient(ambi), diffuse(diff), specular(spec), shinniness(s), revAngle(0.0f), rotAngle(0.0f), obliquity(obliquity), angleSpan(angleSpan), VBO(QOpenGLBuffer::VertexBuffer), IBO(QOpenGLBuffer::IndexBuffer), texture(QOpenGLTexture::Target2D) {
	GLfloat u = 0, v = 0;
	GLint uStepNum = 360 / angleSpan;
	GLint vStepNum = 360 / angleSpan;
	GLfloat uStep = 1.0f / uStepNum;
	GLfloat vStep = 1.0f / vStepNum;
	GLfloat x = sin(PI * v) * cos(2 * PI * u);
	GLfloat y = sin(PI * v) * sin(2 * PI * u);
	GLfloat z = cos(PI * v);
	vertices << x << y << z << 0.5f << 1.0f;
	for (int i = 1; i < vStepNum; i++)
	{
		for (int j = 0; j < uStepNum; j++)
		{
			u = uStep * j;
			v = vStep * i;
			x = sin(PI * v) * cos(2 * PI * u);
			y = sin(PI * v) * sin(2 * PI * u);
			z = cos(PI * v);
			vertices << x << y << z << 1.0f - u << v;
		}
	}

	u = 1.0f;
	v = 1.0f;
	x = sin(PI * v) * cos(2 * PI * u);
	y = sin(PI * v) * sin(2 * PI * u);
	z = cos(PI * v);
	vertices << x << y << z << 0.5f << 0.0f;

	for (int i = 0; i <= uStepNum; i++) // 球体上第一层
	{
		indices << 0 << i + 1 << i + 2; // 上顶点总是第一个点
	};

	for (int i = 1; i < vStepNum - 1; i++) {
		int start = 1 + (i - 1) * (uStepNum + 1);
		for (int j = start; j < start + (1 + uStepNum); j++) {

			/*
			*       j
			*       |\
			*       | \
			*       |__\
			* j+uStepn j + (uStepnum + 1) % vStepnum
			*/
			indices << j << j + uStepNum + 1 << start + (1 + uStepNum) + ((j + 1 - start) % (1 + uStepNum));
			/*
			*
			*         j ___ ��j + 1��% uStepnum
			*           \  |
			*		     \ |
			*		      \|
			*     j + (uStepnum + 1) % vStepnum
			*/
			indices << j << start + (j + 1 - start) % (1 + uStepNum) << start + uStepNum + 1 + (j + 1 - start) % (1 + uStepNum);

		}
	}

	int last = 1 + (uStepNum + 1) * (vStepNum - 1);
	int start = 1 + (uStepNum + 1) * (vStepNum - 2);
	for (int i = 1 + (uStepNum + 1) * (vStepNum - 2); i < 1 + uStepNum * (vStepNum - 1); i++) // 球体上最后一层
	{
		indices << i << last << (last + ((1 + i) - start) % (1 + uStepNum)); // 逆时针排列
	}
	VAO.create();
	VBO.create();
	IBO.create();

	QOpenGLVertexArrayObject::Binder{ &VAO };

	VBO.bind();
	VBO.allocate(vertices.data(), sizeof(GLfloat) * vertices.size());
	VBO.release();

	IBO.bind();
	IBO.allocate(indices.data(), sizeof(unsigned int) * indices.size());
	IBO.release();

	texture.create();
	texture.setData(QImage(":/resource/textures/earth.jpg").mirrored());
	texture.setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
	texture.setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);
	//texture.setBorderColor(QColor(1.0f, 1.0f, 1.0f, 1.0f));
	texture.setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Linear);
	texture.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);
}

void Ball::revolute() {
	revAngle = (revAngle + revSpeed) < 360 ? revAngle + revSpeed : 0;
}

void Ball::rotate() {
	rotAngle = (rotAngle + rotSpeed) < 360 ? rotAngle + rotSpeed : 0;
}

void Ball::drawBall(QOpenGLExtraFunctions* f, QMatrix4x4 view, QMatrix4x4 projection, QMatrix4x4 model, QOpenGLShaderProgram& shader) {

	QOpenGLVertexArrayObject::Binder{ &VAO };

	VBO.bind();
	IBO.bind();
	shader.bind();

	shader.setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(GLfloat) * 5); // Pos
	shader.enableAttributeArray(0);
	shader.setAttributeBuffer(2, GL_FLOAT, sizeof(GLfloat) * 3, 2, sizeof(GLfloat) * 5); // TexCoord
	shader.enableAttributeArray(2);

	//model.setToIdentity();
	model.rotate(revAngle, QVector3D(0.0f, 1.0f, 0.0f));  // 公转
	model.translate(pos);
	model.rotate(-revAngle, QVector3D(0.0f, 1.0f, 0.0f));
	model.rotate(obliquity, QVector3D(0.0f, 0.0f, 1.0f));// 轴倾角
	model.rotate(rotAngle, QVector3D(0.0f, 1.0f, 0.0f)); // 自转
	model.rotate(90, QVector3D(1.0f, 0.0f, 0.0f));

	shader.setUniformValue("model", model);
	shader.setUniformValue("view", view);
	shader.setUniformValue("projection", projection);

	texture.bind(1);
	shader.setUniformValue("ourTexture", 1);

	//glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	texture.release();
	shader.release();
	VBO.release();
	IBO.release();
}