#include "mainwindow.h"
#include "juego.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QTimer>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->timer = new QTimer(this);
    miJuego.configurarCrono(30);
    connect(this->timer, &QTimer::timeout, this, &MainWindow::ontimer);

    juego miJuego;

    // Crear una instancia de juego y configurar el mapa con las filas y columnas especificadas
    miJuego.configurarMapa(15, 15);

    // Agregar el mapa al diseño
    ui->mapagrid->addWidget(miJuego.mapa);
    connect(miJuego.mapa, &Mapa::botonEstacionObjetivoClickeadoSignal, this, &MainWindow::verificarBotonEstacionObjetivoClickeado);

    refresh();
    this->timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh()
{
    this->ui->lcdNumber->display(miJuego.cronometro->get_seg());
}


void MainWindow::ontimer()
{
    miJuego.cronometro->decrementar();
    if (miJuego.cronometroLlegoACero()) {
        // El tiempo se ha agotado, muestra un mensaje y se cierra
        QMessageBox::critical(this, "Game Over", "¡Tiempo agotado!");
        QCoreApplication::quit();
    }
    refresh();
}

void MainWindow::verificarBotonEstacionObjetivoClickeado() {
    // Realiza la verificación y acciones correspondientes
    miJuego.cronometro->reiniciar();
}

