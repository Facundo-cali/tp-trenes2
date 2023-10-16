#ifndef RUTA_H
#define RUTA_H


#include "estacion.h"
#include <vector>
using namespace std;

class ruta{
    private:
        estacion* estacionInicio; // Estación de inicio de la ruta
        estacion* estacionFinal;  // Estación de destino de la ruta

    public:
        ruta();
        ruta(estacion* estacionInicio,estacion* estacionFinal,vector<pair<int, int>>& camino);

        // Métodos para gestionar el camino de la ruta

        vector<pair<int, int>> camino; // Lista de coordenadas que forman el camino
        estacion *getEstacionFinal();
        void setEstacionFinal(estacion *newEstacionFinal);
        estacion *getEstacionInicio();
        void setEstacionInicio(estacion *newEstacionInicio);
};

#endif // RUTA_H
