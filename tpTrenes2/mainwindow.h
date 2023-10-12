// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "juego.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    juego miJuego;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


};

#endif // MAINWINDOW_H
