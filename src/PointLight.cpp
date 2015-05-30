#include "PointLight.h"


PointLight::PointLight(GLenum number) : LightSource(number) { }

PointLight::~PointLight() { }

void PointLight::shine() {
	GLfloat ambient[] = { static_cast<GLfloat>(_ambient->getX()), static_cast<GLfloat>(_ambient->getY()), static_cast<GLfloat>(_ambient->getZ()), static_cast<GLfloat>(_ambient->getW()) };
	GLfloat diffuse[] = { static_cast<GLfloat>(_diffuse->getX()), static_cast<GLfloat>(_diffuse->getY()), static_cast<GLfloat>(_diffuse->getZ()), static_cast<GLfloat>(_diffuse->getW()) };
	GLfloat specular[] = { static_cast<GLfloat>(_specular->getX()), static_cast<GLfloat>(_specular->getY()), static_cast<GLfloat>(_specular->getZ()), static_cast<GLfloat>(_specular->getW()) };
	GLfloat position[] = { static_cast<GLfloat>(_position->getX()), static_cast<GLfloat>(_position->getY()), static_cast<GLfloat>(_position->getZ()), static_cast<GLfloat>(_position->getW()) };
	GLfloat direction[] = { static_cast<GLfloat>(_direction->getX()), static_cast<GLfloat>(_direction->getY()), static_cast<GLfloat>(_direction->getZ()), static_cast<GLfloat>(_direction->getW()) };
	glLightfv(_num, GL_AMBIENT, ambient);
	glLightfv(_num, GL_DIFFUSE, diffuse);
	glLightfv(_num, GL_SPECULAR, specular);
	glLightfv(_num, GL_POSITION, position);
	glLightfv(_num, GL_SPOT_DIRECTION, direction);
	glLightf(_num, GL_SPOT_CUTOFF, _cut_off);
	glLightf(_num, GL_SPOT_EXPONENT, _exponent);
	if (_num == GL_LIGHT7) {
		glLightf(_num, GL_LINEAR_ATTENUATION, 0.25f);
	}
}

void PointLight::draw() {
	glColor3f(1.0, 1.0, 1.0);
	GLfloat amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat diff[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat spec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	if (glIsEnabled(_num)) {
		GLfloat emission[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	}
	else if (glIsEnabled(GL_LIGHT0) && !glIsEnabled(_num)) {
		GLfloat emission[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	}
	else {
		GLfloat emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	}
	GLfloat shine = 128;
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix();
	glTranslatef(_position->getX(), _position->getY(), _position->getZ());
	glScalef(0.3, 0.3, 0.3);
	glutSolidSphere(1.0, 8.0, 8.0);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	GLfloat postamb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat postdiff[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat postspec[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat postemission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat postshine = 50;
	glMaterialfv(GL_FRONT, GL_AMBIENT, postamb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, postdiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, postspec);
	glMaterialf(GL_FRONT, GL_SHININESS, postshine);
	glMaterialfv(GL_FRONT, GL_EMISSION, postemission);
	glTranslatef(_position->getX(), _position->getY(), _position->getZ() - 1.0);
	glScalef(0.1, 0.1, 1.4);
	glutSolidCube(1.0);
	glPopMatrix();
}