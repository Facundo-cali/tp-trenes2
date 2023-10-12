#ifndef JUEGO_H
#define JUEGO_H


#include "mapa.h"

class MainWindow; // Declaración previa para evitar ciclos de inclusión
class juego {
private:

public:
    Mapa* mapa; // Instancia de la clase Mapa
    juego();
    juego(int filas, int columnas);


    // Métodos para la lógica del juego
    // bool verificarObjetivoCompleto();
    void configurarMapa(int filas, int columnas);

};

#endif // JUEGO_H
