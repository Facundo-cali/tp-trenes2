#ifndef HORIZONTAL_H
#define HORIZONTAL_H


#include "estacion.h"
class horizontal :public estacion
{
public:
    horizontal();
    horizontal(int fila, int columna);
    void estacionColapsada();
};

#endif // HORIZONTAL_H
