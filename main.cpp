#include <exception>
#include <cmath>
#include <iostream>
#include <string>
#include "game.h"
#include "calculations.h"
#include "comm.h"
#include <nlohmann/json.hpp>

#define PI 3.1415926535F
#define DEG_TO_RAD (PI / 180.0F)

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
                // Moves robot every two seconds
                if (time == 0)
                {
                    // fill in
                }   
                else if (game.time == 40)
                {
                    // fill in
                }

                game.time++;
                if (game.time >= 80)
                    game.time = 0;
                comm.poseHomeBots(game.homeBot1, game.homeBot2);
            }
        }
        catch (exception &error)
        {
            cerr << error.what() << endl;
        }
    }
}
