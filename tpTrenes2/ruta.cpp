#include "ruta.h"

ruta::ruta()
{
    this->camino = vector<pair<int, int>>(); // Inicializa un vector vacío
    this->estacionFinal = nullptr; // Inicializa un puntero a estación como nullptr
    this->estacionInicio = nullptr; // Inicializa otro puntero a estación como nullptr
}

ruta::ruta(estacion *estacionInicio, estacion *estacionFinal, vector<pair<int, int> > &camino)
{
    this->estacionInicio = estacionInicio;
    this->estacionFinal = estacionFinal;
    this->camino = camino;
}


estacion *ruta::getEstacionFinal()
{
    return estacionFinal;
}

void ruta::setEstacionFinal(estacion *newEstacionFinal)
{
    estacionFinal = newEstacionFinal;
}

estacion *ruta::getEstacionInicio()
{
    return estacionInicio;
}

void ruta::setEstacionInicio(estacion *newEstacionInicio)
{
    estacionInicio = newEstacionInicio;
}



