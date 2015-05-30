#include "Car.h"
#include <gl/glut.h>

Car::Car() {
}

Car::Car(double x, double y, double z, Vector3 speed, int direction, int timer) {
	this->setPosition(x, y, z);
	this->setDirection(direction);
	this->setSpeed(speed);
	this->setDirection(direction);
	this->setTimer(timer);
	this->setToDraw(false);
}

Car::~Car() {}

void Car::draw() {
	glPushMatrix();
	glColor3f(0.0, 0.541, 0.388);
	GLfloat caramb[] = { 0.0f, 0.54f, 0.39f, 1.0f };
	GLfloat cardiff[] = { 0.0f, 0.54f, 0.37f, 1.0f };
	GLfloat carspec[] = { 0.0f, 0.54f, 0.38f, 1.0f };
	GLfloat carshine = 20;
	glMaterialfv(GL_FRONT, GL_AMBIENT, caramb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cardiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, carspec);
	glMaterialf(GL_FRONT, GL_SHININESS, carshine);
	this->drawBox();
	this->drawRoof();
	glColor3f(0.0, 0.0, 0.0);
	GLfloat tiresamb[] = { 0.12f, 0.11f, 0.12f, 1.0f };
	GLfloat tiresdiff[] = { 0.45f, 0.44f, 0.47f, 1.0f };
	GLfloat tiresspec[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat tiresshine = 128;
	glMaterialfv(GL_FRONT, GL_AMBIENT, tiresamb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, tiresdiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, tiresspec);
	glMaterialf(GL_FRONT, GL_SHININESS, tiresshine);
	this->drawWheels();
	glPopMatrix();
}

void Car::drawBox() {
	this->drawBoxHorizontal();
	this->drawBoxVerticalX();
	this->drawBoxVerticalY();
}

void Car::drawBoxHorizontal() {
	Vector3 *vec = this->getPosition();
	for (double y = vec->getY() - 0.4; y < vec->getY() + 0.4; y += 0.1) {
		for (double x = vec->getX() - 0.8; x < vec->getX() + 0.8; x += 0.1) {
			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(x, y, vec->getZ() + 0.5);
			glVertex3f(x + 0.1, y, vec->getZ() + 0.5);
			glVertex3f(x + 0.1, y + 0.1, vec->getZ() + 0.5);
			glVertex3f(x, y + 0.1, vec->getZ() + 0.5);
			glEnd();
		}
	}
	for (double y = vec->getY() - 0.4; y < vec->getY() + 0.4; y += 0.1) {
		for (double x = vec->getX() - 0.8; x < vec->getX() + 0.8; x += 0.1) {
			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(x, y, vec->getZ() + 0.1);
			glVertex3f(x + 0.1, y, vec->getZ() + 0.1);
			glVertex3f(x + 0.1, y + 0.1, vec->getZ() + 0.1);
			glVertex3f(x, y + 0.1, vec->getZ() + 0.1);
			glEnd();
		}
	}
}

void Car::drawBoxVerticalX() {
	Vector3 *vec = this->getPosition();
	for (double y = vec->getY() - 0.4; y < vec->getY() + 0.4; y += 0.1) {
		for (double z = vec->getZ() + 0.1; z < vec->getZ() + 0.5; z += 0.1) {
			glBegin(GL_QUADS);
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(vec->getX() - 0.8, y, z);
			glVertex3f(vec->getX() - 0.8, y + 0.1, z);
			glVertex3f(vec->getX() - 0.8, y + 0.1, z + 0.1);
			glVertex3f(vec->getX() - 0.8, y, z + 0.1);
			glEnd();
		}
	}
	for (double y = vec->getY() - 0.4; y < vec->getY() + 0.4; y += 0.1) {
		for (double z = vec->getZ() + 0.1; z < vec->getZ() + 0.5; z += 0.1) {
			glBegin(GL_QUADS);
			glNormal3f(1.0, 0.0, 0.0);
			glVertex3f(vec->getX() + 0.8, y, z);
			glVertex3f(vec->getX() + 0.8, y + 0.1, z);
			glVertex3f(vec->getX() + 0.8, y + 0.1, z + 0.1);
			glVertex3f(vec->getX() + 0.8, y, z + 0.1);
			glEnd();
		}
	}
}

void Car::drawBoxVerticalY() {
	Vector3 *vec = this->getPosition();
	for (double x = vec->getX() - 0.8; x < vec->getX() + 0.8; x += 0.1) {
		for (double z = vec->getZ() + 0.1; z < vec->getZ() + 0.5; z += 0.1) {
			glBegin(GL_QUADS);
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(x, vec->getY() + 0.4, z);
			glVertex3f(x + 0.1, vec->getY() + 0.4, z);
			glVertex3f(x + 0.1, vec->getY() + 0.4, z + 0.1);
			glVertex3f(x, vec->getY() + 0.4, z + 0.1);
			glEnd();
		}
	}
	for (double x = vec->getX() - 0.8; x < vec->getX() + 0.8; x += 0.1) {
		for (double z = vec->getZ() + 0.1; z < vec->getZ() + 0.5; z += 0.1) {
			glBegin(GL_QUADS);
			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(x, vec->getY() - 0.4, z);
			glVertex3f(x + 0.1, vec->getY() - 0.4, z);
			glVertex3f(x + 0.1, vec->getY() - 0.4, z + 0.1);
			glVertex3f(x, vec->getY() - 0.4, z + 0.1);
			glEnd();
		}
	}
}

void Car::drawRoof() {
	this->drawRoofHorizontal();
	glColor3f(0.658, 0.929, 0.854);
	GLfloat windowsamb[] = { 0.65f, 0.93f, 0.85f, 1.0f };
	GLfloat windowdiff[] = { 0.65f, 0.93f, 0.85f, 1.0f };
	GLfloat windowspec[] = { 0.65f, 0.93f, 0.85f, 1.0f };
	GLfloat windowshine = 128;
	glMaterialfv(GL_FRONT, GL_AMBIENT, windowsamb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, windowdiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, windowspec);
	glMaterialf(GL_FRONT, GL_SHININESS, windowshine);
	this->drawRoofDiagonalFront();
	this->drawRoofDiagonalBack();
	this->drawRoofVerticalY();
}

void Car::drawRoofHorizontal() {
	Vector3 *vec = this->getPosition();
	for (double y = vec->getY() - 0.4; y < vec->getY() + 0.4; y += 0.1) {
		for (double x = vec->getX() - 0.3; x < vec->getX() + 0.3; x += 0.1) {
			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(x, y, vec->getZ() + 0.8);
			glVertex3f(x + 0.1, y, vec->getZ() + 0.8);
			glVertex3f(x + 0.1, y + 0.1, vec->getZ() + 0.8);
			glVertex3f(x, y + 0.1, vec->getZ() + 0.8);
			glEnd();
		}
	}
	for (double y = vec->getY() - 0.4; y < vec->getY() + 0.4; y += 0.1) {
		for (double x = vec->getX() - 0.5; x < vec->getX() + 0.5; x += 0.1) {
			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(x, y, vec->getZ() + 0.5);
			glVertex3f(x + 0.1, y, vec->getZ() + 0.5);
			glVertex3f(x + 0.1, y + 0.1, vec->getZ() + 0.5);
			glVertex3f(x, y + 0.1, vec->getZ() + 0.5);
			glEnd();
		}
	}
}

void Car::drawRoofDiagonalFront() {
	Vector3 *vec = this->getPosition();
	Vector3 normal;
	normal = normalVector(vec->getX() - 0.5, vec->getY() - 0.4, vec->getZ() + 0.5, vec->getX() - 0.3, vec->getY() - 0.4, vec->getZ() + 0.8, vec->getX() - 0.3, vec->getY() + 0.4, vec->getZ() + 0.8);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.5, vec->getY() - 0.4, vec->getZ() + 0.5);
	glVertex3f(vec->getX() - 0.3, vec->getY() - 0.4, vec->getZ() + 0.8);
	glVertex3f(vec->getX() - 0.3, vec->getY() + 0.4, vec->getZ() + 0.8);
	glVertex3f(vec->getX() - 0.5, vec->getY() + 0.4, vec->getZ() + 0.5);
	glEnd();
}

void Car::drawRoofDiagonalBack() {
	Vector3 *vec = this->getPosition();
	Vector3 normal;
	normal = normalVector(vec->getX() + 0.3, vec->getY() - 0.4, vec->getZ() + 0.8, vec->getX() + 0.5, vec->getY() - 0.4, vec->getZ() + 0.5, vec->getX() + 0.5, vec->getY() + 0.4, vec->getZ() + 0.5);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.3, vec->getY() - 0.4, vec->getZ() + 0.8);
	glVertex3f(vec->getX() + 0.5, vec->getY() - 0.4, vec->getZ() + 0.5);
	glVertex3f(vec->getX() + 0.5, vec->getY() + 0.4, vec->getZ() + 0.5);
	glVertex3f(vec->getX() + 0.3, vec->getY() + 0.4, vec->getZ() + 0.8);
	glEnd();
}

void Car::drawRoofVerticalY() {
	Vector3 *vec = this->getPosition();
	//Janelas da frente
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(vec->getX() - 0.5, vec->getY() - 0.4, vec->getZ() + 0.5);
	glVertex3f(vec->getX() - 0.3, vec->getY() - 0.4, vec->getZ() + 0.5);
	glVertex3f(vec->getX() - 0.3, vec->getY() - 0.4, vec->getZ() + 0.8);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(vec->getX() - 0.5, vec->getY() + 0.4, vec->getZ() + 0.5);
	glVertex3f(vec->getX() - 0.3, vec->getY() + 0.4, vec->getZ() + 0.5);
	glVertex3f(vec->getX() - 0.3, vec->getY() + 0.4, vec->getZ() + 0.8);
	glEnd();

	//Janelas de tras
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(vec->getX() + 0.3, vec->getY() - 0.4, vec->getZ() + 0.8);
	glVertex3f(vec->getX() + 0.3, vec->getY() - 0.4, vec->getZ() + 0.5);
	glVertex3f(vec->getX() + 0.5, vec->getY() - 0.4, vec->getZ() + 0.5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(vec->getX() + 0.3, vec->getY() + 0.4, vec->getZ() + 0.8);
	glVertex3f(vec->getX() + 0.3, vec->getY() + 0.4, vec->getZ() + 0.5);
	glVertex3f(vec->getX() + 0.5, vec->getY() + 0.4, vec->getZ() + 0.5);
	glEnd();

	for (double x = vec->getX() - 0.3; x < vec->getX() + 0.3; x += 0.1) {
		for (double z = vec->getZ() + 0.5; z < vec->getZ() + 0.75; z += 0.1) {
			glBegin(GL_QUADS);
			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(x, vec->getY() - 0.4, z);
			glVertex3f(x + 0.1, vec->getY() - 0.4, z);
			glVertex3f(x + 0.1, vec->getY() - 0.4, z + 0.1);
			glVertex3f(x, vec->getY() - 0.4, z + 0.1);
			glEnd();
		}
	}

	for (double x = vec->getX() - 0.3; x < vec->getX() + 0.3; x += 0.1) {
		for (double z = vec->getZ() + 0.5; z < vec->getZ() + 0.75; z += 0.1) {
			glBegin(GL_QUADS);
			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(x, vec->getY() + 0.4, z);
			glVertex3f(x + 0.1, vec->getY() + 0.4, z);
			glVertex3f(x + 0.1, vec->getY() + 0.4, z + 0.1);
			glVertex3f(x, vec->getY() + 0.4, z + 0.1);
			glEnd();
		}
	}
}

void Car::drawWheels() {
	this->drawWheelFrontLeft();
	this->drawWheelFrontRight();
	this->drawWheelRearLeft();
	this->drawWheelRearRight();
}

void Car::drawWheelFrontLeft() {
	Vector3 *vec = this->getPosition();
	Vector3 normal;
	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(vec->getX() - 0.5, vec->getY() - 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.45, vec->getY() - 0.5, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.35, vec->getY() - 0.5, vec->getZ() + 0.3);
	glVertex3f(vec->getX() - 0.25, vec->getY() - 0.5, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.2, vec->getY() - 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.25, vec->getY() - 0.5, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.35, vec->getY() - 0.5, vec->getZ());
	glVertex3f(vec->getX() - 0.45, vec->getY() - 0.5, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.5, vec->getY() - 0.5, vec->getZ() + 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(vec->getX() - 0.5, vec->getY() - 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.45, vec->getY() - 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.35, vec->getY() - 0.4, vec->getZ() + 0.3);
	glVertex3f(vec->getX() - 0.25, vec->getY() - 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.2, vec->getY() - 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.25, vec->getY() - 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.35, vec->getY() - 0.4, vec->getZ());
	glVertex3f(vec->getX() - 0.45, vec->getY() - 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.5, vec->getY() - 0.4, vec->getZ() + 0.15);
	glEnd();

	normal = this->normalVector(vec->getX() - 0.5, vec->getY() - 0.5, vec->getZ() + 0.15, vec->getX() - 0.5, vec->getY() - 0.4, vec->getZ() + 0.15, vec->getX() - 0.45, vec->getY() - 0.4, vec->getZ() + 0.25);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.5, vec->getY() - 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.5, vec->getY() - 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.45, vec->getY() - 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.45, vec->getY() - 0.5, vec->getZ() + 0.25);
	glEnd();

	normal = this->normalVector(vec->getX() - 0.45, vec->getY() - 0.5, vec->getZ() + 0.25, vec->getX() - 0.45, vec->getY() - 0.4, vec->getZ() + 0.25, vec->getX() - 0.35, vec->getY() - 0.4, vec->getZ() + 0.3);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.45, vec->getY() - 0.5, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.45, vec->getY() - 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.35, vec->getY() - 0.4, vec->getZ() + 0.3);
	glVertex3f(vec->getX() - 0.35, vec->getY() - 0.5, vec->getZ() + 0.3);
	glEnd();

	normal = this->normalVector(vec->getX() - 0.35, vec->getY() - 0.5, vec->getZ() + 0.3, vec->getX() - 0.35, vec->getY() - 0.4, vec->getZ() + 0.3, vec->getX() - 0.25, vec->getY() - 0.4, vec->getZ() + 0.25);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.35, vec->getY() - 0.5, vec->getZ() + 0.3);
	glVertex3f(vec->getX() - 0.35, vec->getY() - 0.4, vec->getZ() + 0.3);
	glVertex3f(vec->getX() - 0.25, vec->getY() - 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.25, vec->getY() - 0.5, vec->getZ() + 0.25);
	glEnd();

	normal = this->normalVector(vec->getX() - 0.25, vec->getY() - 0.5, vec->getZ() + 0.25, vec->getX() - 0.25, vec->getY() - 0.4, vec->getZ() + 0.25, vec->getX() - 0.2, vec->getY() - 0.4, vec->getZ() + 0.15);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.25, vec->getY() - 0.5, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.25, vec->getY() - 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.2, vec->getY() - 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.2, vec->getY() - 0.5, vec->getZ() + 0.15);
	glEnd();

	normal = this->normalVector(vec->getX() - 0.2, vec->getY() - 0.5, vec->getZ() + 0.15, vec->getX() - 0.2, vec->getY() - 0.4, vec->getZ() + 0.15, vec->getX() - 0.25, vec->getY() - 0.5, vec->getZ() + 0.05);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.2, vec->getY() - 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.2, vec->getY() - 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.25, vec->getY() - 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.25, vec->getY() - 0.5, vec->getZ() + 0.05);
	glEnd();

	normal = this->normalVector(vec->getX() - 0.2, vec->getY() - 0.5, vec->getZ() + 0.15, vec->getX() - 0.2, vec->getY() - 0.4, vec->getZ() + 0.15, vec->getX() - 0.25, vec->getY() - 0.5, vec->getZ() + 0.05);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.2, vec->getY() - 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.2, vec->getY() - 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.25, vec->getY() - 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.25, vec->getY() - 0.5, vec->getZ() + 0.05);
	glEnd();

	normal = this->normalVector(vec->getX() - 0.25, vec->getY() - 0.5, vec->getZ() + 0.05, vec->getX() - 0.25, vec->getY() - 0.4, vec->getZ() + 0.05, vec->getX() - 0.35, vec->getY() - 0.4, vec->getZ());
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.25, vec->getY() - 0.5, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.25, vec->getY() - 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.35, vec->getY() - 0.4, vec->getZ());
	glVertex3f(vec->getX() - 0.35, vec->getY() - 0.5, vec->getZ());
	glEnd();

	normal = this->normalVector(vec->getX() - 0.35, vec->getY() - 0.5, vec->getZ(), vec->getX() - 0.35, vec->getY() - 0.4, vec->getZ(), vec->getX() - 0.45, vec->getY() - 0.4, vec->getZ() + 0.05);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.35, vec->getY() - 0.5, vec->getZ());
	glVertex3f(vec->getX() - 0.35, vec->getY() - 0.4, vec->getZ());
	glVertex3f(vec->getX() - 0.45, vec->getY() - 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.45, vec->getY() - 0.5, vec->getZ() + 0.05);
	glEnd();

	normal = this->normalVector(vec->getX() - 0.45, vec->getY() - 0.5, vec->getZ() + 0.05, vec->getX() - 0.45, vec->getY() - 0.4, vec->getZ() + 0.05, vec->getX() - 0.5, vec->getY() - 0.4, vec->getZ() + 0.15);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.45, vec->getY() - 0.5, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.45, vec->getY() - 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.5, vec->getY() - 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.5, vec->getY() - 0.5, vec->getZ() + 0.15);
	glEnd();
}

void Car::drawWheelFrontRight() {
	Vector3 *vec = this->getPosition();
	Vector3 normal;
	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(vec->getX() - 0.5, vec->getY() + 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.45, vec->getY() + 0.5, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.35, vec->getY() + 0.5, vec->getZ() + 0.3);
	glVertex3f(vec->getX() - 0.25, vec->getY() + 0.5, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.2, vec->getY() + 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.25, vec->getY() + 0.5, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.35, vec->getY() + 0.5, vec->getZ());
	glVertex3f(vec->getX() - 0.45, vec->getY() + 0.5, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.5, vec->getY() + 0.5, vec->getZ() + 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(vec->getX() - 0.5, vec->getY() + 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.45, vec->getY() + 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.35, vec->getY() + 0.4, vec->getZ() + 0.3);
	glVertex3f(vec->getX() - 0.25, vec->getY() + 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.2, vec->getY() + 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.25, vec->getY() + 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.35, vec->getY() + 0.4, vec->getZ());
	glVertex3f(vec->getX() - 0.45, vec->getY() + 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.5, vec->getY() + 0.4, vec->getZ() + 0.15);
	glEnd();

	normal = this->normalVector(vec->getX() - 0.5, vec->getY() + 0.5, vec->getZ() + 0.15, vec->getX() - 0.5, vec->getY() + 0.4, vec->getZ() + 0.15, vec->getX() - 0.45, vec->getY() + 0.4, vec->getZ() + 0.25);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.5, vec->getY() + 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.5, vec->getY() + 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.45, vec->getY() + 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.45, vec->getY() + 0.5, vec->getZ() + 0.25);
	glEnd();

	normal = this->normalVector(vec->getX() - 0.45, vec->getY() + 0.5, vec->getZ() + 0.25, vec->getX() - 0.45, vec->getY() + 0.4, vec->getZ() + 0.25, vec->getX() - 0.35, vec->getY() + 0.4, vec->getZ() + 0.3);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.45, vec->getY() + 0.5, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.45, vec->getY() + 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.35, vec->getY() + 0.4, vec->getZ() + 0.3);
	glVertex3f(vec->getX() - 0.35, vec->getY() + 0.5, vec->getZ() + 0.3);
	glEnd();

	normal = this->normalVector(vec->getX() - 0.35, vec->getY() + 0.5, vec->getZ() + 0.3, vec->getX() - 0.35, vec->getY() + 0.4, vec->getZ() + 0.3, vec->getX() - 0.25, vec->getY() + 0.4, vec->getZ() + 0.25);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.35, vec->getY() + 0.5, vec->getZ() + 0.3);
	glVertex3f(vec->getX() - 0.35, vec->getY() + 0.4, vec->getZ() + 0.3);
	glVertex3f(vec->getX() - 0.25, vec->getY() + 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.25, vec->getY() + 0.5, vec->getZ() + 0.25);
	glEnd();

	normal = this->normalVector(vec->getX() - 0.25, vec->getY() + 0.5, vec->getZ() + 0.25, vec->getX() - 0.25, vec->getY() + 0.4, vec->getZ() + 0.25, vec->getX() - 0.2, vec->getY() + 0.4, vec->getZ() + 0.15);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.25, vec->getY() + 0.5, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.25, vec->getY() + 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() - 0.2, vec->getY() + 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.2, vec->getY() + 0.5, vec->getZ() + 0.15);
	glEnd();

	normal = this->normalVector(vec->getX() - 0.2, vec->getY() + 0.5, vec->getZ() + 0.15, vec->getX() - 0.2, vec->getY() + 0.4, vec->getZ() + 0.15, vec->getX() - 0.25, vec->getY() + 0.5, vec->getZ() + 0.05);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.2, vec->getY() + 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.2, vec->getY() + 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.25, vec->getY() + 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.25, vec->getY() + 0.5, vec->getZ() + 0.05);
	glEnd();

	normal = this->normalVector(vec->getX() - 0.2, vec->getY() + 0.5, vec->getZ() + 0.15, vec->getX() - 0.2, vec->getY() + 0.4, vec->getZ() + 0.15, vec->getX() - 0.25, vec->getY() + 0.5, vec->getZ() + 0.05);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.2, vec->getY() + 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.2, vec->getY() + 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.25, vec->getY() + 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.25, vec->getY() + 0.5, vec->getZ() + 0.05);
	glEnd();

	normal = this->normalVector(vec->getX() - 0.25, vec->getY() + 0.5, vec->getZ() + 0.05, vec->getX() - 0.25, vec->getY() + 0.4, vec->getZ() + 0.05, vec->getX() - 0.35, vec->getY() + 0.4, vec->getZ());
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.25, vec->getY() + 0.5, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.25, vec->getY() + 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.35, vec->getY() + 0.4, vec->getZ());
	glVertex3f(vec->getX() - 0.35, vec->getY() + 0.5, vec->getZ());
	glEnd();

	normal = this->normalVector(vec->getX() - 0.35, vec->getY() + 0.5, vec->getZ(), vec->getX() - 0.35, vec->getY() + 0.4, vec->getZ(), vec->getX() - 0.45, vec->getY() + 0.4, vec->getZ() + 0.05);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.35, vec->getY() + 0.5, vec->getZ());
	glVertex3f(vec->getX() - 0.35, vec->getY() + 0.4, vec->getZ());
	glVertex3f(vec->getX() - 0.45, vec->getY() + 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.45, vec->getY() + 0.5, vec->getZ() + 0.05);
	glEnd();

	normal = this->normalVector(vec->getX() - 0.45, vec->getY() + 0.5, vec->getZ() + 0.05, vec->getX() - 0.45, vec->getY() + 0.4, vec->getZ() + 0.05, vec->getX() - 0.5, vec->getY() + 0.4, vec->getZ() + 0.15);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() - 0.45, vec->getY() + 0.5, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.45, vec->getY() + 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() - 0.5, vec->getY() + 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() - 0.5, vec->getY() + 0.5, vec->getZ() + 0.15);
	glEnd();
}

void Car::drawWheelRearLeft() {
	Vector3 *vec = this->getPosition();
	Vector3 normal;
	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(vec->getX() + 0.5, vec->getY() - 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.45, vec->getY() - 0.5, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.35, vec->getY() - 0.5, vec->getZ() + 0.3);
	glVertex3f(vec->getX() + 0.25, vec->getY() - 0.5, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.2, vec->getY() - 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.25, vec->getY() - 0.5, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.35, vec->getY() - 0.5, vec->getZ());
	glVertex3f(vec->getX() + 0.45, vec->getY() - 0.5, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.5, vec->getY() - 0.5, vec->getZ() + 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(vec->getX() + 0.5, vec->getY() - 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.45, vec->getY() - 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.35, vec->getY() - 0.4, vec->getZ() + 0.3);
	glVertex3f(vec->getX() + 0.25, vec->getY() - 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.2, vec->getY() - 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.25, vec->getY() - 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.35, vec->getY() - 0.4, vec->getZ());
	glVertex3f(vec->getX() + 0.45, vec->getY() - 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.5, vec->getY() - 0.4, vec->getZ() + 0.15);
	glEnd();

	normal = this->normalVector(vec->getX() + 0.5, vec->getY() - 0.5, vec->getZ() + 0.15, vec->getX() + 0.5, vec->getY() - 0.4, vec->getZ() + 0.15, vec->getX() + 0.45, vec->getY() - 0.4, vec->getZ() + 0.25);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.5, vec->getY() - 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.5, vec->getY() - 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.45, vec->getY() - 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.45, vec->getY() - 0.5, vec->getZ() + 0.25);
	glEnd();

	normal = this->normalVector(vec->getX() + 0.45, vec->getY() - 0.5, vec->getZ() + 0.25, vec->getX() + 0.45, vec->getY() - 0.4, vec->getZ() + 0.25, vec->getX() + 0.35, vec->getY() - 0.4, vec->getZ() + 0.3);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.45, vec->getY() - 0.5, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.45, vec->getY() - 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.35, vec->getY() - 0.4, vec->getZ() + 0.3);
	glVertex3f(vec->getX() + 0.35, vec->getY() - 0.5, vec->getZ() + 0.3);
	glEnd();

	normal = this->normalVector(vec->getX() + 0.35, vec->getY() - 0.5, vec->getZ() + 0.3, vec->getX() + 0.35, vec->getY() - 0.4, vec->getZ() + 0.3, vec->getX() + 0.25, vec->getY() - 0.4, vec->getZ() + 0.25);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.35, vec->getY() - 0.5, vec->getZ() + 0.3);
	glVertex3f(vec->getX() + 0.35, vec->getY() - 0.4, vec->getZ() + 0.3);
	glVertex3f(vec->getX() + 0.25, vec->getY() - 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.25, vec->getY() - 0.5, vec->getZ() + 0.25);
	glEnd();

	normal = this->normalVector(vec->getX() + 0.25, vec->getY() - 0.5, vec->getZ() + 0.25, vec->getX() + 0.25, vec->getY() - 0.4, vec->getZ() + 0.25, vec->getX() + 0.2, vec->getY() - 0.4, vec->getZ() + 0.15);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.25, vec->getY() - 0.5, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.25, vec->getY() - 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.2, vec->getY() - 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.2, vec->getY() - 0.5, vec->getZ() + 0.15);
	glEnd();

	normal = this->normalVector(vec->getX() + 0.2, vec->getY() - 0.5, vec->getZ() + 0.15, vec->getX() + 0.2, vec->getY() - 0.4, vec->getZ() + 0.15, vec->getX() + 0.25, vec->getY() - 0.5, vec->getZ() + 0.05);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.2, vec->getY() - 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.2, vec->getY() - 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.25, vec->getY() - 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.25, vec->getY() - 0.5, vec->getZ() + 0.05);
	glEnd();

	normal = this->normalVector(vec->getX() + 0.2, vec->getY() - 0.5, vec->getZ() + 0.15, vec->getX() + 0.2, vec->getY() - 0.4, vec->getZ() + 0.15, vec->getX() + 0.25, vec->getY() - 0.5, vec->getZ() + 0.05);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.2, vec->getY() - 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.2, vec->getY() - 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.25, vec->getY() - 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.25, vec->getY() - 0.5, vec->getZ() + 0.05);
	glEnd();

	normal = this->normalVector(vec->getX() + 0.25, vec->getY() - 0.5, vec->getZ() + 0.05, vec->getX() + 0.25, vec->getY() - 0.4, vec->getZ() + 0.05, vec->getX() + 0.35, vec->getY() - 0.4, vec->getZ());
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.25, vec->getY() - 0.5, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.25, vec->getY() - 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.35, vec->getY() - 0.4, vec->getZ());
	glVertex3f(vec->getX() + 0.35, vec->getY() - 0.5, vec->getZ());
	glEnd();

	normal = this->normalVector(vec->getX() + 0.35, vec->getY() - 0.5, vec->getZ(), vec->getX() + 0.35, vec->getY() - 0.4, vec->getZ(), vec->getX() + 0.45, vec->getY() - 0.4, vec->getZ() + 0.05);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.35, vec->getY() - 0.5, vec->getZ());
	glVertex3f(vec->getX() + 0.35, vec->getY() - 0.4, vec->getZ());
	glVertex3f(vec->getX() + 0.45, vec->getY() - 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.45, vec->getY() - 0.5, vec->getZ() + 0.05);
	glEnd();

	normal = this->normalVector(vec->getX() + 0.45, vec->getY() - 0.5, vec->getZ() + 0.05, vec->getX() + 0.45, vec->getY() - 0.4, vec->getZ() + 0.05, vec->getX() + 0.5, vec->getY() - 0.4, vec->getZ() + 0.15);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.45, vec->getY() - 0.5, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.45, vec->getY() - 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.5, vec->getY() - 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.5, vec->getY() - 0.5, vec->getZ() + 0.15);
	glEnd();
}

void Car::drawWheelRearRight() {
	Vector3 *vec = this->getPosition();
	Vector3 normal;
	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(vec->getX() + 0.5, vec->getY() + 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.45, vec->getY() + 0.5, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.35, vec->getY() + 0.5, vec->getZ() + 0.3);
	glVertex3f(vec->getX() + 0.25, vec->getY() + 0.5, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.2, vec->getY() + 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.25, vec->getY() + 0.5, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.35, vec->getY() + 0.5, vec->getZ());
	glVertex3f(vec->getX() + 0.45, vec->getY() + 0.5, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.5, vec->getY() + 0.5, vec->getZ() + 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(vec->getX() + 0.5, vec->getY() + 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.45, vec->getY() + 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.35, vec->getY() + 0.4, vec->getZ() + 0.3);
	glVertex3f(vec->getX() + 0.25, vec->getY() + 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.2, vec->getY() + 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.25, vec->getY() + 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.35, vec->getY() + 0.4, vec->getZ());
	glVertex3f(vec->getX() + 0.45, vec->getY() + 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.5, vec->getY() + 0.4, vec->getZ() + 0.15);
	glEnd();

	normal = this->normalVector(vec->getX() + 0.5, vec->getY() + 0.5, vec->getZ() + 0.15, vec->getX() + 0.5, vec->getY() + 0.4, vec->getZ() + 0.15, vec->getX() + 0.45, vec->getY() + 0.4, vec->getZ() + 0.25);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.5, vec->getY() + 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.5, vec->getY() + 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.45, vec->getY() + 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.45, vec->getY() + 0.5, vec->getZ() + 0.25);
	glEnd();

	normal = this->normalVector(vec->getX() + 0.45, vec->getY() + 0.5, vec->getZ() + 0.25, vec->getX() + 0.45, vec->getY() + 0.4, vec->getZ() + 0.25, vec->getX() + 0.35, vec->getY() + 0.4, vec->getZ() + 0.3);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.45, vec->getY() + 0.5, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.45, vec->getY() + 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.35, vec->getY() + 0.4, vec->getZ() + 0.3);
	glVertex3f(vec->getX() + 0.35, vec->getY() + 0.5, vec->getZ() + 0.3);
	glEnd();

	normal = this->normalVector(vec->getX() + 0.35, vec->getY() + 0.5, vec->getZ() + 0.3, vec->getX() + 0.35, vec->getY() + 0.4, vec->getZ() + 0.3, vec->getX() + 0.25, vec->getY() + 0.4, vec->getZ() + 0.25);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.35, vec->getY() + 0.5, vec->getZ() + 0.3);
	glVertex3f(vec->getX() + 0.35, vec->getY() + 0.4, vec->getZ() + 0.3);
	glVertex3f(vec->getX() + 0.25, vec->getY() + 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.25, vec->getY() + 0.5, vec->getZ() + 0.25);
	glEnd();

	normal = this->normalVector(vec->getX() + 0.25, vec->getY() + 0.5, vec->getZ() + 0.25, vec->getX() + 0.25, vec->getY() + 0.4, vec->getZ() + 0.25, vec->getX() + 0.2, vec->getY() + 0.4, vec->getZ() + 0.15);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.25, vec->getY() + 0.5, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.25, vec->getY() + 0.4, vec->getZ() + 0.25);
	glVertex3f(vec->getX() + 0.2, vec->getY() + 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.2, vec->getY() + 0.5, vec->getZ() + 0.15);
	glEnd();

	normal = this->normalVector(vec->getX() + 0.2, vec->getY() + 0.5, vec->getZ() + 0.15, vec->getX() + 0.2, vec->getY() + 0.4, vec->getZ() + 0.15, vec->getX() + 0.25, vec->getY() + 0.5, vec->getZ() + 0.05);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.2, vec->getY() + 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.2, vec->getY() + 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.25, vec->getY() + 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.25, vec->getY() + 0.5, vec->getZ() + 0.05);
	glEnd();

	normal = this->normalVector(vec->getX() + 0.2, vec->getY() + 0.5, vec->getZ() + 0.15, vec->getX() + 0.2, vec->getY() + 0.4, vec->getZ() + 0.15, vec->getX() + 0.25, vec->getY() + 0.5, vec->getZ() + 0.05);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.2, vec->getY() + 0.5, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.2, vec->getY() + 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.25, vec->getY() + 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.25, vec->getY() + 0.5, vec->getZ() + 0.05);
	glEnd();

	normal = this->normalVector(vec->getX() + 0.25, vec->getY() + 0.5, vec->getZ() + 0.05, vec->getX() + 0.25, vec->getY() + 0.4, vec->getZ() + 0.05, vec->getX() + 0.35, vec->getY() + 0.4, vec->getZ());
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.25, vec->getY() + 0.5, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.25, vec->getY() + 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.35, vec->getY() + 0.4, vec->getZ());
	glVertex3f(vec->getX() + 0.35, vec->getY() + 0.5, vec->getZ());
	glEnd();

	normal = this->normalVector(vec->getX() + 0.35, vec->getY() + 0.5, vec->getZ(), vec->getX() + 0.35, vec->getY() + 0.4, vec->getZ(), vec->getX() + 0.45, vec->getY() + 0.4, vec->getZ() + 0.05);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.35, vec->getY() + 0.5, vec->getZ());
	glVertex3f(vec->getX() + 0.35, vec->getY() + 0.4, vec->getZ());
	glVertex3f(vec->getX() + 0.45, vec->getY() + 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.45, vec->getY() + 0.5, vec->getZ() + 0.05);
	glEnd();

	normal = this->normalVector(vec->getX() + 0.45, vec->getY() + 0.5, vec->getZ() + 0.05, vec->getX() + 0.45, vec->getY() + 0.4, vec->getZ() + 0.05, vec->getX() + 0.5, vec->getY() + 0.4, vec->getZ() + 0.15);
	glBegin(GL_QUADS);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vec->getX() + 0.45, vec->getY() + 0.5, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.45, vec->getY() + 0.4, vec->getZ() + 0.05);
	glVertex3f(vec->getX() + 0.5, vec->getY() + 0.4, vec->getZ() + 0.15);
	glVertex3f(vec->getX() + 0.5, vec->getY() + 0.5, vec->getZ() + 0.15);
	glEnd();
}