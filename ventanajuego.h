#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H


#include "mapa.h"
#include "colabomba.h"
#include "Jugador.h"
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
    void keyPressEvent(QKeyEvent* evento) override; //KeyPress
    void keyReleaseEvent(QKeyEvent* evento) override;//KeyRelseEvent

private:

    ~VentanaJuego();

    void actualizarMovimiento();
    QGraphicsScene* escena = nullptr;


    QTimer* temporizadorMovimiento = nullptr;

    Jugador* jugador;

    void revisarItemsJugador();





    int tamanoJugador = 40;


    void colocarBomba();

    Mapa* mapa = nullptr;
    void construirMapa();


    //bombas


    void actualizarBombas();

    void crearExplosion(int x, int y, int tamanoCelda,int alcance);

    int tamanoFlama = 20;
    int tamanoItemAlcance =2;

     bool reaccionEnCadena( int filaFlama, int columnaBomba,int retraso);
};

#endif // VENTANAJUEGO_H
