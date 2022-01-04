#ifndef __MYGLWIDGET_H__
#define __MYGLWIDGET_H__

#include "inc.h"

#include "mycamera.h"
#include "solarSystem.h"
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

	void calcFPS();

private:
	int scene_id;
	int fps;
	void scene_0();
	void scene_1();

	
	QTimer* timer;
	SolarSystem* solarSystem;

	Camera camera;

};
#endif // __MYGLWIDGET_H__
