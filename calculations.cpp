#include "calculations.h"
#include <cmath>
#include <iostream>
#include "config.h"


float getAngle(Coords origin, Coords destiny) {
	float dx = destiny.z - origin.z; // Tomando el tablero como un plano con el eje X horizontal
	float dy = destiny.x - origin.x; // y el eje Y vertical.

	float angle = atan2(dy, dx) + PI;

	return angle;
}

int proximityCheck(Coords origin, Coords destiny, float threshold) {
	
	float dX = ABS(destiny.x - origin.x), dY = ABS(destiny.y - origin.y);
	
	if (dX <= threshold && dY <= threshold) {
		return 1;
	}
	else {
		return 0;
	}
}

int offLimitsCheck(Coords position) {
	if (position.x < X_MIN || position.x > X_MAX || position.y < Y_MIN || position.y > Y_MAX || ABS(position.z) > MAX_HEIGHT) {
		return 1;
	}
	else {
		return 0;
	}
}

float defenderXCord(Coords position, Coords ball) {
	float defenderX;
	defenderX = (CENTER_X + ball.x) / 2.0F;
	return defenderX;
}

float getDistance(Coords origin, Coords destiny) {
	float dX = destiny.x - origin.x;
	float dZ = destiny.z - origin.z;
	return sqrt(dX * dX + dZ * dZ);
}
