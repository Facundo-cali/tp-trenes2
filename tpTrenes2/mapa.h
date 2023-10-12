// mapa.h
#ifndef MAPA_H
#define MAPA_H

#include "estacion.h"
#include "ruta.h"
#include <QGridLayout>
#include <QPushButton>

class Mapa : public QWidget {
    Q_OBJECT
private:
    int filas;
    int columnas;
    QPushButton*** botones;
    vector<estacion*> estaciones;
    vector<ruta*> rutasValidas;
    vector<pair<int, int>> rutaEnConstruccion;// Vector para almacenar rutas en construccion.

public:
    Mapa();
    Mapa(int filas, int columnas);
    void crearMatrizDeBotones(int filas, int columnas);
    void botonClickeado(int fila, int columna);
    void agregarEstacionAleatoria();
    bool hayEstacionEnPosicion(int fila, int columna);


    //gestion de creacion de rutas
    int inicioFila;
    int inicioColumna;
    bool conectandoEstaciones;
    bool esAdyacente(int fila1, int columna1, int fila2, int columna2);
    void botonEstacionObjetivoClickeado(int fila, int columna);
    estacion *encontrarEstacionPorPosicion(int fila, int columna);
};

#endif // MAPA_H
