#ifndef ESTACION_H
#define ESTACION_H
#include <iostream>
#include <vector>


using namespace std;
class estacion
{
private:
    int fila;
    int columna;
    vector<pair<int, int>> puntosEntradaSalida;// Vector para almacenar puntos de entrada y salida
protected:
    char* tipo;
public:
    estacion();
    estacion(int fila, int columna);

    int getFila();
    int getColumna();
    virtual bool estacionColapsada() = 0;
    char *getTipo();
    void agregarPuntoEntradaSalida(pair<int, int> punto);
    vector<pair<int, int> > getPuntosEntradaSalida();
};

#endif // ESTACION_H
