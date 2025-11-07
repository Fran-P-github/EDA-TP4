#include "comm.h"
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

void Comm::poseHomeBots(HomeBot &homeBot1, HomeBot &homeBot2)
{
    Coords bot1Pos = homeBot1.getPosition(), bot2Pos = homeBot2.getPosition();
    float rot1 = homeBot1.getRotation().rotY;
    float rot2 = homeBot2.getRotation().rotY;
    Actions bot1BallControl = homeBot1.getBallControl(), bot2BallControl = homeBot2.getBallControl();

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

bool Comm::updateGame(GameState &game) {
    string line;
    getline(cin, line);
    bool mustReply = false;
    json message = json::parse(line);
    string type = message["type"];
    if (type == "start") {
        game.status = PLAYING;
        mustReply = false;
    }
    else if (type == "stop") {
        game.status = STOPPED;
        mustReply = false;
    }
    else if (type == "state") {
        json data = message["data"];
        json hb1_data = data["homeBot1"];
        json hb2_data = data["homeBot2"];
        json rb1_data = data["rivalBot1"];
        json rb2_data = data["rivalBot2"];
        json ball_data = data["ball"];

        game.homeBot1.setPosition(Coords{
            (float)hb1_data["position"][0],
            (float)hb1_data["position"][1],
            (float)hb1_data["position"][2]});
        game.homeBot1.setRotation(Rotation{
            (float)hb1_data["rotation"][0],
            (float)hb1_data["rotation"][1],
            (float)hb1_data["rotation"][2] });
        game.homeBot1.setVelocity(Velocity{
            (float)hb1_data["velocity"][0],
            (float)hb1_data["velocity"][1],
            (float)hb1_data["velocity"][2] });
        game.homeBot1.setAV(AngularVelocity{
            (float)hb1_data["angularVelocity"][0],
            (float)hb1_data["angularVelocity"][1],
            (float)hb1_data["angularVelocity"][2] });

        game.homeBot2.setPosition(Coords{
            (float)hb2_data["position"][0],
            (float)hb2_data["position"][1],
            (float)hb2_data["position"][2] });
        game.homeBot2.setRotation(Rotation{
            (float)hb2_data["rotation"][0],
            (float)hb2_data["rotation"][1],
            (float)hb2_data["rotation"][2] });
        game.homeBot2.setVelocity(Velocity{
            (float)hb2_data["velocity"][0],
            (float)hb2_data["velocity"][1],
            (float)hb2_data["velocity"][2] });
        game.homeBot2.setAV(AngularVelocity{
            (float)hb2_data["angularVelocity"][0],
            (float)hb2_data["angularVelocity"][1],
            (float)hb2_data["angularVelocity"][2] });

        game.rivalBot1.setPosition(Coords{
            (float)rb1_data["position"][0],
            (float)rb1_data["position"][1],
            (float)rb1_data["position"][2] });
        game.rivalBot1.setRotation(Rotation{
            (float)rb1_data["rotation"][0],
            (float)rb1_data["rotation"][1],
            (float)rb1_data["rotation"][2] });
        game.rivalBot1.setVelocity(Velocity{
            (float)rb1_data["velocity"][0],
            (float)rb1_data["velocity"][1],
            (float)rb1_data["velocity"][2] });
        game.rivalBot1.setAV(AngularVelocity{
            (float)rb1_data["angularVelocity"][0],
            (float)rb1_data["angularVelocity"][1],
            (float)rb1_data["angularVelocity"][2] });

        game.rivalBot2.setPosition(Coords{
            (float)rb2_data["position"][0],
            (float)rb2_data["position"][1],
            (float)rb2_data["position"][2] });
        game.rivalBot2.setRotation(Rotation{
            (float)rb2_data["rotation"][0],
            (float)rb2_data["rotation"][1],
            (float)rb2_data["rotation"][2] });
        game.rivalBot2.setVelocity(Velocity{
            (float)rb2_data["velocity"][0],
            (float)rb2_data["velocity"][1],
            (float)rb2_data["velocity"][2] });
        game.rivalBot2.setAV(AngularVelocity{
            (float)rb2_data["angularVelocity"][0],
            (float)rb2_data["angularVelocity"][1],
            (float)rb2_data["angularVelocity"][2] });

        game.ball.setPosition(Coords{
            (float)ball_data["position"][0],
            (float)ball_data["position"][1],
            (float)ball_data["position"][2] });
        game.ball.setRotation(Rotation{
            (float)ball_data["rotation"][0],
            (float)ball_data["rotation"][1],
            (float)ball_data["rotation"][2] });
        game.ball.setVelocity(Velocity{
            (float)ball_data["velocity"][0],
            (float)ball_data["velocity"][1],
            (float)ball_data["velocity"][2] });
        game.ball.setAV(AngularVelocity{
            (float)ball_data["angularVelocity"][0],
            (float)ball_data["angularVelocity"][1],
            (float)ball_data["angularVelocity"][2] });

        mustReply = true;
    }
    return mustReply;
}