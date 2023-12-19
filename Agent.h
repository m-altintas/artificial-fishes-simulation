#ifndef AGENT_H
#define AGENT_H

#include <math.h>
#include <vector>
#include <memory>

#include "Vector.h"
#include "World.h"
#include "Entity.h"
#include "Target.h"

#define PI 3.14159265358979323846

typedef std::shared_ptr<Entity> EntityPtr;

class Agent : public Entity{
private:
    //-------Instance Variables
    float eyeX, eyeY, sight, weight, speed;
    std::vector<EntityPtr> percEntities;

    //-------Private Methods
    EntityPtr findTarget(std::vector<EntityPtr> visibleEntities);
    bool isPathToTargetClear(std::vector<EntityPtr> visibleEntities, EntityPtr target);
    bool isObstacleInDirection(Vector& dir, EntityPtr& entity);
    bool isPathClear(Vector &dir, std::vector<EntityPtr> visibleEntities);

public:
    //-------Constructors
    Agent();
    virtual ~Agent();
    Agent(float cx, float cy, float cSight, float cWeight, float cSpeed, int cWidth, int cHeight);
    Agent(float cx, float cy, float cSight);

    //-------Getters
    float getEyeX();
    float getEyeY();
    float getSight();
    float getWeight();
    float getSpeed();
    std::vector<EntityPtr> getPercEntities();

    //-------Setters
    void setEyeX(float newEyeX);
    void setEyeY(float newEyeY);
    void setSight(float newSight);
    void setWeight(float newWeight);
    void setSpeed(float newSpeed);
    void setPercEntities(std::vector<EntityPtr> newPercEntities);

    //-------Methods
    //percieve
    void percieve(World& world);

    //deciede
    Vector decide(Vector& mov);

    //move
    Vector move(World& world, Vector& dir);

    bool mission();
};

#endif