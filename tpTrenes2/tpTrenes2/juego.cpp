#include "juego.h"

juego::juego()
{
    mapa = nullptr;
}

void juego::configurarMapa(int filas, int columnas) {
    if (mapa != nullptr) {
        delete mapa;
    }
    mapa = new Mapa(filas, columnas);
}



