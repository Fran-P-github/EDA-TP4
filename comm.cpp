#include "comm.h"
#include "algorithm.h"
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

void Comm::poseHomeBots(HomeBotPlan &hb1Plan, HomeBotPlan &hb2Plan)
{
    json sampleMessage = {
        {"type", "set"},
        {"data",
         {{
             "homeBot1",
             {
                 {"positionXZ", {hb1Plan.posXZ.x, hb1Plan.posXZ.z}},
                 {"rotationY", hb1Plan.rotY},
                 {"dribbler", hb1Plan.actions.dribbler},
                 {"kick", hb1Plan.actions.kicker},
                 {"chirp", hb1Plan.actions.chipper}
             }},
         {   "homeBot2",
             {
                 {"positionXZ", {hb2Plan.posXZ.x, hb2Plan.posXZ.z}},
                 {"rotationY", hb2Plan.rotY},
                 {"dribbler", hb2Plan.actions.dribbler},
                 {"kick", hb2Plan.actions.kicker},
                 {"chirp", hb2Plan.actions.chipper }
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
        TeamPlan plan = computeTeamPlan(game);
        HomeBotPlan hb1Plan = plan.hb1Plan;
        HomeBotPlan hb2Plan = plan.hb2Plan;
        poseHomeBots(hb1Plan, hb2Plan);
        mustReply = true;
    }
    return mustReply;
}