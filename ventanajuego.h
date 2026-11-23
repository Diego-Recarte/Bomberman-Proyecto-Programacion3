#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H


#include "MapaYCasillas/mapa.h"
#include "Bombas/colabomba.h"
#include "Bombas/sistemaexplosion.h"
#include "Jugador/jugador.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>

class VentanaJuego : public QGraphicsView
{
public:
    VentanaJuego();
     Mapa* mapa = nullptr;

protected:
    void keyPressEvent(QKeyEvent* evento) override; //KeyPress
    void keyReleaseEvent(QKeyEvent* evento) override;//KeyRelseEvent

private:

    ~VentanaJuego();

    Jugador* jugador = nullptr;
    QGraphicsScene* escena = nullptr;

    QTimer* temporizadorMovimiento = nullptr;

    void colocarBomba();


    void construirMapa();

    //bombas

    ColaBomba bombas;
    SistemaExplosion sistemaExplosion;
    void actualizarBombas();

};

#endif // VENTANAJUEGO_H
