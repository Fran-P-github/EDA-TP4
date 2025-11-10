/**
 * @file calculations.h
 * @brief Funciones utilitarias geométricas y comprobaciones (ángulos, distancias, límites).
 *
 * Definiciones de constantes y prototipos para operaciones usadas por el algoritmo.
 */

#pragma once
#include "game.h"

#define PI 3.1415926535F
#define DEG_TO_RAD (PI / 180.0F)

#define ABS(x) ((x) >= 0 ? (x) : -(x))

/**
 * @brief Calcula el ángulo de orientación desde origin hacia destiny (radianes).
 * @param origin Coordenadas de origen.
 * @param destiny Coordenadas destino.
 * @return float Ángulo en radianes.
 */
float getAngle(Coords origin, Coords destiny);

/**
 * @brief Comprueba si dos posiciones están dentro de un umbral de proximidad.
 * @param origin Coordenada de referencia.
 * @param destiny Coordenada objetivo.
 * @param threshold Umbral máximo permitido.
 * @return int 1 si están dentro del umbral, 0 en caso contrario.
 */
int proximityCheck(Coords origin, Coords destiny, float threshold);

/**
 * @brief Comprueba si una posición está fuera de los límites del campo o en el área.
 * @param position Posición a comprobar.
 * @return int 1 si está fuera o en área restringida, 0 en caso contrario.
 */
int offLimitsCheck(Coords position);

/**
 * @brief Calcula la distancia euclidiana en el plano XZ entre dos puntos.
 * @param origin Punto origen.
 * @param destiny Punto destino.
 * @return float Distancia euclidiana.
 */
float getDistance(Coords origin, Coords destiny);