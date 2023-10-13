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
    juego miJuego;
    this->timer=new QTimer(this);
    this->cronometro=new tiempo(30);
    connect(this->timer, &QTimer::timeout, this, &MainWindow::ontimer);


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
    this->ui->lcdNumber->display(this->cronometro->get_seg());
}

bool MainWindow::terminado()
{
    if(this->cronometro->get_seg()==0){
        return true;
    }
    else{
        return false;
    }
}

void MainWindow::ontimer()
{
    this->cronometro->decrementar();
    refresh();
    if(terminado()){
        this->timer->stop();
        QMessageBox::critical(this,"Perdiste","Se termino el tiempo.");
    }
}

void MainWindow::verificarBotonEstacionObjetivoClickeado() {
    // Aquí puedes realizar la verificación o ejecutar acciones adicionales
    this->cronometro->reiniciar();
}

