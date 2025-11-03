#include <exception>
#include <cmath>
#include <iostream>
#include <string>
#include "game.h"
#include "calculations.h"

#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

void poseHomeBots(HomeBot *homeBot1, HomeBot *homeBot2);

void poseHomeBots(HomeBot *homeBot1, HomeBot *homeBot2)
{
    Coords bot1Pos = homeBot1->getPosition(), bot2Pos = homeBot2->getPosition();
    float rot1 = homeBot1->getRotation().rotY;
    float rot2 = homeBot2->getRotation().rotY;
    Actions bot1BallControl = homeBot1->getBallControl(), bot2BallControl = homeBot2->getBallControl();

    json sampleMessage = {
        {"type", "set"},
        {"data",
         {{
             "homeBot1",
             {
                 {"positionXZ", {bot1Pos.x, bot1Pos.z}},
                 {"rotationY", rot1},
                 {"dribbler", bot1BallControl.dribbler},
                 {"kick", bot1BallControl.kicker},
                 {"chirp", bot1BallControl.chipper}
             }},
         {   "homeBot2",
             {
                 {"positionXZ", {bot2Pos.x, bot2Pos.z}},
                 {"rotationY", rot2},
                 {"dribbler", bot2BallControl.dribbler},
                 {"kick", bot2BallControl.kicker},
                 {"chirp", bot2BallControl.chipper }
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
    float position = -0.645f;
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
                    /*Coords currentPos = homeBot1->getPosition();
                    Coords currentPos2 = homeBot2->getPosition();
                    float angle = getAngle(currentPos, homeBot2->getPosition());
                    homeBot1->setPosition(currentPos.x, currentPos.z, angle);
                    homeBot2->setPosition(currentPos2.x + .1f, currentPos2.z, 0.0f);
                    poseHomeBots(homeBot1, homeBot2);*/
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
