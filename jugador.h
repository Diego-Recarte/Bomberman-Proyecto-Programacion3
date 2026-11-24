
#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsRectItem>

#include "MapaYCasillas/mapa.h"
#include "Bombas/colabomba.h"
#include "pilaitem.h"

enum class Direccion
{
    Arriba,
    Abajo,
    Izquierda,
    Derecha,
    Null
};

class Jugador
{
public:
    Jugador(int x, int y, int tamanio, int velocidadInicial);

    QGraphicsRectItem* obtenerFigura();
    int obtenerVelocidad() const;

    void aumentarBombasMaximas();
    void aumentarVidas();

    int obtenerAlcance() const;

    void establecerDireccion(Direccion nuevaDireccion);
    Direccion obtenerDireccion() const;
    void actualizarMovimiento(Mapa* mapa, int tamanoCelda);


    bool puedeColocarBomba() const;
    void bombaColocada();
    void bombaExplotada();

    ColaBomba& obtenerBombas();
    int obtenerVidaMaxima();
    int obtenerVidaActual();
    void aumentarVelocidad();

    void recogerItem(TipoItem item);
    PilaItem& obtenerItems();






private:

    void aumentarVida();
    void curar();
    QGraphicsRectItem* figura;
    int velocidad;
    int bombasMaximas;
    int bombasActivas;
    int vidaActual;
    int vidaMaxima;
    int tamanioJugador=40;
    int alcance=3;

    PilaItem items;

    Direccion direccion;

    ColaBomba  bombas;
};

#endif