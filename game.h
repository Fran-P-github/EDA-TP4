#pragma once

#include <vector>

typedef struct Coords {
    float x;
    float y;
    float z;
};

typedef struct Rotation {
    float rotX;
    float rotY;
    float rotZ;
};

typedef struct Velocity {
    float vx;
    float vy;
    float vz;
};

typedef struct AngularVelocity {
    float avX;
    float avY;
    float avZ;
};

typedef struct Actions {
    float dribbler;
    float kicker;
    float chipper;
};

typedef struct GameState {
    Bot rivalBot1;
    Bot rivalBot1;
    HomeBot homeBot1;
    HomeBot homeBot2;
    Ball ball;
    unsigned homeScore;
    unsigned rivalScore;
    bool playing;
};

class Entity {
public:
    Entity(Coords initCoords, Velocity initVelocity, Rotation initRot, AngularVelocity initAV);
    Coords getPosition();
    Velocity getVelocity();
    Rotation getRotation();
    AngularVelocity getAV();
protected:
    Coords coords;
    Velocity velocity;
    Rotation rotation;
    AngularVelocity av;
};

class Ball : public Entity {
public:
    Ball();
};

class Bot : public Entity {
public:
    Bot(float xInitial, float zInitial, float InitialRot);
};

typedef Bot RivalBot;

class HomeBot : public Bot {
public:
    HomeBot(float xInitial, float zInitial, float InitialRot);
    Actions getBallControl();
    void setBallControl(float dribblerValue, float kickValue, float chirpValue);
    void setPosition(float xValue, float zValue, float rotationValue);

private:
    Actions actions;
};