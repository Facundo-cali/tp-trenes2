// mapa.h
#ifndef MAPA_H
#define MAPA_H

#include "estacion.h"
#include <QGridLayout>
#include <QPushButton>

class Mapa : public QWidget {
    Q_OBJECT

public:
    Mapa();
    Mapa(int filas, int columnas);
    void crearMatrizDeBotones(int filas, int columnas);
    void botonClickeado(int fila, int columna);
    void agregarEstacionAleatoria();
    bool hayEstacionEnPosicion(int fila, int columna);

private:
    int filas;
    int columnas;
    QPushButton*** botones;
    vector<estacion*> estaciones;
};

#endif // MAPA_H
