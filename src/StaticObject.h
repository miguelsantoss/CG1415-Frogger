#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include "GameObject.h"

class StaticObject : public GameObject {
public:
	StaticObject();
	~StaticObject();
	void update(double delta_t);
};

#endif