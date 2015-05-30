#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Lightsource.h"

class PointLight : public LightSource{
public:
	PointLight(GLenum number);
	~PointLight();
	void shine();
	void draw();
};

#endif