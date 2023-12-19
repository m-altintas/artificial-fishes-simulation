/*
    Run:
    g++ main-gui.cpp Vector.cpp World.cpp Agent.cpp -o app -lsfml-graphics -lsfml-window -lsfml-system && ./app
    Debug:
    g++ -g main-gui.cpp Vector.cpp World.cpp Agent.cpp -lsfml-graphics -lsfml-window -lsfml-system && gdb ./a.out
*/

#include <SFML/Graphics.hpp>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <thread>
#include <memory>

#include "World.h"
#include "Agent.h"
#include "Target.h"
#include "Obstacle.h"
#include "Vector.h"

//test variables
#define total_trial 100
#define trial_batch_size 1
//pixel size to determine gui details
#define pxSize 8
//pre-defined sizes
#define world_width 200
#define world_height 100
#define agent_width 3
#define agent_height 5
#define obstacle_width 2
#define obstacle_height 2
#define target_width 10
#define target_height 10
//Agent specifications
#define agent_sight 5
#define agent_weight 10
#define agent_speed 2

using namespace sf;
using std::ofstream;
using std::cout;
using std::endl;

typedef std::shared_ptr<Entity> EntityPtr;

int main() {
    srand(time(0));

    //GUI foundation {
    RenderWindow window(VideoMode(world_width * pxSize, world_height * pxSize), "Artificial Fishes");
    window.setFramerateLimit(60);

    Texture txtrBackground, txtrAgent, txtrTarget, txtrObstacle, txtrAgentEye;
    if (!txtrBackground.loadFromFile("images/tile.png"))
        cout << "Error: could not load tile image" << endl;
    if (!txtrAgent.loadFromFile("images/agent-3x-5y.png"))
        cout << "Error: could not load tile image" << endl;
    else
        txtrAgent.setSmooth(true);
    if (!txtrTarget.loadFromFile("images/target-20x-20y.png"))
        cout << "Error: could not load tile image" << endl;
    else
        txtrTarget.setSmooth(true);
    if (!txtrObstacle.loadFromFile("images/obstacle-2x-2y.png"))
        cout << "Error: could not load tile image" << endl;
    else
        txtrObstacle.setSmooth(true);
    if (!txtrAgentEye.loadFromFile("images/eye.png"))
        cout << "Error: could not load tile image" << endl;
    else
        txtrAgentEye.setSmooth(true);

    Sprite sprtBackground(txtrBackground);
    Sprite sprtAgent(txtrAgent);
    Sprite sprtTarget(txtrTarget);
    Sprite sprtObstacle(txtrObstacle);
    Sprite sprtAgentEye(txtrAgentEye);
    // }

    //World initialization
    World world(world_width, world_height);
    EntityPtr agent = std::make_shared<Agent>(20 + ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 160), (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 100, agent_sight, agent_weight, agent_speed, agent_width, agent_height);
    EntityPtr target = std::make_shared<Target>(20 + ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 160), (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 100, target_width, target_height);
    world.worldInitialization(agent, target);

    int trialCount = 0;
    while (trialCount < total_trial) {

        world.worldInitialization(agent, target);

        int innerTrialCount = 0;
        while (innerTrialCount < trial_batch_size) {

            std::shared_ptr<Agent> agentPtr = std::dynamic_pointer_cast<Agent>(agent);
            std::shared_ptr<Target> targetPtr = std::dynamic_pointer_cast<Target>(target);

            //Initialization of vectors and first view angle
            float y = (0 + (double)(rand()) / (double)(RAND_MAX) / 1) - 1.0 / 2.0;
            float x = sqrt(1 - (y * y));
            Vector dir(-x, y);
            Vector mov(dir.getI(), dir.getJ());

            agentPtr->setEyeX((agentPtr->getX() + 2) + 2 * (dir.getI()));

            while (true) {
                Event e;
                while (window.pollEvent(e)) {
                    if (e.type == Event::Closed) window.close();
                }

                //Agent actions
                if(agentPtr->mission()) {
                    agentPtr->percieve(world);
                    dir = agentPtr->decide(mov);
                    mov = agentPtr->move(world, mov, dir);
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                } else {
                    //TODO: Mission accomplished
                    break;
                }

                ///draw
                window.clear();

                //background
                for (int i = 0; i < world.getWidth(); i++)
                    for (int j = 0; j < world.getHeight(); j++) {
                        sprtBackground.setPosition(i * pxSize, j * pxSize);
                        window.draw(sprtBackground);
                    }

                //agent
                sprtAgent.setPosition(agentPtr->getX() * pxSize, agentPtr->getY() * pxSize);
                window.draw(sprtAgent);

                //target
                sprtTarget.setPosition(targetPtr->getX() * pxSize, targetPtr->getY() * pxSize);
                window.draw(sprtTarget);

                //obstacles
                for (auto& entity : world.getEntities()) {
                    if(dynamic_cast<Obstacle *>(entity.get()) != nullptr) {
                        std::shared_ptr<Obstacle> obstaclePtr = std::dynamic_pointer_cast<Obstacle>(entity);
                        sprtObstacle.setPosition(obstaclePtr->getX() * pxSize, obstaclePtr->getY() * pxSize);
                        window.draw(sprtTarget);
                    }
                }

                sprtAgentEye.setPosition(agentPtr->getEyeX() * pxSize, agentPtr->getEyeY() * pxSize);
                window.draw(sprtAgentEye);

                window.display();
                std::this_thread::sleep_for(std::chrono::milliseconds(7));
            }

            innerTrialCount++;
            trialCount++;
        }
    }
    window.close();

    return 0;
}