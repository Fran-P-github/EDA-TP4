// EDACup example

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

void poseHomeBots(Position_t homeBot1Pos, Position_t homeBot2Pos);

void poseHomeBots(Position_t homeBot1Pos, Position_t homeBot2Pos)
{
    json sampleMessage = {
        {"type", "set"},
        {"data",
         {{
             "homeBot1",
             {
                 {"positionXZ", {homeBot1Pos[X_POSITION], homeBot1Pos[Z_POSITION]}},
                 {"rotationY", homeBot1Pos[ROTATION]},
             }},
         {   "homeBot2",
             {
                 {"positionXZ", {homeBot2Pos[X_POSITION], homeBot2Pos[Z_POSITION]}},
                 {"rotationY", homeBot2Pos[ROTATION]},
             },
         }}},
    };

    // cout connects to server
    cout << sampleMessage.dump() << endl;

    // cerr prints to debug console
    //cerr << "Updated homeBot1 pose." << endl;
    cerr << sampleMessage.dump(4) << endl;
}

int main(int argc, char *argv[])
{
    bool isRunning = false;
    uint32_t time = 0;

    while (true)
    {
        // Try-catch allows intercepting errors.
        // On error, the catch block is executed.
        try
        {
            string line;
            getline(cin, line);

            json message = json::parse(line);
            //cerr << "+Received data:" << endl;
            //cerr << message.dump(4) << endl;
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
                        poseHomeBots(
                            vector<float> { -0.3f, 0.0f, 90 * DEG_TO_RAD }, 
                            vector<float>{ -0.5f, 0.3f, 0.0f}
                        );
                    else if (time == 40)
                        poseHomeBots(
                            vector<float>{0, 0, 90 * DEG_TO_RAD},
                            vector<float>{-0.5f, 0.3f, 0.0f}
                        );
                    time++;
                    if (time >= 80)
                        time = 0;
                }
            }
        }
        catch (exception &error)
        {
            // cerr prints to debug console
            cerr << error.what() << endl;
        }
    }
}
