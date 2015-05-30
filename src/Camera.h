#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"
#include "Vector3.h"

class Camera : public Entity {
public:
	Camera(double near, double far);
	~Camera();
	void update();
	void setUp(const Vector3& vec);
	void setUp(double x, double y, double z);
	void setAt(const Vector3& vec);
	void setAt(double x, double y, double z);
	Vector3* getAt();
	Vector3* getUp();
	virtual void computeProjectionMatrix() = 0;
	virtual void computeVisualizationMatrix() = 0;
protected:
	Vector3 _up;
	Vector3 _at;
	double _near;
	double _far;
};

#endif