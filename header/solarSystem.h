#ifndef __SOLARSYSTEM_H__
#define __SOLARSYSTEM_H__

#include "ball.h"

class SolarSystem {

public:
	SolarSystem();
	~SolarSystem();
	void initShader();
	void draw(QOpenGLExtraFunctions* f, QMatrix4x4 view, QMatrix4x4 projection, QMatrix4x4 model, QVector3D viewPos);
	GLfloat runSpeed;
	QOpenGLShaderProgram shaderProgram;
private:
	Ball* solarSystemBalls[10];
};



#endif // __SOLARSYSTEM_H__