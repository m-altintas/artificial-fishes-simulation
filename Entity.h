#ifndef ENTITY_H
#define ENTITY_H

class Entity {
private:
    //-------Instance Variables
    float x, y;
    int width, height;

public:
    //-------Constructors
    Entity();
    virtual ~Entity();
    Entity(float cx, float cy, int cWidth, int cHeight);

    //-------Getters
    float getX();
    float getY();
    int getWidth();
    int getHeight();

    //-------Setters
    void setX(float newX);
    void setY(float newY);
    void setWidth(int newWidth);
    void setHeight(int newHeight);
};

#endif