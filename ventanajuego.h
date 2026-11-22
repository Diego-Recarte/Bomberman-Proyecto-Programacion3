#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H


#include "MapaYCasillas/mapa.h"
#include "Bombas/colabomba.h"
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
    QGraphicsRectItem* personaje = nullptr;

    QTimer* temporizadorMovimiento = nullptr;





    enum class Direccion{//enum
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


    //bombas

    ColaBomba bombas;
    void actualizarBombas();

    void crearExplosion(int x, int y, int tamanoCelda,int alcance);

    int tamanoFlama = 20;

     bool reaccionEnCadena( int filaFlama, int columnaBomba,int retraso);
};

#endif // VENTANAJUEGO_H
