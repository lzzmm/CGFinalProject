#pragma once
#include "skybox.h"
#define sky_size 500.0f

Skybox::Skybox(QWidget* widget) :
	SkyboxVBO(QOpenGLBuffer::VertexBuffer),
	SkyboxTexture(QOpenGLTexture::Target2D)
{

	SkyboxVertices = {
		// 位置              // 颜色				// 纹理
		 1.0f * sky_size, -1.0f * sky_size, 1.0f * sky_size,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // 右下
		-1.0f * sky_size, -1.0f * sky_size, 1.0f * sky_size,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // 左下
		-1.0f * sky_size,  1.0f * sky_size, 1.0f * sky_size,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // 左下
		 1.0f * sky_size,  1.0f * sky_size, 1.0f * sky_size,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // 右上

		 1.0f * sky_size, -1.0f * sky_size, -1.0f * sky_size,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // 右下
		-1.0f * sky_size, -1.0f * sky_size, -1.0f * sky_size,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // 左下
		-1.0f * sky_size,  1.0f * sky_size, -1.0f * sky_size,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // 左下
		 1.0f * sky_size,  1.0f * sky_size, -1.0f * sky_size,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // 右上

		 1.0f * sky_size, 1.0f * sky_size,  -1.0f * sky_size,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // 右下
		 1.0f * sky_size, -1.0f * sky_size, -1.0f * sky_size,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // 左下
		 1.0f * sky_size, -1.0f * sky_size, 1.0f * sky_size,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // 左下
		 1.0f * sky_size, 1.0f * sky_size,  1.0f * sky_size,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // 右上

		 -1.0f * sky_size, 1.0f * sky_size,  -1.0f * sky_size, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // 右下
		 -1.0f * sky_size, -1.0f * sky_size, -1.0f * sky_size, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // 左下
		 -1.0f * sky_size, -1.0f * sky_size, 1.0f * sky_size,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // 左下
		 -1.0f * sky_size, 1.0f * sky_size,  1.0f * sky_size,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // 右上

		 1.0f * sky_size, 1.0f * sky_size, -1.0f * sky_size,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // 右下
		-1.0f * sky_size, 1.0f * sky_size, -1.0f * sky_size,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // 左下
		-1.0f * sky_size, 1.0f * sky_size, 1.0f * sky_size,    1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // 左下
		 1.0f * sky_size, 1.0f * sky_size, 1.0f * sky_size,    1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // 右上

		 1.0f * sky_size, -1.0f * sky_size, -1.0f * sky_size,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // 右下
		-1.0f * sky_size, -1.0f * sky_size, -1.0f * sky_size,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // 左下
		-1.0f * sky_size, -1.0f * sky_size, 1.0f * sky_size,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // 左下
		 1.0f * sky_size, -1.0f * sky_size, 1.0f * sky_size,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // 右上
	};
}

Skybox::~Skybox() {

}
void Skybox::drawSkybox(QMatrix4x4 view, QMatrix4x4 model, QMatrix4x4 projection) {
	shaderProgram.bind();
	float time = QTime::currentTime().msecsSinceStartOfDay() / 1000.0;
	model.rotate(10 * time, QVector3D(1.0f, 0.0f, -1.0f));//天空盒旋转

	shaderProgram.setUniformValue("view", view);
	shaderProgram.setUniformValue("projection", projection);
	shaderProgram.setUniformValue("model", model);

	SkyboxVAO.bind();
	SkyboxVBO.create();       // 生成VBO对象
	SkyboxVBO.bind();         // 将VBO绑定到当前的顶点缓冲对象（QOpenGLBuffer::VertexBuffer）中
	// 将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
	SkyboxVBO.allocate(SkyboxVertices.data(), sizeof(float) * SkyboxVertices.size());

	shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(GLfloat) * 8);
	shaderProgram.enableAttributeArray(0);
	shaderProgram.setAttributeBuffer(1, GL_FLOAT, sizeof(GLfloat) * 3, 3, sizeof(GLfloat) * 8);
	shaderProgram.enableAttributeArray(1);
	shaderProgram.setAttributeBuffer(2, GL_FLOAT, sizeof(GLfloat) * 6, 2, sizeof(GLfloat) * 8);
	shaderProgram.enableAttributeArray(2);

	SkyboxTexture.bind(0);
	shaderProgram.setUniformValue("ourTexture", 0);      // 让ourTexture着色采样器从纹理单元0中获取纹理数据

	glDrawArrays(GL_QUADS, 0, 24);
	SkyboxVAO.release();
	SkyboxTexture.release();
	shaderProgram.release();
}

void Skybox::init() {
	if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/resource/shaders/triangle.vert")) {     //添加并编译顶点着色器
		qDebug() << "ERROR:" << shaderProgram.log();    // 编译出错时打印报错信息
	}
	if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resource/shaders/triangle.frag")) {   //添加并编译片段着色器
		qDebug() << "ERROR:" << shaderProgram.log();    // 编译出错时打印报错信息
	}
	if (!shaderProgram.link()) {						// 链接着色器
		qDebug() << "ERROR:" << shaderProgram.log();    // 编译出错时打印报错信息
	}

	SkyboxVAO.create();       // 生成VAO对象

	SkyboxTexture.create();

	SkyboxTexture.setData(QImage(":/resource/textures/sky.png").mirrored());
	SkyboxTexture.setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	SkyboxTexture.setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);

	SkyboxTexture.setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Linear);
	SkyboxTexture.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);


}
