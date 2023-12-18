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
#include "World.h"
#include "Agent.h"
#include "Obstacle.h"
#include "Target.h"
#include "Vector.h"

//test variables
#define total_trial 100
#define trial_batch_size 5
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
#define agent_weight 10
#define agent_speed 2

using namespace sf;
using std::ofstream;
using std::cout;
using std::endl;


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

    //TODO: use sizes

    Sprite sprtBackground(txtrBackground);
    Sprite sprtAgent(txtrAgent);
    Sprite sprtTarget(txtrTarget);
    Sprite sprtObstacle(txtrObstacle);
    Sprite sprtAgentEye(txtrAgentEye);
    // }

    //World initialization
    World world(world_width, world_height);
    Agent agent(187.5, 25 + (rand() % (world.getHeight() / 2)), agent_weight, agent_speed, agent_width, agent_height); //TODO: more random spawn
    Target target(7.5, 25 + (rand() % (world.getHeight() / 2)), target_width, target_height); //TODO: more random spawn
    world.worldInitialization(agent, target);

    int trialCount = 0;
    while (trialCount < total_trial) {

        int innerTrialCount = 0;
        while (innerTrialCount < trial_batch_size) {

            //Initialization of vectors and first view angle
            Vector v1;
            float y = (0 + (double)(rand()) / (double)(RAND_MAX) / 1) - 1.0 / 2.0;
            float x = sqrt(1 - (y * y));
            Vector v2(-x, y);
            agent.setIndicX((agent.getX() + 2) + 2 * (v2.getI()));

            while (true) {
                Event e;
                while (window.pollEvent(e)) {
                    if (e.type == Event::Closed) window.close();
                }

                //TODO: Agent actions

                ///////draw
                window.clear();

                //background
                for (int i = 0; i < world.getWidth(); i++)
                    for (int j = 0; j < world.getHeight(); j++) {
                        sprtBackground.setPosition(i * pxSize, j * pxSize);
                        window.draw(sprtBackground);
                    }

                //agent
                sprtAgent.setPosition(agent.getX() * pxSize, agent.getY() * pxSize);
                window.draw(sprtAgent);

                //target
                sprtTarget.setPosition(target.getX() * pxSize, target.getY() * pxSize);
                window.draw(sprtTarget);

                //obstacles
                //TODO: obstacle array drawing

                //TODO: direction indicator, agent's eye
                sprtAgentEye.setPosition(agent.getIndicX() * pxSize, agent.getIndicY() * pxSize);
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