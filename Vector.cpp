#include "Vector.h"

//-------Constructors
Vector::Vector() {
    i = 0;
    j = 0;
}
Vector::Vector(float ci, float cj) {
    i = ci;
    j = cj;
    this->makeUnit();
}

//-------Getters
float Vector::getI() { return i; }
float Vector::getJ() { return j; }

//-------Setters
void Vector::setI(float newI) { i = newI; }
void Vector::setJ(float newJ) { j = newJ; }

//-------Methods
void Vector::makeUnit() {
    float length = sqrt((this->i) * (this->i) + (this->j) * (this->j));

    this->setI(this->getI() / length);
    this->setJ(this->getJ() / length);
}

void Vector::rotateVector(float angleDegrees) {
    float radians = angleDegrees * PI / 180.0;

    this->setI(this->getI() * cos(radians) - this->getJ() * sin(radians));
    this->setJ(this->getI() * sin(radians) + this->getJ() * cos(radians));
}