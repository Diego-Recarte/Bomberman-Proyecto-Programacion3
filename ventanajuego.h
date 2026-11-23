#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H


#include "MapaYCasillas/mapa.h"
#include "Bombas/colabomba.h"
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
    void actualizarBombas();

    void crearExplosion(int x, int y, int tamanoCelda,int alcance);
    // El jugador se crea dentro del constructor; no existe aún al inicializar miembros.
    int tamanoJugador = 0;
    int tamanoFlama = 20;

     bool reaccionEnCadena( int filaFlama, int columnaBomba,int retraso);
};

#endif // VENTANAJUEGO_H
