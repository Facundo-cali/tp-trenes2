#ifndef JUEGO_H
#define JUEGO_H


#include "mapa.h"
#include "tiempo.h"


class juego {
private:

public:
    Mapa* mapa; // Instancia de la clase Mapa
    tiempo* cronometro;
    juego();
    juego(int filas, int columnas);


    // Métodos para la lógica del juego
    // bool verificarObjetivoCompleto();
    // Agrega la declaración del método para verificar el cronómetro

    bool cronometroLlegoACero();
    void configurarMapa(int filas, int columnas);
    void configurarCrono(int seg);
};

#endif // JUEGO_H
