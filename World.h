#ifndef WORLD_H
#define WORLD_H

class World {
private:
    int width, height;

public:
    //-------Constructors
    World(int cWidht, int cHeight);

    //-------Getters
    int getWidth();
    int getHeight();

    //-------Setters
    void setWidth(int newWidthMod);
    void setHeight(int newHeightMod);

    //-------Methods
    void worldInitialization(Agent& agent, Target& target);
};

#endif