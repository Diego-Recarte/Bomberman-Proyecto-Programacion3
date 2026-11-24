#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H

#include "MapaYCasillas/mapa.h"
#include "jugador.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>

class VentanaJuego : public QGraphicsView
{
public:
    VentanaJuego();
    ~VentanaJuego() override;

    Mapa* mapa = nullptr;

protected:
    void keyPressEvent(QKeyEvent* evento) override;
    void keyReleaseEvent(QKeyEvent* evento) override;

private:
    Jugador* jugador = nullptr;
    QGraphicsScene* escena = nullptr;
    QTimer* temporizadorMovimiento = nullptr;

    int tamanoJugador = 40;
    int tamanoFlama = 20;
    int tamanoItemAlcance = 2;

    void construirMapa();
    void actualizarMovimiento();
    void revisarItemsJugador();

    void colocarBomba();
    void actualizarBombas();

    void crearExplosion(int x, int y, int tamanoCelda, int alcance);

    bool reaccionEnCadena(
        int filaFlama,
        int columnaFlama,
        int retraso
        );
};

#endif // VENTANAJUEGO_H