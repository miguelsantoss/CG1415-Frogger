#ifndef CAR_H
#define CAR_H

#include "DynamicObject.h"

class Car : public DynamicObject {
public:
	Car();
	Car::Car(double x, double y, double z, Vector3 speed, int direction, int timer);
	~Car();
	void draw();
private:
	void drawBox();
	void drawBoxHorizontal();
	void drawBoxVerticalX();
	void drawBoxVerticalY();
	void drawRoof();
	void drawRoofHorizontal();
	void drawRoofDiagonalFront();
	void drawRoofDiagonalBack();
	void drawRoofVerticalY();
	void drawWheels();
	void drawWheelFrontLeft();
	void drawWheelFrontRight();
	void drawWheelRearLeft();
	void drawWheelRearRight();
};

#endif