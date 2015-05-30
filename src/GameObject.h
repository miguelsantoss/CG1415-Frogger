#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Entity.h"

class GameObject : public Entity {
public:
	GameObject();
	~GameObject();
	virtual void draw() = 0;
	virtual void update(double delta_t) = 0;
};

#endif