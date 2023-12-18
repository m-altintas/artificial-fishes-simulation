#include "World.h"

//-------Constructors
World::World(int cWidth, int cHeight) {
    width = cWidth;
    height = cHeight;
}

//-------Getters
int World::getWidth() { return width; }
int World::getHeight() { return height; }

//-------Setters
void World::setWidth(int newWidth) { width = newWidth; }
void World::setHeight(int newHeight) { height = newHeight; }