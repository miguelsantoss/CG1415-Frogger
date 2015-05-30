#ifndef ROAD_H
#define ROAD_H

#include "StaticObject.h"

class Road : public StaticObject {
public:
	Road();
	~Road();
	void draw();
};

#endif