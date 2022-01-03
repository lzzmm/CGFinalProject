#include "mymeteor.h"

#include <iostream>
#include <math.h>
const GLfloat Meteor::COLORS[][3] =                 //没什么用的——彩虹的颜色
{
	 {1.0f, 0.5f, 0.5f}, { 1.0f, 0.75f, 0.5f }, { 1.0f, 1.0f, 0.5f },
	 {0.75f, 1.0f, 0.5f}, { 0.5f, 1.0f, 0.5f }, { 0.5f, 1.0f, 0.75f },
	 {0.5f, 1.0f, 1.0f}, { 0.5f, 0.75f, 1.0f }, { 0.5f, 0.5f, 1.0f },
	 {0.75f, 0.5f, 1.0f}, { 1.0f, 0.5f, 1.0f }, { 1.0f, 0.5f, 0.75f }
};


Meteor::Meteor(QWidget* widget)
	: widget(widget) {
	m_Rainbow = false;
	m_Color = 0;
	m_Slowdown = 2.0f;
	m_xSpeed = 0.0f;
	m_ySpeed = 0.0f;
	m_Deep = -40.0f;

	screen_width = widget->width();
	screen_height = widget->height();

	float row1 = rand() % screen_width + (rand() % 100) * 0.01;
	float col1 = rand() % screen_height + (rand() % 100) * 0.01;

	float row2 = rand() % screen_width + (rand() % 100) * 0.01;
	float col2 = rand() % screen_height + (rand() % 100) * 0.01;

	float rand_y = rand() % 500 * 0.1;


	for (int i = 0; i < MAX_PARTICLES; i++)                 //循环初始化所以粒子
	{
		m_Particles[i].active = true;						//使所有粒子为激活状态
		m_Particles[i].life = 1.0f;							//所有粒子生命值为最大
		//随机生成衰减速率
		m_Particles[i].fade = float(rand() % 1000) / 1000.0f + 0.001;

		//粒子的颜色——白色
		m_Particles[i].r = 1.0f;
		m_Particles[i].g = 1.0f;
		m_Particles[i].b = 1.0f;

		//粒子的初始位置——随便给

		if (i < MAX_PARTICLES / 10) {
			m_Particles[i].x = row1;
			m_Particles[i].y = col1;
			m_Particles[i].z = -5.0f;

			//随机生成x、y、z轴方向速度
			m_Particles[i].xi = float((rand() % 50) - 26.0f) * 10.0f;
			m_Particles[i].yi = float((rand() % 50) - 25.0f) * 10.0f;
		}
		else if (i < MAX_PARTICLES / 10 * 2) {
			m_Particles[i].x = row2;
			m_Particles[i].y = col2;
			m_Particles[i].z = 5.0f;

			//随机生成x、y、z轴方向速度
			m_Particles[i].xi = float((rand() % 50) - 26.0f) * 10.0f;
			m_Particles[i].yi = float((rand() % 50) - 25.0f) * 10.0f;
		}
		else {
			m_Particles[i].fade = float(rand() % 1000) / 1000.0f + 0.001;
			m_Particles[i].x = 5 + rand() % 10 -5;
			m_Particles[i].y = rand_y + rand() % 10 + 10;
			m_Particles[i].z = 0.0f;

			m_Particles[i].xi = fabs(float((rand() % 50) - 26.0f) * 10.0f);
			m_Particles[i].yi = -fabs(float((rand() % 50) - 25.0f) * 10.0f);
		}


		m_Particles[i].xg = 2.0f;                       //设置x方向加速度为2.0
		m_Particles[i].yg = -0.8f;                      //设置y方向加速度为-0.8
		m_Particles[i].zg = 0.0f;                       //设置z方向加速度为0
	}
}

void Meteor::initMeteor() {
	glEnable(GL_TEXTURE_2D);                            //启用纹理映射
	glShadeModel(GL_SMOOTH);                            //启用阴影平滑
	glClearDepth(1.0);                                  //设置深度缓存
	glDisable(GL_DEPTH_TEST);                           //禁止深度测试
	glEnable(GL_BLEND);                                 //启用融合
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//设置融合因子
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //告诉系统对透视进行修正
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}

void Meteor::drawMeteor() {
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕和深度缓存
	glLoadIdentity();                                   //重置模型观察矩阵


	for (int i = 0; i < 1000; i++)                 //1000个粒子当一闪一闪的星星
	{
		if (m_Particles[i].active)                      //如果粒子为激活的
		{
			float x = m_Particles[i].x;                 //x轴位置
			float y = m_Particles[i].y;                 //y轴位置
			float z = m_Particles[i].z + m_Deep;        //z轴位置
			//设置粒子颜色
			glColor4f(m_Particles[i].r, m_Particles[i].g,
				m_Particles[i].b, m_Particles[i].life);
			glBegin(GL_TRIANGLE_STRIP);                 //绘制三角形带
			glTexCoord2d(1, 1);
			glVertex3f(x + 0.5f, y + 0.5f, z);
			glTexCoord2d(0, 1); glVertex3f(x - 0.5f, y + 0.5f, z);
			glTexCoord2d(1, 0); glVertex3f(x + 0.5f, y - 0.5f, z);
			glTexCoord2d(0, 0); glVertex3f(x - 0.5f, y - 0.5f, z);
			glEnd();

			//更新各方向坐标及速度
			m_Particles[i].x += m_Particles[i].xi / (m_Slowdown * 1000);
			m_Particles[i].y += m_Particles[i].yi / (m_Slowdown * 1000);
			m_Particles[i].z += m_Particles[i].zi / (m_Slowdown * 1000);
			m_Particles[i].xi += m_Particles[i].xg;
			m_Particles[i].yi += m_Particles[i].yg;
			m_Particles[i].zi += m_Particles[i].zg;

			m_Particles[i].life -= m_Particles[i].fade; //减少粒子的生命值
			
			if (m_Particles[i].life < 0.0f)             //如果粒子生命值小于0
			{
				m_Particles[i].life = 1.0f;             //产生一个新粒子
				m_Particles[i].fade = float(rand() % 100) / 1000.0f + 0.003f;

				m_Particles[i].r = 1.0f;  //设置颜色
				m_Particles[i].g = 1.0f;
				m_Particles[i].b = 1.0f;

				float row = rand() % screen_width + (rand() % 100) * 0.01;
				float col = rand() % screen_height + (rand() % 100) * 0.01;

				m_Particles[i].x = row;                //粒子随机出现
				m_Particles[i].y = col;
				m_Particles[i].z = 0.0f;

				//随机生成粒子速度
				m_Particles[i].xi = m_xSpeed + float((rand() % 60) - 32.0f);
				m_Particles[i].yi = m_ySpeed + float((rand() % 60) - 30.0f);
				m_Particles[i].zi = float((rand() % 60) - 30.0f);
			}
		}
	}
	if (m_Rainbow)                                      //如果为彩虹模式
	{
		m_Color++;                                      //进行颜色的变换
		if (m_Color > 11)
		{
			m_Color = 0;
		}
	}
}

void Meteor::meteor_run() {

	float speed_x = fabs(float((rand() % 50) - 26.0f) * 10.0f + 5);;
	float speed_y = -fabs(float((rand() % 50) - 25.0f) * 10.0f + 5);
	

	float pos_x = -10;	//在画外产生
	float pos_y = rand() % 50 + 50;		//随机的y坐标

	int num_meteor = MAX_PARTICLES * 2 / 3;
	for (int i = 0; i < MAX_PARTICLES; i++){
	

		if (i < num_meteor / 10) {
			m_Particles[i].x = pos_x;
			m_Particles[i].y = pos_y;
			m_Particles[i].z = 0;

			
		}
		else if (i < num_meteor / 10 * 2) {
			m_Particles[i].x = pos_x - 1;
			m_Particles[i].y = pos_y + 1;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
			m_Particles[i].z = 0.0f;



		}
		else if (i < num_meteor / 10 * 3) {
			m_Particles[i].x = pos_x ;
			m_Particles[i].y = pos_y + 2;
			m_Particles[i].z = 0.0f;



		}
		else if (i < num_meteor / 10 * 4) {
			m_Particles[i].x = pos_x - 2  ;
			m_Particles[i].y = pos_y ;
			m_Particles[i].z = 0.0f;


		}
		else if (i < num_meteor / 10 * 5) {
			m_Particles[i].x = pos_x - 2;
			m_Particles[i].y = pos_y + 2;
			m_Particles[i].z = 0.0f;


		}
		else if (i < num_meteor / 10 * 6) {
			m_Particles[i].x = pos_x - 3;
			m_Particles[i].y = pos_y + 3;
			m_Particles[i].z = 0.0f;

		}
		else if (i < num_meteor / 10 * 7) {
			m_Particles[i].x = pos_x - 4;
			m_Particles[i].y = pos_y + 4;
			m_Particles[i].z = 0.0f;


		}
		else if (i < num_meteor / 10 * 8) {
			m_Particles[i].x = pos_x - 5;
			m_Particles[i].y = pos_y + 5;
			m_Particles[i].z = 0.0f;


		}
		else if (i < num_meteor / 10 * 9) {
			m_Particles[i].x = pos_x - 1;
			m_Particles[i].y = pos_y + 3;
			m_Particles[i].z = 0.0f;

		}
		else if (i < num_meteor) {
			m_Particles[i].x = pos_x - rand()%5;
			m_Particles[i].y = pos_y + rand()%5;
			m_Particles[i].z = 0.0f;

		}
		else {
			float row = rand() % screen_width + (rand() % 100) * 0.01;
			float col = rand() % screen_height + (rand() % 100) * 0.01;

			m_Particles[i].x = row;                //粒子随机出现
			m_Particles[i].y = col;
			m_Particles[i].z = 0.0f;
		}

		m_Particles[i].xi = speed_x * 2 + fabs(rand() % 100 - 50);
		m_Particles[i].yi = speed_y * 2 + fabs(rand() % 100 - 50);
		m_Particles[i].zi = 0;

		m_Particles[i].xg = 35.0f;                       //设置x方向加速度为2.0
		m_Particles[i].yg = -30.5f;                      //设置y方向加速度为-0.8
		m_Particles[i].zg = 0.0f;

		m_Particles[i].r = 1.0f;  //设置颜色
		m_Particles[i].g = 1.0f;
		m_Particles[i].b = 1.0f;
		                   

	}
}


void Meteor::explode() {					//产生两处爆炸的效果

	float row1 = rand() % 100 + (rand() % 100) * 0.01;
	float col1 = rand() % 100 + (rand() % 100) * 0.01;

	float row2 = rand() % 100 + (rand() % 100) * 0.01;
	float col2 = rand() % 100 + (rand() % 100) * 0.01;

	int num_explode = 500;

	for (int i = 0; i < num_explode; i++)
	{
		m_Particles[i].fade = fabs(rand() % 50 - 25) * 0.01;

		if (i < num_explode / 2) {
			m_Particles[i].x = row1;
			m_Particles[i].y = col1;
			m_Particles[i].z = 0;
			
		}
		else {
			m_Particles[i].x = row2;
			m_Particles[i].y = col2;
			m_Particles[i].z = 0.0f;

		}


		//随机生成速度
		m_Particles[i].xi = float((rand() % 50) - 26.0f) * 10.0f;
		m_Particles[i].yi = float((rand() % 50) - 25.0f) * 10.0f;
		m_Particles[i].zi = float((rand() % 50) - 25.0f) * 10.0f;

		m_Particles[i].xg = 0.0f;                       //设置x方向加速度为2.0
		m_Particles[i].yg = -0.8f;                      //设置y方向加速度为-0.8
		m_Particles[i].zg = 0.0f;                       //设置z方向加速度为0

		//设置粒子的颜色

		m_Particles[i].r = 1.0f;
		m_Particles[i].g = 1.0f;
		m_Particles[i].b = 1.0f;

		
	}
}

void Meteor::change_rainbow() {
	m_Rainbow = !m_Rainbow;
}

void Meteor::change_color() {

		m_Rainbow = false;
		m_Color++;
		if (m_Color > 11)
		{
			m_Color = 0;
		}
}