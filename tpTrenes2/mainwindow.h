// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "juego.h"
#include "tiempo.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    juego miJuego;
    tiempo* cronometro;
    QTimer* timer;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void verificarBotonEstacionObjetivoClickeado();
    //para el timer.
    void refresh();
    bool terminado();
    void ontimer();



};

#endif // MAINWINDOW_H
