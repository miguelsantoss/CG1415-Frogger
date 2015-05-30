#include "Frog.h"
#include <gl/glut.h>

Frog::Frog() {}

Frog::~Frog() {}

void Frog::draw() {
	Vector3 *vec = this->getPosition();
	glPushMatrix();
	glTranslatef(vec->getX(), vec->getY(), vec->getZ()+ 0.3);
	glScalef(0.1, 0.1, 0.1);
	rotate();
	//body
	glPushMatrix();
	glColor3f(0.15, 0.4, 0.15);
	GLfloat bodyamb[] = { 0.15f, 0.4f, 0.15f, 1.0f };
	GLfloat bodydiff[] = { 0.15f, 0.4f, 0.15f, 1.0f };
	GLfloat bodyspec[] = { 0.15f, 0.4f, 0.15f, 1.0f };
	GLfloat bodyshine = 76.8f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, bodyamb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, bodydiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, bodyspec);
	glMaterialf(GL_FRONT, GL_SHININESS, bodyshine);
	glTranslatef( 0.0, -1.0, 0.0);
	glScalef(3.5, 3.0, 2.5);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//head
	glPushMatrix();
	glTranslatef(0.0, 2.0, 0.0);
	glScalef(3.0, 2.0, 2.0);
	glColor3f(0.2, 0.5, 0.2);
	GLfloat headamb[] = { 0.2f, 0.5f, 0.2f, 1.0f };
	GLfloat headdiff[] = { 0.2f, 0.5f, 0.2f, 1.0f };
	GLfloat headspec[] = { 0.2f, 0.5f, 0.2f, 1.0f };
	GLfloat headshine = 76.8f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, headamb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, headdiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, headspec);
	glMaterialf(GL_FRONT, GL_SHININESS, headshine);
	glutSolidSphere(1.0, 8.0, 8.0);
	glPopMatrix();

	//eyeL
	glColor3f(1.0, 1.0, 1.0);
	GLfloat eyeamb[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat eyediff[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat eyespec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat eyeshine = 76.8f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, eyeamb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, eyediff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, eyespec);
	glMaterialf(GL_FRONT, GL_SHININESS, eyeshine);
	glPushMatrix();
	glTranslatef(-2.0, 3.0, 1.0);
	glutSolidSphere(0.9, 30.0, 30.0);
	glPushMatrix();
	glTranslatef(0.0, 0.1, 0.0);
	//glScalef(0.9, 0.9, 0.9);
	glutSolidSphere(0.5, 30.0, 30.0);
	glPopMatrix();
	glPopMatrix();

	//eyeR
	glPushMatrix();
	glTranslatef(2.0, 3.0, 1.0);
	glutSolidSphere(0.9, 30.0, 30.0);
	glPushMatrix();
	glTranslatef(0.0, 0.1, 0.0);
	//glScalef(0.9, 0.9, 0.9);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.5, 30.0, 30.0);
	glColor3f(0.2, 0.6, 0.2);
	glPopMatrix();
	glPopMatrix();


	//back leg L
	glColor3f(0.2, 0.6, 0.2);
	GLfloat legsamb[] = { 0.2f, 0.6f, 0.2f, 1.0f };
	GLfloat legsdiff[] = { 0.2f, 0.6f, 0.2f, 1.0f };
	GLfloat legsspec[] = { 0.2f, 0.6f, 0.2f, 1.0f };
	GLfloat legsshine = 76.8f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, legsamb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, legsdiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, legsspec);
	glMaterialf(GL_FRONT, GL_SHININESS, legsshine);
	glPushMatrix();
	glTranslatef(-3.0, -1.0, 1.0);
	glScalef(1.0, 3.0, 1.0);
	glutSolidCube(1);

	glPopMatrix();


	glPushMatrix();
	glTranslatef(-3.0, -1.0, 0.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);///
	glScalef(1.0, 3.0, 1.0);
	glutSolidCube(1);

	glPopMatrix();


	glPushMatrix();
	glTranslatef(-3.0, -1.0, -1.0);
	glScalef(1.0, 3.0, 1.0);
	glutSolidCube(1);

	glPopMatrix();


	//back leg R
	glPushMatrix();
	glTranslatef(3.0, -1.0, 1.0);
	glScalef(1.0, 3.0, 1.0);
	glutSolidCube(1);

	glPopMatrix();


	glPushMatrix();
	glTranslatef(3.0, -1.0, 0.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	glScalef(1.0, 3.0, 1.0);
	glutSolidCube(1);
	
	glPopMatrix();


	glPushMatrix();
	glTranslatef(3.0, -1.0, -1.0);
	glScalef(1.0, 3.0, 1.0);
	glutSolidCube(1);
	
	glPopMatrix();



	//front leg L
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);

	//glutSolidCube(1);
	glPopMatrix();



	//front leg R
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);

	//glutSolidCube(1);
	glPopMatrix();


	//
	glPopMatrix();

}

Vector3* Frog::getDirection() {
	return _direction;
}

void Frog::setDirection(Vector3* direction) {
	_direction = direction;
}

void Frog::setDirection(double x, double y, double z) {
	_direction = new Vector3(x, y, z);
}

void Frog::rotate() {
	if (_direction->getY() == -1.0){
		glRotatef(180, 0.0, 0.0, 1.0);
	}
	else if (_direction->getX() == -1.0){
		glRotatef(90, 0.0, 0.0, 1.0);
	}
	else if (_direction->getX() == 1.0){
		glRotatef(-90, 0.0, 0.0, 1.0);
	}
}