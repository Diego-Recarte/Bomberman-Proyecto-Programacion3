#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H


#include "MapaYCasillas/mapa.h"
#include "Bombas/colabomba.h"
#include "Bombas/sistemaexplosion.h"
#include "Jugador/jugador.h"
#include "Enemigos/gestorenemigos.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>

class QGraphicsTextItem;

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
    GestorEnemigos enemigos;
    SistemaExplosion sistemaExplosion;
    void actualizarBombas();

    enum class EstadoPartida {
        EnCurso,
        Derrota,
        Victoria
    };

    EstadoPartida estadoPartida = EstadoPartida::EnCurso;
    QGraphicsRectItem* barraVidaFondo = nullptr;
    QGraphicsRectItem* barraVida = nullptr;
    QGraphicsTextItem* textoVida = nullptr;
    QGraphicsTextItem* textoResultado = nullptr;

    void crearInterfaz();
    void actualizarPartida();
    void actualizarInterfazVida();
    void finalizarPartida(bool victoria);

};

#endif // VENTANAJUEGO_H
