#include "OrthogonalCamera.h"
#include <gl/glut.h>

OrthogonalCamera::OrthogonalCamera(double left, double right, double bottom, double top, double near, double far) : Camera(near, far) {
	_left = left;
	_right = right;
	_bottom = bottom;
	_top = top;
}

OrthogonalCamera::~OrthogonalCamera() {}

void OrthogonalCamera::update() {

}

void OrthogonalCamera::computeProjectionMatrix() {
	float w = glutGet(GLUT_WINDOW_WIDTH), h = glutGet(GLUT_WINDOW_HEIGHT);
	float ratio = (_right - _left) / (_top - _bottom);
	float aspect = (float)w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio < aspect)
	{
		float delta = ((_top - _bottom) * aspect - (_right - _left)) / 2;
		glOrtho(_left - delta, _right + delta, _bottom, _top, _near, _far);
	}
	else
	{
		float delta = ((_right - _left) / aspect - (_top - _bottom)) / 2;
		glOrtho(_left, _right, _bottom - delta, _top + delta, _near, _far);
	}
}



void OrthogonalCamera::computeVisualizationMatrix() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}