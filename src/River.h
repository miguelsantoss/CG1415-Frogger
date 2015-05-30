#ifndef RIVER_H
#define RIVER_H

#include "StaticObject.h"

class River : public StaticObject {
public:
	River();
	~River();
	void draw();
};

#endif