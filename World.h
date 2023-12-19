#ifndef WORLD_H
#define WORLD_H

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <memory>

#include "Entity.h"
#include "Agent.h"
#include "Target.h"
#include "Obstacle.h"

class Entity;
class Agent;
class Target;

typedef std::shared_ptr<Entity> EntityPtr;

class World {
private:
    int width, height;
    std::vector<EntityPtr> entities;

public:
    //-------Constructors
    World(int cWidht, int cHeight);

    //-------Getters
    int getWidth();
    int getHeight();
    std::vector<EntityPtr> getEntities();

    //-------Setters
    void setWidth(int newWidthMod);
    void setHeight(int newHeightMod);
    void setEntities(std::vector<EntityPtr> newEntities);

    //-------Methods
    void worldInitialization(EntityPtr agent, EntityPtr target);
    std::vector<EntityPtr> getFieldOfView(float x, float y, float sight);
};

#endif