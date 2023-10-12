#include "ruta.h"

ruta::ruta()
{

}

ruta::ruta(estacion *estacionInicio, estacion *estacionFinal, vector<pair<int, int> > &camino)
{
    this->estacionInicio = estacionInicio;
    this->estacionFinal = estacionFinal;
    this->camino = camino;
}
