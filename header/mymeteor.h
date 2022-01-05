#ifndef __MYMETEOR_H__
#define __MYMETEOR_H__

#ifdef MAC_OS
#include <QtOpenGL/QtOpenGL>
#else
#include <GL/glew.h>
#endif
#include <QtGui>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QtMath>

class Meteor
{
public:
	Meteor(QWidget* widget);
	void initMeteor();
	void drawMeteor();
	void explode();					//爆炸效果
	void meteor_run();				//流星效果
	void change_rainbow();			//没什么用的——改成彩虹颜色
	void change_color();			//没什么用的——改变颜色

private:
	QWidget* widget;


	static const int MAX_PARTICLES = 2000;          //最大粒子数
	static const GLfloat COLORS[12][3];             //彩虹的颜色
	bool m_Rainbow;                                 //是否为彩虹模式
	GLuint m_Color;                                 //当前的颜色
	float m_Slowdown;                               //减速粒子
	float m_xSpeed;                                 //x方向的速度
	float m_ySpeed;                                 //y方向的速度
	float m_Deep;                                   //移入屏幕的距离

	int screen_width;
	int screen_height;

	struct Particle                                 //创建粒子结构体
	{
		bool active;                                //是否激活
		float life;                                 //粒子生命
		float fade;                                 //衰减速度

		float r, g, b;                              //粒子颜色
		float x, y, z;                              //位置坐标
		float xi, yi, zi;                           //各方向速度
		float xg, yg, zg;                           //各方向加速度
	} m_Particles[MAX_PARTICLES];                   //存放所有粒子的数组
	//Camera camera;
};
#endif // __MYMETEOR_H__
