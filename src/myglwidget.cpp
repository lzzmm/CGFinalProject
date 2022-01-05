#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget* parent)
	: QOpenGLWidget(parent)
	, scene_id(0)
	, camera(this)
	, meteor(this)
	, fullscreen(false)
	, skybox(this)
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


	glViewport(0, 0, width(), height());
	glEnable(GL_DEPTH_TEST);
	// glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	camera.init();

	solarSystem = new SolarSystem();
	solarSystem->initShader();
	solarSystem->runSpeed = 0.02f;

	camera.init();
	skybox.init();


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

void MyGLWidget::keyPressEvent(QKeyEvent* e) {			//增加了一些按键功能
	//Press 0 or 1 to switch the scene
	if (e->key() == Qt::Key_0) {
		scene_id = 0;
		update();
	}
	else if (e->key() == Qt::Key_1) {
		scene_id = 1;
		update();
	}
	else if (e->key() == Qt::Key_F1) {				//F1为全屏和普通屏的切换键
		set_fullscreen(!get_fullscreen());
		if (get_fullscreen())
		{
			showFullScreen();
		}
		else
		{
			showNormal();
		}
		update();
	}
	else if (e->key() == Qt::Key_Escape) {         //ESC为退出键，结束整个进程
		close();
	}
	else if (e->key() == Qt::Key_Tab) {				//Tab按下，随机两个地方产生爆炸
		meteor.explode();
	}
	else if (e->key() == Qt::Key_Z) {				// Z 键，出现一个流星
		meteor.meteor_run();
	}
	else if (e->key() == Qt::Key_Return) {			//没什么用的——回车键为是否彩虹模式的切换键
		meteor.change_rainbow();
	}
	else if (e->key() == Qt::Key_Space) {			//也没什么用的——换颜色
		meteor.change_color();
	}
}

void MyGLWidget::scene_0()
{
	makeCurrent();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	QMatrix4x4 model;
	QMatrix4x4 view = camera.getView();
	QMatrix4x4 projection;
	projection.perspective(45.0f, width() / (float)height(), 0.1f, 1000.0f);
	model.setToIdentity();
    
    solarSystem->draw(QOpenGLContext::currentContext()->extraFunctions(), view, projection, model, camera.getCameraPos());

    skybox.drawSkybox(model, projection);
	meteor.drawMeteor();


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


bool MyGLWidget::get_fullscreen() {
	return fullscreen;
}

void MyGLWidget::set_fullscreen(bool val) {
	fullscreen = val;
}