#ifndef TARGET_H
#define TARGET_H

#include "Entity.h"

class Target : public Entity {
public:
	//-------Constructors
	Target();
	virtual ~Target();
	Target(float cx, float cy, int cWidth, int cHeight);
};

#endif