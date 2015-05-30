#include "DynamicObject.h"
#include <iostream>

DynamicObject::DynamicObject() {}

DynamicObject::~DynamicObject() {}

void DynamicObject::update(double delta_t) {
	Vector3 *vec = this->getPosition();
	Vector3 vel = this->getSpeed();
	(*vec) = (*vec) + (vel * delta_t);
	this->setPosition(*vec);
}

void DynamicObject::setSpeed(const Vector3& speed) {
	_speed = speed;
}

void DynamicObject::setSpeed(double x, double y, double z){
	_speed.set(x, y, z);
}

Vector3 DynamicObject::getSpeed() {
	return _speed;
}

Vector3& DynamicObject::normalVector(double x0, double x1, double x2, double y0, double y1, double y2, double z0, double z1, double z2) {
	Vector3 AB(y0 - x0, y1 - x1, y2 - x2);
	Vector3 BC(y0 - z0, y1 - z1, y2 - z2);
	Vector3 n((AB.getY() * BC.getZ()) - (AB.getY() * BC.getZ()), (AB.getX() * BC.getZ()) - (AB.getZ() * BC.getX()), (AB.getX() * BC.getY()) - (AB.getY() * BC.getX()));
	return n;
}

int DynamicObject::getDirection() const {
	return _direction;
}

void  DynamicObject::setDirection(int direction) {
	_direction = direction;
}

int DynamicObject::getTimer() {
	return _timer;
}
void DynamicObject::setTimer(int timer) {
	_timer = timer;
}

bool DynamicObject::getToDraw() {
	return _todraw;
}

void DynamicObject::setToDraw(bool draw) {
	_todraw = draw;
}