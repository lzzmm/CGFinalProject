#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget* parent)
	: QOpenGLWidget(parent)
	, scene_id(1)
	, VBO(QOpenGLBuffer::VertexBuffer)
	, IBO(QOpenGLBuffer::IndexBuffer)
{
	vertices = {
		 0.5f, 0.5f, 0.0f,   // 右上角
		 0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};
	indices = {    // 注意索引从0开始!
		 0, 1, 3, // 第一个三角形
		 1, 2, 3  // 第二个三角形
	};

}

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::initializeGL()
{
	//this->initializeOpenGLFunctions();        //初始化opengl函数

	if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/resource/shaders/triangle.vert")) {     //添加并编译顶点着色器
		qDebug() << "ERROR:" << shaderProgram.log();    // 编译出错时打印报错信息
	}
	if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resource/shaders/triangle.frag")) {   //添加并编译片段着色器
		qDebug() << "ERROR:" << shaderProgram.log();    // 编译出错时打印报错信息
	}
	if (!shaderProgram.link()) {						// 链接着色器
		qDebug() << "ERROR:" << shaderProgram.log();    // 编译出错时打印报错信息
	}

	VAO.create();       // 生成VAO对象
	VBO.create();       // 生成VBO对象
	IBO.create();       // 生成IBO对象


	glViewport(0, 0, width(), height());
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glDisable(GL_DEPTH_TEST);
}

void MyGLWidget::paintGL()
{
	if (scene_id == 0) {
		scene_0();
	}
	else {
		scene_1();
	}
}

void MyGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	update();
}

void MyGLWidget::keyPressEvent(QKeyEvent* e) {
	//Press 0 or 1 to switch the scene
	if (e->key() == Qt::Key_0) {
		scene_id = 0;
		update();
	}
	else if (e->key() == Qt::Key_1) {
		scene_id = 1;
		update();
	}
}

void MyGLWidget::scene_0()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, 100.0f, 0.0f, 100.0f, -1000.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(50.0f, 50.0f, 0.0f);

	//draw a diagonal "I"
	glPushMatrix();
	glColor3f(0.839f, 0.153f, 0.157f);
	//glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(-2.5f, -22.5f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(15.0f, 0.0f);
	glVertex2f(0.0f, 45.0f);

	glVertex2f(15.0f, 0.0f);
	glVertex2f(0.0f, 45.0f);
	glVertex2f(15.0f, 45.0f);

	glEnd();
	glPopMatrix();
}

void MyGLWidget::scene_1()
{
	//QOpenGLVertexArrayObject::Binder{ &VAO };


    VAO.bind();         // 绑定VAO，之后所以的顶点缓冲对象的操作都会存储到VAO中


	VBO.bind();         // 将VBO绑定到当前的顶点缓冲对象（QOpenGLBuffer::VertexBuffer）中
	//将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
	VBO.allocate(vertices.data(), sizeof(float) * vertices.size());

	
	IBO.bind();         // 将IBO绑定到当前的索引缓冲对象（QOpenGLBuffer::IndexBuffer）中
	IBO.allocate(indices.data(), sizeof(unsigned int) * indices.size());

	shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);
	shaderProgram.enableAttributeArray(0);


	glClearColor(0.1f, 0.5f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width(), 0.0f, height(), -1000.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.5 * width(), 0.5 * height(), 0.0f);*/

	//your implementation here, maybe you should write several glBegin
	//glPushMatrix();
	//your implementation
	shaderProgram.bind();                     //使用shaderProgram着色程序
	{
		//QOpenGLVertexArrayObject::Binder{ &VAO };
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	VAO.release();      // 解绑VAO，安全使用

	//glPopMatrix();
}