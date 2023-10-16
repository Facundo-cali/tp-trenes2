#ifndef MULTI_H
#define MULTI_H


#include "estacion.h"
class multi : public estacion
{
private:

public:
    multi();
    multi(int fila, int columna);
    bool estacionColapsada();
};

#endif // MULTI_H
