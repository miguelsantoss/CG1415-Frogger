#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#include "GameObject.h"
#include "Vector3.h"

class DynamicObject : public GameObject {
public:
	DynamicObject();
	~DynamicObject();
	void update(double delta_t);
	void setSpeed(const Vector3& speed);
	void setSpeed(double x, double y, double z);
	int getDirection() const;
	void setDirection(int direction);
	int getTimer();
	void setTimer(int timer);
	bool getToDraw();
	void setToDraw(bool draw);
	Vector3 getSpeed();
	Vector3& normalVector(double x0, double x1, double x2, double y0, double y1, double y2, double z0, double z1, double z2);
protected:
	Vector3 _speed;
private:
	int _direction;
	int _timer;
	bool _todraw;
};

#endif