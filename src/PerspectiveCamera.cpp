#include "PerspectiveCamera.h"
#include <iostream>
#include <gl/glut.h>

PerspectiveCamera::PerspectiveCamera(double fovy, double aspect, double zNear, double zFar) : Camera(zNear, zFar){
	_fovy = fovy;
	_aspect = aspect;
}

PerspectiveCamera::~PerspectiveCamera() {}

void PerspectiveCamera::update() {

}

void PerspectiveCamera::computeProjectionMatrix() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(_fovy, _aspect, _near, _far);
}

void PerspectiveCamera::computeVisualizationMatrix() {
	Vector3 *pos = this->getPosition();
	Vector3 *at = this->getAt();
	Vector3 *up = this->getUp();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pos->getX(), pos->getY(), pos->getZ(), at->getX(), at->getY(), at->getZ(), up->getX(), up->getY(), up->getZ());
}