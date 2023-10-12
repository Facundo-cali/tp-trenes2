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

int estacion::getCantConexiones() {
    return cantConexiones;
}

void estacion::incrementarConexiones() {
    cantConexiones+=1;
}

string estacion::getTipo()
{
    return this->tipo;
}
