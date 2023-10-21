#include "normal.h"
#include <QDebug>
normal::normal()
{

}

normal::normal(int fila, int columna) : estacion(fila,columna)
{
    this->tipo = "Normal";
}

bool normal::estacionColapsada(){
    vector<pair<int, int>> puntosConexion = this->getPuntosEntradaSalida();
    if (puntosConexion.size() > 2) {
        qDebug() << "Error: Hay más de 2 puntos de conexión";
        return true;
    }

    return false;
}

