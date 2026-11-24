
#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsRectItem>

#include "MapaYCasillas/mapa.h"
#include "Bombas/colabomba.h"
#include "../Item/tipoitem.h"
#include "../Item/pilaitem.h"

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
    Jugador(int x, int y, int tamanio, int velocidadInicial, Mapa* mapa = nullptr);
    ~Jugador();

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

    bool calcularCasillaInteraccion( int& fila,int& columna, int dx = 0,int dy = 0) const;

    ColaBomba& obtenerBombas();
    int obtenerVidaMaxima() const;
    int obtenerVidaActual() const;
    int obtenerVida() const;
    void recibirDanio(int cantidad);
    void recibirDanioPorExplosion(int cantidad);
    void actualizarTemporizadores(int milisegundos);
    int obtenerFilaActual() const;
    int obtenerColumnaActual() const;
    void aumentarVelocidad();

    void recogerItem(TipoItem item);
    PilaItem& obtenerItems();






private:

    void aumentarVida();
    void curar();
    QGraphicsRectItem* figura;
    Mapa* mapa = nullptr;
    int velocidad;
    int bombasMaximas;
    int bombasActivas;
    int vidaActual;
    int vidaMaxima;
    int cooldownDanioMs = 0;
    int tamanioJugador=40;
    int alcance=3;

    PilaItem items;

    Direccion direccion;

    ColaBomba  bombas;
    bool casillaLibre(Mapa* mapa, int fila, int columna) const;

    };

#endif
