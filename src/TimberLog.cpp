#include "TimberLog.h"
#include <gl/glut.h>

TimberLog::TimberLog() {}

TimberLog::TimberLog(double x, double y, double z, Vector3 speed, int direction, int timer) {
	this->setPosition(x, y, z);
	this->setDirection(direction);
	this->setSpeed(speed);
	this->setDirection(direction);
	this->setTimer(timer);
	this->setToDraw(false);
}

TimberLog::~TimberLog() {}

void TimberLog::draw() {
	glPushMatrix();
	Vector3 *vec = this->getPosition();
	glColor3f(0.827451, 0.521569, 0.26470);
	GLfloat logamb[] = { 0.3f, 0.15f, 0.0f, 1.0f };
	GLfloat logdiff[] = { 0.29f, 0.16f, 0.0f, 1.0f };
	GLfloat logspec[] = { 0.39f, 0.18f, 0.0f, 1.0f };
	GLfloat logshine = 128;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, logamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, logdiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, logspec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, logshine);
	glTranslatef(vec->getX(), vec->getY(), vec->getZ()+0.001);
	glScalef(2.5, 0.9, 0.0);
	glutSolidCube(1);
	glPopMatrix();
}