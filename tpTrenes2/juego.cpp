#include "juego.h"
#include <QDebug>

juego::juego()
{
    mapa = nullptr;
    cronometro = new tiempo;
}

bool juego::cronometroLlegoACero()
{
    if (cronometro->get_seg() <= 0) {
        return true;
    }
    return false;
}

void juego::configurarMapa(int filas, int columnas) {
    if (mapa != nullptr) {
        delete mapa;
    }
    mapa = new Mapa(filas, columnas);
}

void juego::configurarCrono(int seg) {

    this->cronometro = new tiempo(seg);
}







