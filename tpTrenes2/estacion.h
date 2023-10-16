#ifndef ESTACION_H
#define ESTACION_H
#include <iostream>


using namespace std;
class estacion
{
private:
    int cantConexiones = 0;
protected:
    char* tipo;
    bool colapsada = false;
public:
    int fila;
    int columna;
    estacion();
    estacion(int fila, int columna);

    int getFila();
    int getColumna();
    int getCantConexiones();// Metodo para obtener la cantidad de conexiones.
    void incrementarConexiones();// Incrementar conexión.
    virtual void estacionColapsada() = 0;
    char *getTipo();
};

#endif // ESTACION_H
