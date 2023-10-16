// mapa.cpp
#include "mapa.h"
#include "estacion.h"
#include "horizontal.h"
#include "multi.h"
#include "normal.h"
#include "qapplication.h"
#include "vertical.h"
#include <QMessageBox>
#include <vector>
#include <iostream>

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
    mapaLayout = new QGridLayout; // Crea un nuevo layout

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
    if (!conectandoEstaciones) {
        // Verificar si el botón clickeado representa una estación
        bool esEstacionObjetivo = false;
        for (estacion* estacion : estaciones) {
            if (fila == estacion->getFila() && columna == estacion->getColumna()) {
                //El botón clickeado representa una estación
                inicioFila = fila;
                inicioColumna = columna;
                conectandoEstaciones = true;
                this->rutaEnConstruccion = new ruta;
                this->rutaEnConstruccion->setEstacionInicio(estacion);
                esEstacionObjetivo = true;
                ultimoPuntoFila = fila;
                ultimoPuntoColumna = columna;
                qDebug() << "Iniciando creación de ruta desde: (" << inicioFila << "," << inicioColumna << ")";
                break;
            }
        }
        if (!esEstacionObjetivo) {
            qDebug() << "Error: Debes comenzar la ruta desde una estación.";
        }
    } else {
        //verificamos si se oprimio un boton adyecente
        if (esAdyacente(ultimoPuntoFila, ultimoPuntoColumna, fila, columna)) {
            // Verificar si el punto es una estación objetivo
            for (estacion* estacion : estaciones) {
                if (fila == estacion->getFila() && columna == estacion->getColumna()) {
                    qDebug() << "Ruta terminada en: (" << fila << "," << columna << ")";
                    this->rutaEnConstruccion->setEstacionFinal(estacion);
                    botonEstacionObjetivoClickeado(fila, columna);
                    return;
                }
            }
            //si no es una estacion objetivo, se guarda en rutaEnContruccion
            QPushButton* botonClickeado = botones[fila][columna];
            botonClickeado->setText(" --- ");
            // Nos fijamos si chocan los caminos, si choca pierde el juego
            if(cruceDeCaminos(fila, columna)){
                QMessageBox::critical(this, "Game Over", "¡Trataste de usar una ruta ya usada!");
                QCoreApplication::quit();
            }
            this->rutaEnConstruccion->camino.push_back(make_pair(fila, columna));
        }else{
            //Si el usuario se confunde y aprieta mal, la ruta se borra y puede seguir jugando.
            QMessageBox::critical(this, "Error", "Debes seguir una ruta adyacente. Creación de ruta cancelada.");
            for (int i = 0; i < this->rutaEnConstruccion->camino.size(); i++) {
                int fila = this->rutaEnConstruccion->camino[i].first;
                int columna = this->rutaEnConstruccion->camino[i].second;
                if (fila == inicioFila && columna == inicioColumna) {
                    QPushButton* botonClickeadoInicio = botones[inicioFila][inicioColumna];
                    botonClickeadoInicio->setText(encontrarEstacionPorPosicion(inicioFila, inicioColumna)->getTipo());
                } else {
                    botones[fila][columna]->setText(" . ");
                }
            }
            conectandoEstaciones = false;
            this->rutaEnConstruccion->camino.clear();
        }
        // Actualiza las variables del último punto oprimido
        ultimoPuntoFila = fila;
        ultimoPuntoColumna = columna;
    }

}
void Mapa::botonEstacionObjetivoClickeado(int fila, int columna)
{
    if (conectandoEstaciones) {
        // Finalizar la creación de ruta
        conectandoEstaciones = false;

        // Obtén el primer punto y el último punto de la ruta en construcción
        pair<int, int> puntoConexionUno = rutaEnConstruccion->camino.front();
        pair<int, int> puntoConexionDos = rutaEnConstruccion->camino.back();

        // Obtener las estaciones de origen y destino
        estacion* estacionOrigen = encontrarEstacionPorPosicion(inicioFila, inicioColumna);
        estacion* estacionDestino = encontrarEstacionPorPosicion(fila, columna);

        // Establece los puntos de entrada y salida en las estaciones
        estacionOrigen->agregarPuntoEntradaSalida(puntoConexionUno);
        estacionDestino->agregarPuntoEntradaSalida(puntoConexionDos);

        // Realizar comprobación y mostrar errores si corresponde
        if (estacionOrigen->estacionColapsada() || estacionDestino->estacionColapsada()) {
            QMessageBox::critical(this, "Game Over", "¡Has perdido el juego por no seguir las reglas!");
            QCoreApplication::quit();
        }

        // Crear una copia de la ruta en construcción y la establece como ruta valida
        ruta* nuevaRuta = new ruta(*rutaEnConstruccion);
        rutasValidas.push_back(nuevaRuta);


        // Restaurar los textos de los botones
        for (int i = 0; i < this->rutaEnConstruccion->camino.size(); i++) {
            int fila = this->rutaEnConstruccion->camino[i].first;
            int columna = this->rutaEnConstruccion->camino[i].second;
            botones[fila][columna]->setText("Ruta");
        }

        qDebug() << "Ruta conectada correctamente.";
        agregarEstacionAleatoria();
        agregarEstacionAleatoria();
    } else {
        qDebug() << "Error: La ruta no es válida.";
    }
    this->rutaEnConstruccion->camino.clear(); // Limpia la ruta en construcción para una nueva creación
    emit botonEstacionObjetivoClickeadoSignal();
}

estacion* Mapa::encontrarEstacionPorPosicion(int fila, int columna)
{
    for (estacion* estacion : estaciones) {
        if (estacion->getFila() == fila && estacion->getColumna() == columna) {
            return estacion;
        }
    }
}

bool Mapa::cruceDeCaminos(int fila, int columna) {
    for (ruta* rutaValida : rutasValidas) {
        for (pair<int, int>& punto : rutaValida->camino) {
            if (punto.first == fila && punto.second == columna) {
                return true;
            }
        }
    }
    return false;
}


void Mapa::agregarEstacionAleatoria() {
    srand(time(nullptr)); // Initialize random seed
    int cant = 15;
    int filaAleatoria, columnaAleatoria;
    bool posicionOcupada;

    do {
        filaAleatoria = rand() % cant;
        columnaAleatoria = rand() % cant;
        posicionOcupada = hayEstacionEnPosicion(filaAleatoria, columnaAleatoria) || cruceDeCaminos(filaAleatoria, columnaAleatoria);
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

bool Mapa::esAdyacente(int fila1, int columna1, int fila2, int columna2)
{
    int distanciaFila = abs(fila1 - fila2);
    int distanciaColumna = abs(columna1 - columna2);
    return (distanciaFila == 1 && distanciaColumna == 0) || (distanciaFila == 0 && distanciaColumna == 1);
}






