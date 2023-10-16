#include "horizontal.h"

horizontal::horizontal()
{

}

horizontal::horizontal(int fila, int columna) : estacion(fila,columna)
{
    this->tipo = "Horizontal";
}

bool horizontal::estacionColapsada(){
    vector<pair<int, int>> puntosConexion = this->getPuntosEntradaSalida();
    if (puntosConexion.size() > 2) {
        // Error: Hay más de 2 puntos de conexion
        return true;
    }

    if (puntosConexion.size() == 2 && puntosConexion[0].first != puntosConexion[1].first) {
        // Error: Los puntos tienen diferentes filas
        return true;
    }

    if (puntosConexion.size() == 1) {
        if(puntosConexion[0].first != this->getFila()){
            //Error: No se respeto una conexion horizontal
            return true;
        }
    }

    if (puntosConexion.size() == 2) {
        if(puntosConexion[0].first != this->getColumna() || puntosConexion[1].first != this->getColumna()){
            //Error: No se respeto una conexion horizontal
            return true;
        }
    }


    return false;
}
