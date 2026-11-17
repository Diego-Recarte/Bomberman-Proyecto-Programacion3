#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H


#include "mapa.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>

class VentanaJuego : public QGraphicsView
{
public:
    VentanaJuego();


protected:
    void keyPressEvent(QKeyEvent* evento) override;
    void keyReleaseEvent(QKeyEvent* evento) override;

private:
    void actualizarMovimiento();
    QGraphicsScene* escena = nullptr;
    QGraphicsRectItem* personaje = nullptr;

    QTimer* temporizadorMovimiento = nullptr;


    QGraphicsRectItem* bomba = nullptr;


    enum class Direccion{
        Arriba,
        Abajo,
        Izquierda,
        Derecha,
        Null
    };
    Direccion direccion = Direccion::Null;



    int movimiento = 5;
    int tamanoJugador = 40;


    void colocarBomba();

    Mapa* mapa = nullptr;
    void construirMapa();


};

#endif // VENTANAJUEGO_H
