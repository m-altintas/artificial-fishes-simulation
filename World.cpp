#include "World.h"

typedef std::shared_ptr<Entity> EntityPtr;

//-------Constructors
World::World(int cWidth, int cHeight) {
    width = cWidth;
    height = cHeight;
}

//-------Getters
int World::getWidth() { return width; }
int World::getHeight() { return height; }
std::vector<EntityPtr> World::getEntities() { return entities; }

//-------Setters
void World::setWidth(int newWidth) { width = newWidth; }
void World::setHeight(int newHeight) { height = newHeight; }
void World::setEntities(std::vector<EntityPtr> newEntities) { entities = newEntities; }

//-------Methods
void World::worldInitialization(EntityPtr agent, EntityPtr target) {
    srand(time(0));
    for (int i = 0; i < 80; i++) {
        EntityPtr obstacle = std::make_shared<Obstacle>(20 + ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 160), (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 100, 2, 2);
        entities.push_back(obstacle);
    }
    agent->setX((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 20);
    agent->setY((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 100);
    entities.push_back(agent);

    target->setX(180 + ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 20));
    target->setY((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 100);
    entities.push_back(target);
}


std::vector<EntityPtr> World::getFieldOfView(float x, float y, float sight) {
    std::vector<EntityPtr> percEntities;
    int k = 0;
    for (int i = 0; i < 81; i++) {
        float x, y, distance;
        x = pow((entities.at(i)->getX() - x), 2);
        y = pow((entities.at(i)->getY() - y), 2);
        distance = sqrt(x + y) - 5;
        if (distance < sight) {
            percEntities.push_back(entities[i]);
            k++;
        }
    }
    return percEntities;
}