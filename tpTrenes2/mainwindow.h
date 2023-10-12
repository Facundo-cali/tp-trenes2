// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mapa.h"
#include "ui_mainwindow.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    Mapa* mapa; // Agrega una instancia de la clase Mapa u otras clases necesarias
    // Otros miembros y propiedades privadas
};

#endif // MAINWINDOW_H
