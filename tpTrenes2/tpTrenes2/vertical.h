#ifndef VERTICAL_H
#define VERTICAL_H


#include "estacion.h"
class vertical : public estacion
{
public:
    vertical();
    vertical(int fila, int columna);
    void estacionColapsada();
};


#endif // VERTICAL_H
