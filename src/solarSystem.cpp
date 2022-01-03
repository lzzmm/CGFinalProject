#include "solarSystem.h"

SolarSystem::SolarSystem()
{
	// sun
	QVector3D a(0.0f, 0.0f, 0.0f);
	solarSystemBalls[0] = new Ball(0, 2.0f, a, 0.0f, 0.1f, 7.25f, a, a, a, 0.0f, 1.0f);
	solarSystemBalls[0]->textureBind(":/resource/textures/sun.jpg");

	// Mercury r = 2440km 0.38 87.70 58.653 0.01бу
	solarSystemBalls[1] = new Ball(1, 0.0244f, QVector3D(3.8f, 0.0f, 0.0f), 360.0f / 87.70f, 360.0f / 58.653f, 0.01f, a, a, a, 0.0f, 1.0f);
	solarSystemBalls[1]->textureBind(":/resource/textures/mercury.jpg");

	// Venus r = 6052km 0.72 224.701 243.02 2.64бу
	solarSystemBalls[2] = new Ball(2, 0.06052f, QVector3D(7.2f, 0.0f, 0.0f), 360.0f / 224.701f, 360.0f / 243.02f, 2.64f, a, a, a, 0.0f, 1.0f);
	solarSystemBalls[2]->textureBind(":/resource/textures/venus.jpg");

	// Earth r = 6378km 1.00 365.2422 0.9973 23.44бу
	solarSystemBalls[3] = new Ball(3, 0.06378f, QVector3D(100.00f, 0.0f, 0.0f), 360.0f / 365.2422f, 360.0f / 0.9973f, 23.44f, a, a, a, 0.0f, 1.0f);
	solarSystemBalls[3]->textureBind(":/resource/textures/earth.jpg");

	/*
	solarSystemBalls[4] = new Ball(2, 0.6052f, QVector3D(0.72f, 0.0f, 0.0f), 360.0f / 224.701f, 360.0f / 243.02f, 2.64f, a, a, a, 0.0f, 1.0f);

	solarSystemBalls[5] = new Ball(2, 0.6052f, QVector3D(0.72f, 0.0f, 0.0f), 360.0f / 224.701f, 360.0f / 243.02f, 2.64f, a, a, a, 0.0f, 1.0f);

	solarSystemBalls[6] = new Ball(2, 0.6052f, QVector3D(0.72f, 0.0f, 0.0f), 360.0f / 224.701f, 360.0f / 243.02f, 2.64f, a, a, a, 0.0f, 1.0f);

	solarSystemBalls[7] = new Ball(2, 0.6052f, QVector3D(0.72f, 0.0f, 0.0f), 360.0f / 224.701f, 360.0f / 243.02f, 2.64f, a, a, a, 0.0f, 1.0f);

	solarSystemBalls[8] = new Ball(2, 0.6052f, QVector3D(0.72f, 0.0f, 0.0f), 360.0f / 224.701f, 360.0f / 243.02f, 2.64f, a, a, a, 0.0f, 1.0f);
	*/

	
}

SolarSystem::~SolarSystem()
{
	for (int i = 0; i < 4; i++)delete solarSystemBalls[i];
}

void SolarSystem::draw(QOpenGLExtraFunctions* f, QMatrix4x4 view, QMatrix4x4 projection, QMatrix4x4 model, QOpenGLShaderProgram& shader)
{
	for(int i = 0;i<4;i++)
	{
		solarSystemBalls[i]->drawBall(f, view, projection, model, shader);
		solarSystemBalls[i]->rotate();
		solarSystemBalls[i]->revolute();
	}
}