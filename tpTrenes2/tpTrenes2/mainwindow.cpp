#include "mainwindow.h"
#include "juego.h"
#include "ui_mainwindow.h"
#include <QInputDialog>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    juego miJuego;

    // Solicitar al usuario la cantidad de filas
    bool ok;
    int filas = QInputDialog::getInt(this, "Ingrese la cantidad de filas", "Filas:", 15, 1, 100, 1, &ok);
    if (!ok) {
        // El usuario canceló la entrada
        return;
    }
    // Solicitar al usuario la cantidad de columnas
    int columnas = QInputDialog::getInt(this, "Ingrese la cantidad de columnas", "Columnas:", 15, 1, 100, 1, &ok);
    if (!ok) {
        // El usuario canceló la entrada
        return;
    }


    // Crear una instancia de juego y configurar el mapa con las filas y columnas especificadas
    miJuego.configurarMapa(filas, columnas);

    // Establecer el mapa como el widget central en la ventana principal
    setCentralWidget((miJuego.mapa));

}

MainWindow::~MainWindow()
{
    delete ui;
}


