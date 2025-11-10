/**
 * @file calculations.cpp
 * @brief Implementación de utilidades geométricas (ángulos, distancia, límites).
 *
 * Comentarios en español para Doxygen. Se preservan los comentarios ya existentes.
 */

#include "calculations.h"
#include <cmath>
#include <iostream>
#include "config.h"

/**
 * @brief Calcula el ángulo de orientación desde origin hacia destiny (usa atan2).
 * @param origin Coordenadas de origen.
 * @param destiny Coordenadas destino.
 * @return float Ángulo en radianes.
 */
float getAngle(Coords origin, Coords destiny) {
	float dx = destiny.z - origin.z; // Tomando el tablero como un plano con el eje X horizontal
	float dy = destiny.x - origin.x; // y el eje Y vertical.

	float angle = atan2(dy, dx) + PI;

	return angle;
}

/**
 * @brief Comprueba si dos posiciones están dentro de un umbral (proximidad).
 * @param origin Punto de referencia.
 * @param destiny Punto destino.
 * @param threshold Umbral de proximidad.
 * @return int 1 si está dentro del umbral, 0 si no.
 */
int proximityCheck(Coords origin, Coords destiny, float threshold) {
	
	float dX = ABS(destiny.x - origin.x), dY = ABS(destiny.y - origin.y);
	
	if (dX <= threshold && dY <= threshold) {
		return 1;
	}
	else {
		return 0;
	}
}

/**
 * @brief Verifica si una posición está fuera de los límites del campo o en el área.
 * @param position Posición a evaluar.
 * @return int 1 si está fuera o en área prohibida, 0 en caso contrario.
 */
int offLimitsCheck(Coords position) {
	if (position.z < X_MIN || position.z > X_MAX || position.x < Y_MIN || position.x > Y_MAX) {
		return 1;
	}
	else if((position.x <= Y_MIN + AREA_LENGTH || position.x >= Y_MAX - AREA_LENGTH) && ABS(position.z) <= AREA_WIDTH/2) {
		return 1;
	}
	else {
		return 0;
	}
}

/**
 * @brief Calcula la distancia euclidiana en el plano XZ entre origin y destiny.
 * @param origin Punto origen.
 * @param destiny Punto destino.
 * @return float Distancia calculada.
 */
float getDistance(Coords origin, Coords destiny) {
	float dX = destiny.x - origin.x;
	float dZ = destiny.z - origin.z;
	return sqrt(dX * dX + dZ * dZ);
}
