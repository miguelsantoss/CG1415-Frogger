#ifndef DIRECTEDLIGHT_H
#define DIRECTEDLIGHT_H

#include "Lightsource.h"

class DirectedLight : public LightSource{
public:
	DirectedLight(GLenum number);
	~DirectedLight();
	void shine();
	void draw();
};

#endif