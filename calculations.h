#pragma once
#include "game.h"

#define PI 3.1415926535F
#define DEG_TO_RAD (PI / 180.0F)

#define ABS(x) ((x) >= 0 ? (x) : -(x))

float getAngle(Coords origin, Coords destiny);
int proximityCheck(Coords origin, Coords destiny, float threshold);
int offLimitsCheck(Coords position);
float defenderXCord(Coords position, Coords ball);
float getDistance(Coords origin, Coords destiny);