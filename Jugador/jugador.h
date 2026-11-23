#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include "../MapaYCasillas/mapa.h"

class Jugador
{
public:
    Jugador(Mapa* mapa);

    void presionarTecla(QKeyEvent* evento);
    void soltarTecla(QKeyEvent* evento);
    int obtenerTamanio();
    void actualizarMovimiento();

    QGraphicsRectItem* obtenerPersonaje();

private:

    enum class Direccion {
        Arriba,
        Abajo,
        Izquierda,
        Derecha,
        Null
    };

    Direccion direccion = Direccion::Null;

    QGraphicsRectItem* personaje = nullptr;
    Mapa* mapa = nullptr;

    int movimiento = 5;
    int vida = 2;
    int tamanoJugador = 40;

};

#endif
