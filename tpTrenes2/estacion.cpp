#include "estacion.h"


estacion::estacion()
{

}

estacion::estacion(int fila, int columna) {
    this->fila = fila;
    this->columna = columna;
}

int estacion::getFila() {
    return fila;
}

int estacion::getColumna() {
    return columna;
}

char* estacion::getTipo()
{
    return this->tipo;
}

void estacion::agregarPuntoEntradaSalida(pair<int, int> punto)
{
    puntosEntradaSalida.push_back(punto);
}

vector<pair<int, int>> estacion::getPuntosEntradaSalida()
{
    return puntosEntradaSalida;
}
