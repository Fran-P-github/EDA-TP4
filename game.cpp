#include "game.h"

Entity::Entity(Coords initCoords, Velocity initVelocity, Rotation initRot, AngularVelocity initAV)
	: coords(initCoords), velocity(initVelocity), rotation(initRot), av(initAV) {}

Coords Entity::getPosition() {
    return coords;
}
Velocity Entity::getVelocity() {
    return velocity;
}
Rotation Entity::getRotation() {
    return rotation;
}
AngularVelocity Entity::getAV() {
    return av;
}

void Entity::setPosition(Coords newCoords) {
    coords = newCoords;
}

void Entity::setVelocity(Velocity newVelocity) {
    velocity = newVelocity;
}

void Entity::setRotation(Rotation newRotation) {
    rotation = newRotation;
}

void Entity::setAV(AngularVelocity newAV) {
    av = newAV;
}

Ball::Ball() : Entity(Coords{ 0, 0, 0 }, Velocity{ 0, 0, 0 }, Rotation{ 0, 0, 0 }, AngularVelocity{ 0, 0, 0 }) {}

Bot::Bot(float xInitial, float zInitial, float InitialRot)
    : Entity(Coords{ xInitial, 0, zInitial }, Velocity{ 0, 0, 0 }, Rotation{ 0, InitialRot, 0 }, AngularVelocity{ 0, 0, 0 }) {}

HomeBot::HomeBot(float xInitial, float zInitial, float InitialRot) :
    Bot(xInitial, zInitial, InitialRot), actions(Actions{ 0,0,0 }), role(BotRole::NONE) {}

Actions HomeBot::getBallControl() {
    return actions;
}

void HomeBot::setBallControl(Actions newActions) {
    actions = newActions;
}

BotRole HomeBot::getRole() {
    return role;
}

void HomeBot::setRole(BotRole newRole) {
    role = newRole;
}