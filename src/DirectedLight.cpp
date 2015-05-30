#include "DirectedLight.h"

DirectedLight::DirectedLight(GLenum number) : LightSource(number) { }

DirectedLight::~DirectedLight() {
	LightSource::~LightSource();
}

void DirectedLight::shine() {
	GLfloat ambient[] = { static_cast<GLfloat>(_ambient->getX()), static_cast<GLfloat>(_ambient->getY()), static_cast<GLfloat>(_ambient->getZ()), static_cast<GLfloat>(_ambient->getW()) };
	GLfloat diffuse[] = { static_cast<GLfloat>(_diffuse->getX()), static_cast<GLfloat>(_diffuse->getY()), static_cast<GLfloat>(_diffuse->getZ()), static_cast<GLfloat>(_diffuse->getW()) };
	GLfloat specular[] = { static_cast<GLfloat>(_specular->getX()), static_cast<GLfloat>(_specular->getY()), static_cast<GLfloat>(_specular->getZ()), static_cast<GLfloat>(_specular->getW()) };
	GLfloat direction[] = { static_cast<GLfloat>(_direction->getX()), static_cast<GLfloat>(_direction->getY()), static_cast<GLfloat>(_direction->getZ()), static_cast<GLfloat>(_direction->getW()) };
	glLightfv(_num, GL_AMBIENT, ambient);
	glLightfv(_num, GL_DIFFUSE, diffuse);
	glLightfv(_num, GL_SPECULAR, specular);
	glLightfv(_num, GL_POSITION, direction);
}

void DirectedLight::draw() { }
