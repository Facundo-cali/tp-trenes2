#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mapa = new Mapa(15, 15);
    setCentralWidget(mapa);

}

MainWindow::~MainWindow()
{
    delete ui;
}

