#include "Target.h"

//-------Constructors
Target::Target(float cX, float cY, int cWidth, int cHeight) {
    x = cX;
    y = cY;
    width = cWidth;
    height = cHeight;
}

//-------Getters
float Target::getX() { return x; }
float Target::getY() { return y; }
int Target::getWidth() { return width; }
int Target::getHeight() { return height; }

//-------Setters
void Target::setX(float newX) { x = newX; }
void Target::setY(float newY) { y = newY; }
void Target::setWidth(int newWidth) { width = newWidth; }
void Target::setHeight(int newHeight) { height = newHeight; }

//-------Methods
