#include "Entity.h"

//-------Constructors
Entity::Entity() {
    x = 0;
    y = 0;
    width = 0;
    height = 0;
}
Entity::~Entity() {
    x = 0;
    y = 0;
    width = 0;
    height = 0;
}
Entity::Entity(float cX, float cY, int cWidth, int cHeight) {
    x = cX;
    y = cY;
    width = cWidth;
    height = cHeight;
}

//-------Getters
float Entity::getX() { return x; }
float Entity::getY() { return y; }
int Entity::getWidth() { return width; }
int Entity::getHeight() { return height; }

//-------Setters
void Entity::setX(float newX) { x = newX; }
void Entity::setY(float newY) { y = newY; }
void Entity::setWidth(int newWidth) { width = newWidth; }
void Entity::setHeight(int newHeight) { height = newHeight; }