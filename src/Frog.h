#ifndef FROG_H
#define FROG_H

#include "DynamicObject.h"

class Frog : public DynamicObject {
public:
	Frog();
	~Frog();
	void draw();
	Vector3* getDirection();
	void setDirection(Vector3* direction);
	void setDirection(double x, double y, double z);
private:
	Vector3* _direction;
	void rotate();
};

#endif