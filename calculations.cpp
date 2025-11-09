#include "calculations.h"
#include <cmath>
#include <iostream>
#include "config.h"

// El de toda la vida -> el que se usa
// x -> z
// y -> x
// z -> y

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
	if (position.z < X_MIN || position.z > X_MAX || position.x < Y_MIN || position.x > Y_MAX || ABS(position.y) > MAX_HEIGHT) {
		return 1;
	}
	else if((position.x <= Y_MIN + GOAL_LENGTH || position.x >= Y_MAX - GOAL_LENGTH) && ABS(position.z) <= GOAL_WIDTH/2) {
		return 1;
	}
	else {
		return 0;
	}
}


float getDistance(Coords origin, Coords destiny) {
	float dX = destiny.x - origin.x;
	float dZ = destiny.z - origin.z;
	return sqrt(dX * dX + dZ * dZ);
}
