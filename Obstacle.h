#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle {
private:
    //-------Instance Variables
    float x, y;
    int width, height;

public:
    //-------Constructors
    Obstacle(float cx, float cy, int cWidth, int cHeight);

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

    //-------Methods
};

#endif