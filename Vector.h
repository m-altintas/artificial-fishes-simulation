#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#define PI 3.14159265358979323846

class Vector {
private:
    //-------Instance Variables
    float i, j;

public:
    //-------Constructors
    Vector();
    Vector(float ci, float cj);

    //-------Getters
    float getI();
    float getJ();

    //-------Setters
    void setI(float newI);
    void setJ(float newJ);

    //-------Methods
    void makeUnit();
    void rotateVector(float angleDegrees);
};


#endif