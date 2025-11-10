/**
 * @file main.cpp
 * @brief Punto de entrada: inicializa el estado del juego, el algoritmo y entra en el bucle principal.
 *
 * Documentado en español para Doxygen.
 */

#include <exception>
#include <iostream>
#include <string>
#include "game.h"
#include "calculations.h"
#include "comm.h"
#include "algorithm.h"
using namespace std;

/**
 * @brief Función principal que inicializa GameState, inicializa el algoritmo y procesa mensajes.
 */
int main(int argc, char *argv[])
{
    GameState game = {
        .rivalBot1 = Bot(1.0, 1.0, 1.0),
        .rivalBot2 = Bot(2.0, 1.0, 1.0),
        .homeBot1 = HomeBot(- 0.645f, 0.39f, 0.0f),
        .homeBot2 = HomeBot(-0.645f, -0.39f, 0.0f),
        .ball = Ball(),
        .homeScore = 0,
        .rivalScore = 0,
        .status = STOPPED,
        .time = 0,
    };
    algorithmInit(game);
    Comm comm;

    while (true)
    {
        try
        {
            comm.updateGame(game);
        }
        catch (exception &error)
        {
            cerr << error.what() << endl;
        }
    }
}
