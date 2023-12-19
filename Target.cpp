#include "Target.h"

//-------Constructors
Target::Target() {}
Target::~Target() {}
Target::Target(float cX, float cY, int cWidth, int cHeight) {
    Entity(cX, cY, cWidth, cHeight);
}
