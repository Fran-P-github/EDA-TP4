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
};

typedef struct GameState {
    Bot rivalBot1;
    Bot rivalBot2;
    HomeBot homeBot1;
    HomeBot homeBot2;
    Ball ball;
    unsigned homeScore;
    unsigned rivalScore;
    bool playing;
    uint32_t time;
};

class Entity {
public:
    Entity(Coords initCoords, Velocity initVelocity, Rotation initRot, AngularVelocity initAV);
    Coords getPosition();
    Velocity getVelocity();
    Rotation getRotation();
    AngularVelocity getAV();
    void setPosition(Coords newCoords);
    void setVelocity(Velocity newVelocity);
    void setRotation(Rotation newRoation);
    void setAV(AngularVelocity newAV);
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

private:
    Actions actions;
};