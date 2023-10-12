#include "horizontal.h"

horizontal::horizontal()
{

}

horizontal::horizontal(int fila, int columna) : estacion(fila,columna)
{
    this->tipo = "Horizontal";
}

void horizontal::estacionColapsada(){
    if(this->getCantConexiones() > 1){
        this->colapsada = true;
    }
}
