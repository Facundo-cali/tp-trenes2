// mapa.cpp
#include "mapa.h"
#include "estacion.h"
#include "horizontal.h"
#include "multi.h"
#include "normal.h"
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
                    rutaEnConstruccion.clear();
                    rutaEnConstruccion.push_back(make_pair(fila, columna));
                    esEstacionObjetivo = true;
                    qDebug() << "Iniciando creación de ruta desde: (" << inicioFila << "," << inicioColumna << ")";
                    break;
                }
            }

            if (!esEstacionObjetivo) {
                qDebug() << "Error: Debes comenzar la ruta desde una estación.";
            }

        } else {
            auto ultimoPunto = rutaEnConstruccion.back();//se usa para verificar si el usuario esta creando bien la ruta y no esta dando saltos
            int filaUltimoPunto = ultimoPunto.first;//se usa para verificar si el usuario esta creando bien la ruta y no esta dando saltos
            int columnaUltimoPunto = ultimoPunto.second;//se usa para verificar si el usuario esta creando bien la ruta y no esta dando saltos

            if (esAdyacente(filaUltimoPunto, columnaUltimoPunto, fila, columna)) {
                QPushButton* botonClickeado = botones[fila][columna];
                botonClickeado->setText(" --- ");
                // Agregar el clic a la ruta en construcción
                rutaEnConstruccion.push_back(make_pair(fila, columna));

                if (fila == inicioFila && columna == inicioColumna) {
                    // El jugador ha vuelto a hacer clic en la estación de inicio,
                    // lo cual indica que ha cancelado la ruta actual.
                    conectandoEstaciones = false;
                    rutaEnConstruccion.clear();
                    qDebug() << "Creación de ruta cancelada.";
                } else {
                    // Verificar si el botón clickeado representa una estación objetivo
                    for (estacion* estacion : estaciones) {
                        if (fila == estacion->getFila() && columna == estacion->getColumna()) {
                            // El botón clickeado representa una estación objetivo
                            botonEstacionObjetivoClickeado(fila, columna);
                            return;
                        }
                    }
                }
            } else {
                //si el usuario se confunde y apreta mal, la ruta se borra y puede seguir jugando.El tiempo no se reinicia
                qDebug() << "Error: Debes seleccionar un botón adyacente al último botón en la ruta.";
                QMessageBox::critical(this, "Error", "Debes seguir una ruta adyacente. Creación de ruta cancelada.");
                for (int i = 0; i < rutaEnConstruccion.size(); i++) {
                    int fila = rutaEnConstruccion[i].first;
                    int columna = rutaEnConstruccion[i].second;
                    if(fila == inicioFila && columna == inicioColumna){
                        QPushButton* botonClickeadoInicio = botones[inicioFila][inicioColumna];
                        botonClickeadoInicio->setText(encontrarEstacionPorPosicion(inicioFila,inicioColumna)->getTipo());
                    }else{
                        botones[fila][columna]->setText(" . ");
                    }
                }
                conectandoEstaciones = false;
                rutaEnConstruccion.clear();
                return;
            }
        }

}
void Mapa::botonEstacionObjetivoClickeado(int fila, int columna)
{
    if (conectandoEstaciones) {
        // Finalizar la creación de ruta
        conectandoEstaciones = false;

        // Obtener las estaciones de origen y destino
        estacion* estacionOrigen = encontrarEstacionPorPosicion(inicioFila, inicioColumna);
        estacion* estacionDestino = encontrarEstacionPorPosicion(fila, columna);

//         Verificar restricciones según el tipo de estación de origen
//        if (!verificarRestriccionesEstacion(estacionOrigen, estacionDestino, rutaEnConstruccion)) {
//            qDebug() << "Error: Fallo estacion .";
//            conectandoEstaciones = false;
//            rutaEnConstruccion.clear();
//            return;
//        }


//        PARA QUE NO SE ATRAVIESEN LAS RUTAS
//        for (const auto& punto : rutaEnConstruccion) {
//            if (estaEnRutaEstablecida(punto.first,punto.second)) {
//                // El botón clickeado representa una posición que coincide con una ruta válida
//                qDebug() << "Error: Este botón representa una ruta establecida.";
//                QMessageBox::critical(this, "Error", "Este botón representa una ruta establecida. Creación de ruta cancelada.");
//                conectandoEstaciones = false;
//                rutaEnConstruccion.clear();
//                return;
//            };
//        }

        // Incrementar conexiones de la estación de origen y estacion destino
        estacionOrigen->incrementarConexiones();
        estacionDestino->incrementarConexiones();


        // Crear un objeto de la clase Ruta y almacenarlo en una colección de rutas válidas
        ruta* nuevaRuta = new ruta(estacionOrigen, estacionDestino, rutaEnConstruccion);
        rutasValidas.push_back(nuevaRuta);


        for (int i = 0; i < rutaEnConstruccion.size(); i++) {
            int fila = rutaEnConstruccion[i].first;
            int columna = rutaEnConstruccion[i].second;
            botones[fila][columna]->setText("Ruta");
        }

        // Restaurar los textos de los botones de las estaciones
        this->botones[fila][columna]->setText(estacionDestino->getTipo());
        this->botones[inicioFila][inicioColumna]->setText(estacionOrigen->getTipo());

        qDebug() << "Ruta conectada correctamente.";
        agregarEstacionAleatoria();
        agregarEstacionAleatoria();
//        this->cronometro->reiniciar();//reinicio timer
    } else {
        qDebug() << "Error: La ruta no es válida.";
    }
    rutaEnConstruccion.clear(); // Limpia la ruta en construcción para una nueva creación
    emit botonEstacionObjetivoClickeadoSignal();
}

estacion* Mapa::encontrarEstacionPorPosicion(int fila, int columna)
{
    for (estacion* estacion : estaciones) {
        if (estacion->getFila() == fila && estacion->getColumna() == columna) {
            return estacion;
        }
    }
    throw runtime_error("Estación no encontrada para la posición dada.");
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


//Verifica si el usuario crea las rutas de manera correcta.
bool Mapa::esAdyacente(int fila1, int columna1, int fila2, int columna2)
{
    int distanciaFila = abs(fila1 - fila2);
    int distanciaColumna = abs(columna1 - columna2);
    return (distanciaFila == 1 && distanciaColumna == 0) || (distanciaFila == 0 && distanciaColumna == 1);
}






