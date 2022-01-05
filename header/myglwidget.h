#ifndef __MYGLWIDGET_H__
#define __MYGLWIDGET_H__

#include "inc.h"

#include "mycamera.h"
#include "solarSystem.h"
#include "mymeteor.h"
#include "skybox.h"
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

	bool get_fullscreen();
	void set_fullscreen(bool val);

	void calcFPS();

private:
	bool fullscreen;
	int scene_id;
	int fps;
	void scene_0();
	void scene_1();

	
	QTimer* timer;
	SolarSystem* solarSystem;

	Camera camera;
	Meteor meteor;
	Skybox skybox;

};
#endif // __MYGLWIDGET_H__
