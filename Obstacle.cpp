#include "Obstacle.h"

//-------Constructors
Obstacle::Obstacle(float cX, float cY, int cWidth, int cHeight) {
    x = cX;
    y = cY;
    width = cWidth;
    height = cHeight;
}

//-------Getters
float Obstacle::getX() { return x; }
float Obstacle::getY() { return y; }
int Obstacle::getWidth() { return width; }
int Obstacle::getHeight() { return height; }

//-------Setters
void Obstacle::setX(float newX) { x = newX; }
void Obstacle::setY(float newY) { y = newY; }
void Obstacle::setWidth(int newWidth) { width = newWidth; }
void Obstacle::setHeight(int newHeight) { height = newHeight; }

//-------Methods
