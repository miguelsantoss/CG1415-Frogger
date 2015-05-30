#include "Vector4.h"

Vector4::Vector4() : Vector3() {
	_w = 0.0;
}

Vector4::Vector4(double x, double y, double z, double w) : Vector3(x, y, z) {
	_w = w;
}

Vector4::~Vector4(){}

double Vector4::getW() const {
	return _w;
}

void Vector4::set(double x, double y, double z, double w) {
	Vector3::set(x, y, z);
	_w = w;
}


Vector4& Vector4::operator=(const Vector4& vec) {
	_x = vec.getX();
	_y = vec.getY();
	_z = vec.getZ();
	_w = vec.getW();
	return *this;
}

Vector4& Vector4::operator*(double num) {
	_x *= num;
	_y *= num;
	_z *= num;
	_w *= num;
	return *this;
}

Vector4& Vector4::operator+(const Vector4& vec) {
	_x += vec.getX();
	_y += vec.getY();
	_z += vec.getZ();
	_w += vec.getW();
	return *this;
}

Vector4& Vector4::operator-(const Vector4& vec) {
	_x -= vec.getX();
	_y -= vec.getY();
	_z -= vec.getZ();
	_w -= vec.getW();
	return *this;
}