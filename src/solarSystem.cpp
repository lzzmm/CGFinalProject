#include "solarSystem.h"

SolarSystem::SolarSystem()
	:runSpeed(1.0f)
{
	QVector3D a(0.0f, 0.0f, 0.0f);
	// sun r = 696000 各种比例都进行了一定的缩小
	solarSystemBalls[0] = new Ball(0, 26.96f, a, 0.0f, 0.1f, 7.25f, a, a, a, 0.0f, 1.0f);
	solarSystemBalls[0]->textureBind(":/resource/textures/sun.jpg");

	// Mercury r = 2440km 0.38 87.70 58.653 0.01
	solarSystemBalls[1] = new Ball(1, 0.244f, QVector3D(38.0f, 0.0f, 0.0f), 360.0f / 87.70f, 360.0f / 58.653f, 0.01f, a, a, a, 0.0f, 1.0f);
	solarSystemBalls[1]->textureBind(":/resource/textures/mercury.jpg");

	// Venus r = 6052km 0.72 224.701 -243.02 2.64
	solarSystemBalls[2] = new Ball(2, 0.6052f, QVector3D(72.0f, 0.0f, 0.0f), 360.0f / 224.701f, -360.0f / 243.02f, 2.64f, a, a, a, 0.0f, 1.0f);
	solarSystemBalls[2]->textureBind(":/resource/textures/venus.jpg");

	// Earth r = 6378km 1.00 365.2422 0.9973 23.44
	solarSystemBalls[3] = new Ball(3, 0.6378f, QVector3D(100.0f, 0.0f, 0.0f), 360.0f / 365.2422f, 360.0f / 0.9973f, 23.44f, a, a, a, 0.0f, 1.0f);
	solarSystemBalls[3]->textureBind(":/resource/textures/earth.jpg");

	// Moon r = 1737km 
	solarSystemBalls[9] = new Ball(9, 0.1737f, QVector3D(100.0f, 0.0f, 0.0f), 360.0f / 365.2422f, 360.0f / 27.35f, 23.44f, a, a, a, 0.0f, 1.0f);
	solarSystemBalls[9]->textureBind(":/resource/textures/moon.jpg");

	// Mars r = 3398km 1.52 686.98 1.026 25.19
	solarSystemBalls[4] = new Ball(4, 0.3398f, QVector3D(152.0f, 0.0f, 0.0f), 360.0f / 686.98f, 360.0f / 1.026f, 25.19f, a, a, a, 0.0f, 1.0f);
	solarSystemBalls[4]->textureBind(":/resource/textures/mars.jpg");

	// Jupiter r = 71492km 5.20 4332.59 0.42 3.12 // 缩短距离
	solarSystemBalls[5] = new Ball(5, 7.1492f, QVector3D(320.0f, 0.0f, 0.0f), 360.0f / 4332.59f, 360.0f / 0.42f, 3.12f, a, a, a, 0.0f, 1.0f);
	solarSystemBalls[5]->textureBind(":/resource/textures/jupiter.jpg");

	// Saturn r = 60268km 9.54 10759 0.45 26.73
	solarSystemBalls[6] = new Ball(6, 6.0268f, QVector3D(454.0f, 0.0f, 0.0f), 360.0f / 10759.0f, 360.0f / 0.45f, 26.73f, a, a, a, 0.0f, 1.0f);
	solarSystemBalls[6]->textureBind(":/resource/textures/saturn.jpg");

	// Uranus r = 25559km 19.218 30799.095 -0.719 82.23
	solarSystemBalls[7] = new Ball(7, 2.5559f, QVector3D(621.8f, 0.0f, 0.0f), 360.0f / 30799.095f, 360.0f / -0.719f, 82.23f, a, a, a, 0.0f, 1.0f);
	solarSystemBalls[7]->textureBind(":/resource/textures/uranus.jpg");

	// Neptune r = 24718km 30.06 60327.624 0.67 28.33 
	solarSystemBalls[8] = new Ball(8, 2.4718f, QVector3D(906.0f, 0.0f, 0.0f), 360.0f / 60327.624f, 360.0f / 0.67f, 28.33f, a, a, a, 0.0f, 1.0f);
	solarSystemBalls[8]->textureBind(":/resource/textures/neptune.jpg");


}

SolarSystem::~SolarSystem()
{
	for (int i = 0; i < 10; i++) delete solarSystemBalls[i];
}

void SolarSystem::draw(QOpenGLExtraFunctions* f, QMatrix4x4 view, QMatrix4x4 projection, QMatrix4x4 model, QOpenGLShaderProgram& shader)
{
	for (int i = 0; i < 10; i++)
	{
		//if (i == 9) 
		solarSystemBalls[i]->drawBall(f, view, projection, model, shader);
		solarSystemBalls[i]->rotate(runSpeed);
		solarSystemBalls[i]->revolute(runSpeed);
	}
}