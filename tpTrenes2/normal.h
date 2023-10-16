#ifndef NORMAL_H
#define NORMAL_H


#include "estacion.h"
class normal : public estacion
{
public:
    normal();
    normal(int fila, int columna);
    bool estacionColapsada();
};
#endif // NORMAL_H
