#include "Camera.h"

Camera::Camera(double near, double far) {
	_near = near;
	_far = far;
}

Camera::~Camera() {}

void Camera::update() {}

void Camera::computeProjectionMatrix() {}

void Camera::computeVisualizationMatrix() {}

void Camera::setUp(const Vector3& vec) {
	_up = vec;
}
void Camera::setUp(double x, double y, double z) {
	_up.set(x, y, z);
}

void Camera::setAt(const Vector3& vec) {
	_at = vec;
}

void Camera::setAt(double x, double y, double z) {
	_at.set(x, y, z);
}

Vector3* Camera::getUp() {
	return &_up;
}

Vector3* Camera::getAt() {
	return &_at;
}