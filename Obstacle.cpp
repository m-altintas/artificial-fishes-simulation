#include "Obstacle.h"

//-------Constructors
Obstacle::Obstacle() {}
Obstacle::~Obstacle() {}
Obstacle::Obstacle(float cX, float cY, int cWidth, int cHeight) {
    Entity(cX, cY, cWidth, cHeight);
}