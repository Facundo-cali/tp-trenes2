#include "multi.h"

multi::multi()
{

}

multi::multi(int fila, int columna) : estacion(fila,columna)
{
    this->tipo = "Multiple";
}

void multi::estacionColapsada()
{
    if(this->getCantConexiones() > 2){
        this->colapsada = true;
    }
}
