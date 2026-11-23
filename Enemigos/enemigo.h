#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsRectItem>
#include "../MapaYCasillas/mapa.h"


class Enemigo
{
public:
    Enemigo(Mapa *mapa);
    int obtenerTamanio();
    void actualizarMovimiento();
    QGraphicsRectItem* obtenerPersonaje();
private:
    enum Direccion{
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
    int vida = 1;
    int tamanoEnemigo = 40;
};

#endif // ENEMIGO_H
