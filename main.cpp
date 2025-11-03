#include <exception>
#include <cmath>
#include <iostream>
#include <string>
#include "game.h"
#include "calculations.h"
#include "comm.h"
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

int main(int argc, char *argv[])
{
    GameState game = {
        .rivalBot1 = Bot(1.0, 1.0, 1.0),
        .rivalBot2 = Bot(2.0, 1.0, 1.0),
        .homeBot1 = HomeBot(- 0.645f, 0.39f, 0.0f),
        .homeBot2 = HomeBot(-0.645f, -0.39f, 0.0f),
        .ball = Ball(),
        .homeScore = 0,
        .rivalScore = 0,
        .playing = false,
        .time = 0,
    };

    Comm comm;

    while (true)
    {
        try
        {
            bool mustReply = comm.updateGame(game);
            if (game.playing && mustReply)
            {
                /*Coords currentPos = homeBot1->getPosition();
                Coords currentPos2 = homeBot2->getPosition();
                float angle = getAngle(currentPos, homeBot2->getPosition());
                homeBot1->setPosition(currentPos.x, currentPos.z, angle);
                homeBot2->setPosition(currentPos2.x + .1f, currentPos2.z, 0.0f);
                poseHomeBots(homeBot1, homeBot2);*/
            }
        }
        catch (exception &error)
        {
            cerr << error.what() << endl;
        }
    }
}
