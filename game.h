/**
 * @file game.h
 * @brief Definiciones de tipos y clases que representan el estado del juego y entidades.
 *
 * Contiene las estructuras Coords, Rotation, Velocity, Actions y las clases Entity, Ball, Bot y HomeBot.
 */

#pragma once

#include <stdint.h>

/**
 * @struct Coords
 * @brief Coordenadas del mundo (x, y, z). En este proyecto se usa el plano XZ para el terreno.
 */
typedef struct {
    float x;
    float y;
    float z;
} Coords;

/**
 * @struct Rotation
 * @brief Rotaciones (rotX, rotY, rotZ) en radianes.
 */
typedef struct {
    float rotX;
    float rotY;
    float rotZ;
} Rotation;

/**
 * @struct Velocity
 * @brief Componentes de velocidad lineal.
 */
typedef struct {
    float vx;
    float vy;
    float vz;
} Velocity;

/**
 * @struct AngularVelocity
 * @brief Componentes de velocidad angular.
 */
typedef struct {
    float avX;
    float avY;
    float avZ;
} AngularVelocity;

/**
 * @struct Actions
 * @brief Acciones de un HomeBot: dribbler, kicker y chipper (valores entre 0 y 1).
 */
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

/**
 * @class Ball
 * @brief Representa la pelota; sin métodos adicionales por ahora.
 */
class Ball : public Entity {
public:
    Ball();
};

/**
 * @class Bot
 * @brief Bot genérico con constructor que posiciona en (x,z) y rotación Y.
 */
class Bot : public Entity {
public:
    Bot(float xInitial, float zInitial, float InitialRot);
};

typedef Bot RivalBot;

/**
 * @class HomeBot
 * @brief Bot controlado por el equipo con acciones y rol.
 */
class HomeBot : public Bot {
public:
    HomeBot(float xInitial, float zInitial, float InitialRot);
    Actions getBallControl();
    void setBallControl(Actions newActions);
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

/**
 * @struct GameState
 * @brief Estado completo del juego usado por el algoritmo.
 */
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

