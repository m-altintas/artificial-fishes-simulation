#include "Agent.h"

typedef std::shared_ptr<Entity> EntityPtr;

//-------Constructors
Agent::Agent() {}
Agent::~Agent() {}
Agent::Agent(float cX, float cY, float cSight, float cWeight, float cSpeed, int cWidth, int cHeight) {
    setX(cX);
    setY(cY);
    eyeX = cX;
    eyeY = cY;
    sight = cSight;
    weight = cWeight;
    speed = cSpeed;
    setWidth(cWidth);
    setHeight(cHeight);
}
Agent::Agent(float cX, float cY, float cSight) {
    setX(cX);
    setY(cY);
    sight = cSight;
}

//-------Getters
float Agent::getEyeX() { return eyeX; }
float Agent::getEyeY() { return eyeY; }
float Agent::getSight() { return sight; }
float Agent::getWeight() { return weight; }
float Agent::getSpeed() { return speed; }
std::vector<EntityPtr> Agent::getPercEntities() { return percEntities; }

//-------Setters
void Agent::setEyeX(float newEyeX) { eyeX = newEyeX; }
void Agent::setEyeY(float newEyeY) { eyeY = newEyeY; }
void Agent::setSight(float newSight) { sight = newSight; }
void Agent::setWeight(float newWeight) { weight = newWeight; }
void Agent::setSpeed(float newSpeed) { speed = newSpeed; }
void Agent::setPercEntities(std::vector<EntityPtr> newPercEntities) { percEntities = newPercEntities; }

//-------Methods
void Agent::percieve(World& world) {
    float x = getX();
    float y = getY();
    float sight = getSight();
    std::vector<EntityPtr> percEntities = world.getFieldOfView(x, y, sight);
    setPercEntities(percEntities);
}

Vector Agent::decide(Vector& mov) {
    std::vector<EntityPtr> visibleEntities = getPercEntities();

    //If the target is visible and there's a clear path, move directly towards it
    EntityPtr target = this->findTarget(visibleEntities);
    bool isTargetVisible = (target != nullptr) ? true : false;
    bool isPathToTargetClear = (isTargetVisible) ? this->isPathToTargetClear(visibleEntities, target) : false;

    if(isTargetVisible && isPathToTargetClear) {
        Vector newDirection(target->getX() - this->getX(), target->getY() - this->getY());
        return newDirection;
    }

    //# Check for obstacles and decide movement
    Vector tempDir(mov.getI(), mov.getJ());
    bool isFirstPhaseComplete = false;
    while(true) {
        if(isFirstPhaseComplete) {
            if(tempDir.getI() == mov.getI() && tempDir.getJ() == mov.getJ())
                return Vector(-1,0);
        }
        if(tempDir.getI() == 0 && tempDir.getJ() == 1) {
            tempDir.setJ(-1);
            isFirstPhaseComplete = true;
        }

        if(isPathClear(tempDir, visibleEntities))
            return tempDir;
        else
            tempDir.rotateVector(10);
    }
}

EntityPtr Agent::findTarget(std::vector<EntityPtr> visibleEntities) {
    EntityPtr target = nullptr;
    for (int i = 0; i < visibleEntities.size(); i++) {
        if(dynamic_cast<Target *>(visibleEntities.at(i).get()) != nullptr) {
            target = visibleEntities.at(i);
        }
    }
    return target;
}

bool Agent::isPathToTargetClear(std::vector<EntityPtr> visibleEntities, EntityPtr target) {
    Vector toTarget(target->getX() - this->getX(), target->getY() - this->getY());
    for (auto& ePtr : visibleEntities) {
            if (this->isObstacleInDirection(toTarget, ePtr)) {
                return false;
            }
        }
        return true;
}

bool Agent::isObstacleInDirection(Vector& dir, EntityPtr& entity) {
    if(dynamic_cast<Obstacle *>(entity.get()) != nullptr) {
        // Calculate the normal vector from the agent to the obstacle
        Vector toEntity(entity->getX() - this->getX(), entity->getY() - this->getY());

        // Calculate the dot product
        float dot = dir.getI() * toEntity.getI() + dir.getJ() * toEntity.getJ();

        // Calculate the angle between the vectors in degrees
        float angle = acos(dot) * 180.0 / PI;

        // Check if the obstacle is within the threshold angle
        if (angle <= 0) {
            return true;  // Obstacle is in the specified direction
        } else
            return false;

    } else
        return false; // The entity in direction is not even an obstacle
}

bool Agent::isPathClear(Vector &dir, std::vector<EntityPtr> visibleEntities) {
    for (auto& ePtr : visibleEntities) {
            if (this->isObstacleInDirection(dir, ePtr)) {
                return false;
            }
        }
        return true;
}

//move
Vector Agent::move(World& world, Vector& oldMov, Vector& dir) {
    //mov - movement vector
    float alpha = 1 - ((getWeight() * getSpeed()) / 100);
    Vector mov((1 - alpha) * oldMov.getI() + (alpha)*dir.getI(), (1 - alpha) * oldMov.getJ() + (alpha)*dir.getJ());

    //move this agent
    this->setX(this->getX() + 2 * (mov.getI()));
    this->setY(this->getY() + 2 * (mov.getJ()));

    //move this agent's indicator/eye
    this->setEyeX((this->getX() + 2) + 2 * (mov.getI()));
    this->setEyeY((this->getY() + 2) + 2 * (mov.getJ()));

    //control world boundaries and stay inside
    if (this->getX() + this->getWidth() > world.getWidth())
        this->setX(world.getWidth() - this->getWidth());
    if (this->getX() < 0)
        this->setX(0);
    if (this->getY() + this->getHeight() > world.getHeight())
        this->setY(world.getHeight() - this->getHeight());
    if (this->getY() < 0)
        this->setY(0);

    return mov;
}