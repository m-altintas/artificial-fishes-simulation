#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Entity.h"

class Obstacle : public Entity{
public:
	//-------Constructors
	Obstacle();
	virtual ~Obstacle();
	Obstacle(float cx, float cy, int cWidth, int cHeight);
};

#endif