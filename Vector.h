#ifndef VECTOR_H
#define VECTOR_H

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
};


#endif