#include "calculations.h"
#include <cmath>
#include <iostream>

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

int offLimitsCheck(Coords position, float xMin, float xMax, float yMin, float yMax) {
	if (position.x < xMin || position.x > xMax || position.y < yMin || position.y > yMax) {
		return 1;
	}
	else {
		return 0;
	}
}


