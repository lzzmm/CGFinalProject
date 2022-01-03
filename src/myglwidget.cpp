#include "myglwidget.h"
#define sky_size 30.0f

MyGLWidget::MyGLWidget(QWidget* parent)
	: QOpenGLWidget(parent), scene_id(0)
	//, VBO(QOpenGLBuffer::VertexBuffer)
	//, IBO(QOpenGLBuffer::IndexBuffer)
	//, texture(QOpenGLTexture::Target2D)
	, camera(this) {

	timer = new QTimer(this);                                // 实例化一个定时器
	timer->start(16);                                        // 时间间隔设置为16ms，可以根据需要调整
	: QOpenGLWidget(parent)
	, scene_id(1)
	, VBO(QOpenGLBuffer::VertexBuffer)
	, IBO(QOpenGLBuffer::IndexBuffer)
	, texture(QOpenGLTexture::Target2D)
	, camera(this)
	, SkyboxVBO(QOpenGLBuffer::VertexBuffer)
	, SkyboxTexture(QOpenGLTexture::Target2D)
{

	vertices = {
		// 位置              // 颜色				// 纹理
		 0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // 右下
		-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // 左下
		-0.5f,  0.5f, 0.5f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // 左下
		 0.5f,  0.5f, 0.5f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // 右上
	};

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

	indices = {		// 注意索引从0开始
		 0, 1, 3,	// 第一个三角形
		 1, 2, 3	// 第二个三角形
	};

	timer = new QTimer(this); // 实例化一个定时器
	timer->start(16); // 时间间隔设置为16ms，可以根据需要调整
	connect(timer, SIGNAL(timeout()), this, SLOT(update())); // 连接update()函数，每16ms触发一次update()函数进行重新绘图
}

MyGLWidget::~MyGLWidget() {
	makeCurrent();
	delete this->timer;
	//texture.destroy();
	doneCurrent();
}

void MyGLWidget::initializeGL() {
	// this->initializeOpenGLFunctions();        //初始化opengl函数
void drawSkyBox(float x, float y, float z, float width, float height, float len)
{
	//获取中心点
	x = x - width / 2;
	y = y - height / 2;
	z = z - len / 2;

	glPushMatrix();

	//back face
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + width, y, z);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x + width, y + height, z);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, y + height, z);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, y, z);
	glEnd();

	//front face
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y, z + len);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y + height, z + len);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x + width, y + height, z + len);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + width, y, z + len);
	glEnd();


	//bottom face
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y, z);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y, z + len);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x + width, y, z + len);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + width, y, z);
	glEnd();

	//top face
	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + width, y + height, z);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x + width, y + height, z + len);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, y + height, z + len);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, y + height, z);
	glEnd();

	//left face
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y + height, z);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y + height, z + len);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, y, z + len);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, y, z);
	glEnd();

	//right face
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + width, y, z);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x + width, y, z + len);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x + width, y + height, z + len);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + width, y + height, z);
	glEnd();
	glPopMatrix();
}

void MyGLWidget::initializeGL()
{
	//this->initializeOpenGLFunctions();        //初始化opengl函数

	if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/resource/shaders/ball.vert")) { //添加并编译顶点着色器
		qDebug() << "ERROR:" << shaderProgram.log();                                                         // 编译出错时打印报错信息
	}
	if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resource/shaders/ball.frag")) { //添加并编译片段着色器
		qDebug() << "ERROR:" << shaderProgram.log();                                                           // 编译出错时打印报错信息
	}
	if (!shaderProgram.link()) {                     // 链接着色器
		qDebug() << "ERROR:" << shaderProgram.log(); // 编译出错时打印报错信息
	}
	/*
		VAO.create();       // 生成VAO对象
		VBO.create();       // 生成VBO对象
		IBO.create();       // 生成IBO对象

		VBO.bind();         // 将VBO绑定到当前的顶点缓冲对象（QOpenGLBuffer::VertexBuffer）中
		// 将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
		VBO.allocate(vertices.data(), sizeof(float) * vertices.size());

		// 创建纹理
		texture.create();
		//texture.setSize();
		texture.setData(QImage(":/resource/textures/test.png").mirrored());
		texture.setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
		texture.setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
		//texture.setBorderColor(QColor(1.0f, 1.0f, 1.0f, 1.0f));
		texture.setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Linear);
		texture.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);


		shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(GLfloat) * 5); // Pos
		shaderProgram.enableAttributeArray(0);
		//shaderProgram.setAttributeBuffer(1, GL_FLOAT, sizeof(GLfloat) * 3, 3, sizeof(GLfloat) * 8); // Color
		//shaderProgram.enableAttributeArray(1);
		//shaderProgram.setAttributeBuffer(2, GL_FLOAT, sizeof(GLfloat) * 3, 2, sizeof(GLfloat) * 5); // TexCoord
		//shaderProgram.enableAttributeArray(2);
	*/

	VAO.create();       // 生成VAO对象
	VBO.create();       // 生成VBO对象
	IBO.create();       // 生成IBO对象
	SkyboxVAO.create();       // 生成VAO对象


	VBO.bind();         // 将VBO绑定到当前的顶点缓冲对象（QOpenGLBuffer::VertexBuffer）中
	// 将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
	VBO.allocate(vertices.data(), sizeof(float) * vertices.size());

	// 创建纹理
	texture.create();
	//texture.setSize();
	texture.setData(QImage(":/resource/textures/test.png").mirrored());
	texture.setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	texture.setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
	//texture.setBorderColor(QColor(1.0f, 1.0f, 1.0f, 1.0f));
	texture.setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Linear);
	texture.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);

	SkyboxTexture.create();
	//texture.setSize();
	SkyboxTexture.setData(QImage(":/resource/textures/test.png").mirrored());
	SkyboxTexture.setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	SkyboxTexture.setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
	//texture.setBorderColor(QColor(1.0f, 1.0f, 1.0f, 1.0f));
	SkyboxTexture.setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Linear);
	SkyboxTexture.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);


	shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(GLfloat) * 8);
	shaderProgram.enableAttributeArray(0);
	shaderProgram.setAttributeBuffer(1, GL_FLOAT, sizeof(GLfloat) * 3, 3, sizeof(GLfloat) * 8);
	shaderProgram.enableAttributeArray(1);
	shaderProgram.setAttributeBuffer(2, GL_FLOAT, sizeof(GLfloat) * 6, 2, sizeof(GLfloat) * 8);
	shaderProgram.enableAttributeArray(2);


	glViewport(0, 0, width(), height());
	glEnable(GL_DEPTH_TEST);
	// glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	camera.init();
	// makeCurrent();
	/*test = new Ball();
	test->textureBind(":/resource/textures/earth.jpg");
	QVector3D a(0.0f, 0.0f, 0.0f);
	sun = new Ball(0, 2.0f, a, 0.0f, 0.1f, 0.0f, a, a, a, 0.0f, 1.0f);
	sun->textureBind(":/resource/textures/test.png");*/
	solarSystem = new SolarSystem();
}

void MyGLWidget::paintGL() {
	if (scene_id == 0) {
		scene_0();
	}
	else {
		scene_1();
	}
}

void MyGLWidget::resizeGL(int width, int height) {
	// if (height == 0)	// 防止被零除
	//{
	//	height = 1;		// 将高设为1
	// }
	glViewport(0, 0, width, height);
	update();
}

void MyGLWidget::keyPressEvent(QKeyEvent* e) {
	// Press 0 or 1 to switch the scene
	if (e->key() == Qt::Key_0) {
		scene_id = 0;
		update();
	}
	else if (e->key() == Qt::Key_1) {
		scene_id = 1;
		update();
	}
	else if (e->key() == Qt::Key_Escape) {
		close();
	}
}

void MyGLWidget::scene_0() {
	makeCurrent();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

void MyGLWidget::drawSkybox() {
	QOpenGLVertexArrayObject::Binder{ &SkyboxVAO };
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
}

void MyGLWidget::scene_1()
{

	QOpenGLVertexArrayObject::Binder{ &VAO };
	//VAO.bind();         // 绑定VAO，之后所以的顶点缓冲对象的操作都会存储到VAO中

void MyGLWidget::scene_1() {
#if 0
	QOpenGLVertexArrayObject::Binder{ &VAO };

	// VAO.bind();         // 绑定VAO，之后所有的顶点缓冲对象的操作都会存储到VAO中


	IBO.bind();         // 将IBO绑定到当前的索引缓冲对象（QOpenGLBuffer::IndexBuffer）中
	IBO.allocate(indices.data(), sizeof(unsigned int) * indices.size());

	glClearColor(0.1f, 0.5f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram.bind(); // 使用shaderProgram着色程序

	shaderProgram.setUniformValue("view", camera.getView());

	QMatrix4x4 projection;
	projection.perspective(45.0f, width() / (float)height(), 0.1f, 100.0f);
	shaderProgram.setUniformValue("projection", projection);

	QMatrix4x4 model;
	float time = QTime::currentTime().msecsSinceStartOfDay() / 1000.0;
	model.rotate(5 * time, QVector3D(1.0f, 0.0f, -1.0f));
	//model.scale(10.0f);
	shaderProgram.setUniformValue("model", model);

	//texture.bind(0);
	//shaderProgram.setUniformValue("ourTexture", 0);      // 让ourTexture着色采样器从纹理单元0中获取纹理数据
	//glDrawArrays(GL_POLYGON, 0, 4);
	drawSkybox();//绘制天空盒

	texture.release();
	SkyboxTexture.release();
	shaderProgram.release();

	calcFPS();
#endif
}

bool MyGLWidget::event(QEvent* e) {
	camera.handle(e);
	return QWidget::event(e); // 调用父类的事件分发函数
}

void MyGLWidget::calcFPS() {
	static unsigned int frames = 0;
	static float lastTime = QTime::currentTime().msecsSinceStartOfDay() / 1000.0;
	float currTime = QTime::currentTime().msecsSinceStartOfDay() / 1000.0;

	++frames;
	if (frames >= 10) {
		fps = frames / (currTime - lastTime);
		lastTime = currTime;
		frames = 0;
	}

	 printf("FPS: %d\n", fps);
}
