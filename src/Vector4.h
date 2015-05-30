#ifndef VECTOR4_H
#define VECTOR4_H

#include "Vector3.h"

class Vector4 : public Vector3
{
public:
	Vector4();
	Vector4(double x, double y, double z, double w);
	~Vector4();
	double getW() const;
	void set(double x, double y, double z, double w);
	Vector4& operator=(const Vector4& vec);
	Vector4& operator*(double num);
	Vector4& operator+(const Vector4& vec);
	Vector4& operator-(const Vector4& vec);
protected:
	double _w;
};

#endif