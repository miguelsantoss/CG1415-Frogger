#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "Vector4.h"
#include "Vector3.h"
#include <gl/glut.h>

class LightSource {
public:
	LightSource(GLenum number);
	~LightSource();
	bool getState();
	bool setState(bool state);
	GLenum getNum();
	void setPosition(Vector4* position);
	void setDirection(Vector4* direction);
	void setCutOff(double cut_off);
	void setExponent(double exponent);
	void setAmbient(Vector4* ambient);
	void setDiffuse(Vector4* diffuse);
	void setSpecular(Vector4* specular);
	virtual void draw() = 0;
	virtual void shine() = 0;
protected:
	Vector4* _ambient;
	Vector4* _diffuse;
	Vector4* _specular;
	Vector4* _position;
	Vector4* _direction;
	double _cut_off;
	double _exponent;
	GLenum _num;
	bool _state;
};

#endif