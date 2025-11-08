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
    coords.x = newCoords.x;
    coords.y = newCoords.y;
    coords.z = newCoords.z;
}

void Entity::setVelocity(Velocity newVelocity) {
    velocity.vx = newVelocity.vx;
    velocity.vy = newVelocity.vy;
    velocity.vz = newVelocity.vz;
}

void Entity::setRotation(Rotation newRotation) {
    rotation.rotX = newRotation.rotX;
    rotation.rotY = newRotation.rotY;
    rotation.rotZ = newRotation.rotZ;
}

void Entity::setAV(AngularVelocity newAV) {
    av.avX = newAV.avX;
    av.avY = newAV.avY;
    av.avZ = newAV.avZ;
}

Ball::Ball() : Entity(Coords{ 0, 0, 0 }, Velocity{ 0, 0, 0 }, Rotation{ 0, 0, 0 }, AngularVelocity{ 0, 0, 0 }) {}

Bot::Bot(float xInitial, float zInitial, float InitialRot)
    : Entity(Coords{ xInitial, 0, zInitial }, Velocity{ 0, 0, 0 }, Rotation{ 0, InitialRot, 0 }, AngularVelocity{ 0, 0, 0 }) {}

HomeBot::HomeBot(float xInitial, float zInitial, float InitialRot) :
    Bot(xInitial, zInitial, InitialRot), actions(Actions{ 0,0,0 }), role(BotRole::NONE) {}

Actions HomeBot::getBallControl() {
    return actions;
}

void HomeBot::setBallControl(float dribblerValue, float kickValue, float chirpValue) {
    actions.dribbler = dribblerValue;
    actions.kicker = kickValue;
    actions.chipper = chirpValue;
}

BotRole HomeBot::getRole() {
    return role;
}

void HomeBot::setRole(BotRole newRole) {
    role = newRole;
}