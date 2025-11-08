#include "calculations.h"
#include <cmath>
#include <iostream>
#include "config.h"



float xMin = -FIELD_WIDTH/2, float xMax = FIELD_WIDTH/2, float yMin = -FIELD_LENGTH/2, float yMax = FIELD_LENGTH/2;

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
	if (position.x < xMin || position.x > xMax || position.y < yMin || position.y > yMax || ABS(position.z) > maxHeight) {
		return 1;
	}
	else {
		return 0;
	}
}

float defenderXCord(Coords position, Coords ball) {
	float defenderX;
	defenderX = (centreX + ball.x) / 2.0F;
	return defenderX;
}

float getDistance(Coords origin, Coords destiny) {
	float dX = destiny.x - origin.x;
	float dY = destiny.y - origin.y;
	return sqrt(dX * dX + dY * dY);
}
