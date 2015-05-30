#ifndef ENTITY_H
#define ENTITY_H

#include "Vector3.h"

class Entity
{
public:
	Entity();
	~Entity();
	Vector3* getPosition();
	Vector3* setPosition(double newX, double newY, double newZ);
	Vector3* setPosition(const Vector3& vec);
protected:
	Vector3 _position;
};

#endif