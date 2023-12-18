#ifndef TARGET_H
#define TARGET_H

class Target {
private:
    //-------Instance Variables
    float x, y;
    int width, height;

public:
    //-------Constructors
    Target(float cx, float cy, int cWidth, int cHeight);

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