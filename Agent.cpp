#include "Agent.h"
#include <math.h>
#include "Vector.h"
#include "World.h"
#include "Target.h"

//-------Constructors
Agent::Agent(float cX, float cY, float cWeight, float cSpeed, int cWidth, int cHeight) {
    x = cX;
    y = cY;
    indicX = cX;
    indicY = cY;
    weight = cWeight;
    speed = cSpeed;
    width = cWidth;
    height = cHeight;
}

//-------Getters
float Agent::getX() { return x; }
float Agent::getY() { return y; }
float Agent::getIndicX() { return indicX; }
float Agent::getIndicY() { return indicY; }
float Agent::getWeight() { return weight; }
float Agent::getSpeed() { return speed; }
int Agent::getWidth() { return width; }
int Agent::getHeight() { return height; }

//-------Setters
void Agent::setX(float newX) { x = newX; }
void Agent::setY(float newY) { y = newY; }
void Agent::setIndicX(float newIndicX) { indicX = newIndicX; }
void Agent::setIndicY(float newIndicY) { indicY = newIndicY; }
void Agent::setWeight(float newWeight) { weight = newWeight; }
void Agent::setSpeed(float newSpeed) { speed = newSpeed; }
void Agent::setWidth(int newWidth) { width = newWidth; }
void Agent::setHeight(int newHeight) { height = newHeight; }

//-------Methods
    //percieve
float Agent::percieve(Target& target) {
    //distance between this agent and the target
    float x, y, distance;
    x = pow((target.getX() - this->getX()), 2);
    y = pow((target.getY() - this->getY()), 2);
    distance = sqrt(x + y) - 5;
    if (distance < 0)
        distance = 0;
    return distance;
}

//deciede
bool Agent::decide(Target& target, Vector& v1, Vector& v2) {
    float alpha = 0.85;
    //v1 - distance vector
    v1.setI(target.getX() - this->getX());
    v1.setJ(target.getY() - this->getY());
    v1.makeUnit();

    //v2 - direction vector
    Vector v((1 - alpha) * v2.getI() + (alpha)*v1.getI(), (1 - alpha) * v2.getJ() + (alpha)*v1.getJ());
    v2.setI(v.getI());
    v2.setJ(v.getJ());
    v2.makeUnit();

    //catch control
    float xD, yD, distanceD;
    xD = pow((target.getX() - this->getX()), 2);
    yD = pow((target.getY() - this->getY()), 2);
    distanceD = sqrt(xD + yD);
    if (distanceD < 6)
        return 0;
    else
        return 1;
}

//move
void Agent::move(World& world, Vector& v) {
    //move this agent
    this->setX(this->getX() + 2 * (v.getI()));
    this->setY(this->getY() + 2 * (v.getJ()));

    //move this agent's indicator/eye
    this->setIndicX((this->getX() + 2) + 2 * (v.getI()));
    this->setIndicY((this->getY() + 2) + 2 * (v.getJ()));

    //control world boundaries and stay inside
    if (this->getX() + this->getSize() > world.getWidthMod())
        this->setX(world.getWidthMod() - this->getSize());
    if (this->getX() < 0)
        this->setX(0);
    if (this->getY() + this->getSize() > world.getHeightMod())
        this->setY(world.getHeightMod() - this->getSize());
    if (this->getY() < 0)
        this->setY(0);
}