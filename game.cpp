#include "game.h"
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

Ball::Ball() : Entity(Coords{ 0, 0, 0 }, Velocity{ 0, 0, 0 }, Rotation{ 0, 0, 0 }, AngularVelocity{ 0, 0, 0 }) {}

Bot::Bot(float xInitial, float zInitial, float InitialRot)
    : Entity(Coords{ xInitial, 0, zInitial }, Velocity{ 0, 0, 0 }, Rotation{ 0, InitialRot, 0 }, AngularVelocity{ 0, 0, 0 }) {}

HomeBot::HomeBot(float xInitial, float zInitial, float InitialRot) : Bot(xInitial, zInitial, InitialRot), actions(Actions{ 0,0,0 }) {}

Actions HomeBot::getBallControl() {
    return actions;
}

void HomeBot::setBallControl(float dribblerValue, float kickValue, float chirpValue) {
    actions.dribbler = dribblerValue;
    actions.kicker = kickValue;
    actions.chipper = chirpValue;
}

void HomeBot::setPosition(float xValue, float zValue, float rotationValue) {
    coords.x = xValue;
    coords.z = zValue;
    rotation.rotY = rotationValue;
}
