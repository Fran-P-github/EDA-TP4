#include <exception>
#include <cmath>
#include <iostream>
#include <string>
#include "algorithm.h"
#include "calculations.h"

#include <nlohmann/json.hpp>

#define PI 3.1415926535F
#define DEG_TO_RAD (PI / 180.0F)

using namespace std;
using json = nlohmann::json;

void poseHomeBots(HomeBot *homeBot1, HomeBot *homeBot2);

void poseHomeBots(HomeBot *homeBot1, HomeBot *homeBot2)
{
    Parameters_t bot1Pos = homeBot1->getPosition(), bot2Pos = homeBot2->getPosition();
    Parameters_t bot1BallControl = homeBot1->getBallControl(), bot2BallControl = homeBot2->getBallControl();

    json sampleMessage = {
        {"type", "set"},
        {"data",
         {{
             "homeBot1",
             {
                 {"positionXZ", {bot1Pos[X_POSITION], bot1Pos[Z_POSITION]}},
                 {"rotationY", bot1Pos[ROTATION]},
                 {"dribbler", bot1BallControl[DRIBBLER]},
                 {"kick", bot1BallControl[KICK]},
                 {"chirp", bot1BallControl[CHIRP]}
             }},
         {   "homeBot2",
             {
                 {"positionXZ", {bot2Pos[X_POSITION], bot2Pos[Z_POSITION]}},
                 {"rotationY", bot2Pos[ROTATION]},
                 {"dribbler", bot2BallControl[DRIBBLER]},
                 {"kick", bot2BallControl[KICK]},
                 {"chirp", bot2BallControl[CHIRP]}
             },
         }}},
    };

    cout << sampleMessage.dump() << endl;

    cerr << sampleMessage.dump(4) << endl;
}

int main(int argc, char *argv[])
{
    bool isRunning = false;
    uint32_t time = 0;

    HomeBot *homeBot1 = new HomeBot(-0.645f, 0.39f, 0.0f);
    HomeBot *homeBot2 = new HomeBot(-0.645f, -0.39f, 0.0f);

    while (true)
    {
        try
        {
            string line;
            getline(cin, line);

            json message = json::parse(line);
            string type = message["type"];
            if (type == "start")
                isRunning = true;
            else if (type == "stop")
                isRunning = false;
            else if (type == "state")
            {
                if (isRunning)
                {
                    // Moves robot every two seconds
                    if (time == 0)
                    {
                        homeBot1->setPosition(-0.645f, 0.39f, 90 * DEG_TO_RAD);
                        homeBot2->setPosition(-0.645f, -0.39f, 0.0f);
                    }   
                    else if (time == 40)
                    {
                        homeBot1->setPosition(0, 0, 110 * DEG_TO_RAD);
                        // dribbler
                        homeBot1->setBallControl(1, 0, 0);
                    }

                    time++;
                    if (time >= 80)
                        time = 0;

                    poseHomeBots(homeBot1, homeBot2);
                }
            }
        }
        catch (exception &error)
        {
            cerr << error.what() << endl;
        }
    }

    delete homeBot1, homeBot2;
}
