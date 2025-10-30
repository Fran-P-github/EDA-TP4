// EDACup example

#include <exception>
#include <cmath>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

#define PI = 3.1415926535F
#define DEG_TO_RAD (PI / 180.0F)

using namespace std;
using json = nlohmann::json;

void poseHomeBot1(float positionX, float positionZ, float rotationY, unsigned homeBotNum)
{
    string homebot = "homeBot" + to_string(homeBotNum);
    json sampleMessage = {
        {"type", "set"},
        {"data",
         {{
             homebot,
             {
                 {"positionXZ", {positionX, positionZ}},
                 {"rotationY", rotationY},
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
                    if (time == 0)// -0.5, 0.3
                        poseHomeBot1(0, 0, 0, 1);//135 * DEG_TO_RAD);
                    else if (time == 40) // -0.1, 0.3
                        poseHomeBot1(0, 0, 135, 1);//-135 * DEG_TO_RAD);
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
