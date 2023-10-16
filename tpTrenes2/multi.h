#ifndef MULTI_H
#define MULTI_H


#include "estacion.h"
class multi : public estacion
{
private:

public:
    multi();
    multi(int fila, int columna);
    void estacionColapsada();
};

#endif // MULTI_H
