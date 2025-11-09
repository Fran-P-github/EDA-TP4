#include <exception>
#include <iostream>
#include <string>
#include "game.h"
#include "calculations.h"
#include "comm.h"

using namespace std;

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
        .status = STOPPED,
        .time = 0,
    };

    Comm comm;

    while (true)
    {
        try
        {
            bool mustReply = comm.updateGame(game);
            switch(game.status)
            {
                case PLAYING:
                    if (mustReply)
                        {
                            Coords currentPos = game.homeBot1.getPosition();
                            Coords currentPos2 = game.homeBot2.getPosition();

                            float angle = getAngle(currentPos, currentPos2);
                            Rotation newRot = game.homeBot1.getRotation();

                            game.homeBot1.setRotation({ newRot.rotX, angle, newRot.rotZ });
                            game.homeBot2.setPosition({ currentPos2.x + .1f, currentPos2.y, currentPos2.z });
                            
                            comm.poseHomeBots(game.homeBot1, game.homeBot2);
                        }
                    break;
                case STOPPED:
                    break;
                case FOUL:
                    break;
                case RESET:
                    break;
                default:
                    break;
            }
            
        }
        catch (exception &error)
        {
            cerr << error.what() << endl;
        }
    }
}
