#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget* parent)
	: QOpenGLWidget(parent)
	, scene_id(0)
	, camera(this)
{
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

	glViewport(0, 0, width(), height());
	glEnable(GL_DEPTH_TEST);
	// glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	camera.init();

	solarSystem = new SolarSystem();
	solarSystem->runSpeed = 0.01f;
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

void MyGLWidget::scene_0() 
{
	makeCurrent();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	QMatrix4x4 view = camera.getView();
	QMatrix4x4 projection;
	projection.perspective(45.0f, width() / (float)height(), 0.1f, 1000.0f);
	shaderProgram.setUniformValue("projection", projection);
	QMatrix4x4 model;

	model.setToIdentity();
	solarSystem->draw(QOpenGLContext::currentContext()->extraFunctions(), view, projection, model, shaderProgram);
	//calcFPS();
	doneCurrent();
}


void MyGLWidget::scene_1() 
{
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
