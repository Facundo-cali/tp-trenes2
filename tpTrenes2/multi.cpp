#include "multi.h"

multi::multi()
{

}

multi::multi(int fila, int columna) : estacion(fila,columna)
{
    this->tipo = "Multiple";
}

bool multi::estacionColapsada(){
    return false;
}
