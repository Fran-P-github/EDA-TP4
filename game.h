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

class Ball : public Entity {
public:
    Ball()
        : Entity(Coords{ 0, 0, 0 }, Velocity{ 0, 0, 0 }, Rotation{ 0, 0, 0 }, AngularVelocity{ 0, 0, 0 }){}
};

class Entity {
public:
    Entity(Coords initCoords, Velocity initVelocity, Rotation initRot, AngularVelocity initAV)
        : coords(initCoords), velocity(initVelocity), rotation(initRot), av(initAV) {}
    Coords getPosition() {
        return coords;
    }
    Velocity getVelocity() {
        return velocity;
    }
    Rotation getRotation() {
        return rotation;
    }
    AngularVelocity getAV() {
        return av;
    }
protected:
    Coords coords;
    Velocity velocity;
    Rotation rotation;
    AngularVelocity av;
};

class Bot : public Entity {
public:
    Bot(float xInitial, float zInitial, float InitialRot)
        : Entity(Coords{xInitial, 0, zInitial}, Velocity{0, 0, 0}, Rotation{0, InitialRot, 0}, AngularVelocity{0, 0, 0}) { }
};

typedef Bot RivalBot;

class HomeBot : public Bot {
public:
    HomeBot(float xInitial, float zInitial, float InitialRot) 
        : Bot(xInitial, zInitial, InitialRot), actions(Actions{ 0,0,0 }) {}

    Actions getBallControl() {
        return actions;
    }

    void setBallControl(float dribblerValue, float kickValue, float chirpValue) {
        actions.dribbler = dribblerValue;
        actions.kicker = kickValue;
        actions.chipper = chirpValue;
    }

    void setPosition(float xValue, float zValue, float rotationValue) {
        coords.x = xValue;
        coords.z = zValue;
        rotation.rotY = rotationValue;
    }

private:
    Actions actions;
};