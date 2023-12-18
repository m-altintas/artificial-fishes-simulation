#ifndef AGENT_H
#define AGENT_H

class Vector;
class World;
class Target;

class Agent {
private:
    //-------Instance Variables
    float x, y, indicX, indicY, weight, speed;
    int width, height;

public:
    //-------Constructors
    Agent(float cx, float cy, float cWeight, float cSpeed, int cWidth, int cHeight);

    //-------Getters
    float getX();
    float getY();
    float getIndicX();
    float getIndicY();
    float getWeight();
    float getSpeed();
    int getWidth();
    int getHeight();

    //-------Setters
    void setX(float newX);
    void setY(float newY);
    void setIndicX(float newIndicX);
    void setIndicY(float newIndicY);
    void setWeight(float newWeight);
    void setSpeed(float newSpeed);
    void setWidth(int newWidth);
    void setHeight(int newHeight);

    //-------Methods
    //percieve
    float percieve(Target& target);

    //deciede
    bool decide(Target& target, Vector& v1, Vector& v2);

    //move
    void move(World& world, Vector& v);
};

#endif