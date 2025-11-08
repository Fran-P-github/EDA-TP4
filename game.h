#pragma once

#include <stdint.h>

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

typedef struct {
    struct {
        float x;
        float z;
    } posXZ;
    float rotY;
    Actions actions;
} HomeBotPlan;

typedef struct {
    HomeBotPlan hb1Plan;
    HomeBotPlan hb2Plan;
} TeamPlan;

enum class BotRole {
    ATTACKER,
    DEFENDER,
    NONE
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
    BotRole getRole();
    void setRole(BotRole newRole);

private:
    Actions actions;
    BotRole role;
};

typedef enum {
    PLAYING,
    STOPPED,
    FOUL,
    RESET
} GameStatus;

typedef struct {
    RivalBot rivalBot1;
    RivalBot rivalBot2;
    HomeBot homeBot1;
    HomeBot homeBot2;
    Ball ball;
    unsigned homeScore;
    unsigned rivalScore;
    GameStatus status;
    uint32_t time;
} GameState;

