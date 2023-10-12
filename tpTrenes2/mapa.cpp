// mapa.cpp
#include "mapa.h"
#include "estacion.h"
#include "horizontal.h"
#include "multi.h"
#include "normal.h"
#include "vertical.h"

Mapa::Mapa()
{

}

Mapa::Mapa(int filas, int columnas) : filas(filas), columnas(columnas) {
    crearMatrizDeBotones(filas, columnas); // Crea y muestra el mapa en la interfaz de usuario
    agregarEstacionAleatoria();
    agregarEstacionAleatoria();
}

void Mapa::crearMatrizDeBotones(int filas, int columnas) {
    botones = new QPushButton**[filas];
    QGridLayout* mapaLayout = new QGridLayout; // Crea un nuevo layout

    for (int i = 0; i < filas; i++) {
        botones[i] = new QPushButton*[columnas];
        for (int j = 0; j < columnas; j++) {
            botones[i][j] = new QPushButton(" . ");
            mapaLayout->addWidget(botones[i][j], i, j); // Agrega el botón al layout directamente
            QObject::connect(this->botones[i][j], &QPushButton::clicked, [=]() { botonClickeado(i, j); });
        }
    }

    // Establece el nuevo layout para el mapa
    setLayout(mapaLayout);
}

void Mapa::botonClickeado(int fila, int columna)
{
    QPushButton* botonClickeado = botones[fila][columna];
    botonClickeado->setText(" - ");
}

void Mapa::agregarEstacionAleatoria() {
    srand(time(nullptr)); // Initialize random seed
    int cant = 15;
    int filaAleatoria, columnaAleatoria;
    bool posicionOcupada;

    do {
        filaAleatoria = rand() % cant;
        columnaAleatoria = rand() % cant;
        posicionOcupada = hayEstacionEnPosicion(filaAleatoria, columnaAleatoria) /*|| estaEnRutaEstablecida(filaAleatoria, columnaAleatoria)*/;
    } while (posicionOcupada);

    // Generar un número aleatorio para elegir el tipo de estación (0, 1, 2, 3)
    int tipoEstacion = rand() % 4;

    // Declarar un puntero a la clase base Estacion
    estacion* estacionAleatoria = nullptr;

    // Crear una instancia de la estación correspondiente al tipo aleatorio
    switch (tipoEstacion) {
        case 0:
            estacionAleatoria = new horizontal(filaAleatoria, columnaAleatoria);
            break;
        case 1:
            estacionAleatoria = new multi(filaAleatoria, columnaAleatoria);
            break;
        case 2:
            estacionAleatoria = new normal(filaAleatoria, columnaAleatoria);
            break;
        case 3:
            estacionAleatoria = new vertical(filaAleatoria, columnaAleatoria);
            break;
        default:
            cout << "Tipo de estación no válido." << endl;
            break;
    }

    //cambia el texto del boton, mostrando el nombre de la estacion creada
    botones[filaAleatoria][columnaAleatoria]->setText(QString::fromStdString(estacionAleatoria->getTipo()));

    estaciones.push_back(estacionAleatoria);
}

bool Mapa::hayEstacionEnPosicion(int fila, int columna) {
    for (estacion* estacion : estaciones) {
        if (estacion->getFila() == fila && estacion->getColumna() == columna) {
            return true;
        }
    }
    return false;
}








