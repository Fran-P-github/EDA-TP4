#include "calculations.h"
#include <cmath>

float getAngle(Coords origin, Coords destiny) {
	
	float dX = ABS(destiny.x - origin.x), dY = ABS(destiny.y - origin.y);
	
	// Avoid division by zero.
	if (!dX) {
		if (dY >= 0) {
			return PI / 2;
		}
		else return 3 * PI / 2;
	}

	float angleVal = atan(dY / dX);
	float result;
	if (destiny.y >= origin.y && destiny.x >= origin.x) {
		result = angleVal;
	}
	else if (destiny.y >= origin.y && destiny.x <= origin.x) {
		result = PI - angleVal;
	}
	else if (destiny.y <= origin.y && destiny.x <= origin.x) {
		result = PI + angleVal;
	}
	else {
		result = 2 * PI - angleVal;
	}
	return result;
}

