#include "vertical.h"

vertical::vertical()
{

}

vertical::vertical(int fila, int columna) : estacion(fila,columna)
{
    this->tipo = "Vertical";
}

void vertical::estacionColapsada(){
    if(this->getCantConexiones() > 1){
        this->colapsada = true;
    }
}
