#include "normal.h"

normal::normal()
{

}

normal::normal(int fila, int columna) : estacion(fila,columna)
{
    this->tipo = "Normal";
}

void normal::estacionColapsada(){
    if(this->getCantConexiones() > 1){
        this->colapsada = true;
    }
}
