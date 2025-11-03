#pragma once

#include <vector>

typedef struct {
    float x;
    float y;
    float z;
} Coords;

typedef struct {
    float rotX;
    float rotY;
    float rotZ;
} Rotation;

typedef struct {
    float vx;
    float vy;
    float vz;
} Velocity;

typedef struct {
    float avX;
    float avY;
    float avZ;
} AngularVelocity;

typedef struct {
    float dribbler;
    float kicker;
    float chipper;
} Actions;

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
    Ball()
        : Entity(Coords{ 0, 0, 0 }, Velocity{ 0, 0, 0 }, Rotation{ 0, 0, 0 }, AngularVelocity{ 0, 0, 0 }) {
    }
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

typedef struct {
    Bot rivalBot1;
    Bot rivalBot2;
    HomeBot homeBot1;
    HomeBot homeBot2;
    Ball ball;
    unsigned homeScore;
    unsigned rivalScore;
    bool playing;
} GameState;