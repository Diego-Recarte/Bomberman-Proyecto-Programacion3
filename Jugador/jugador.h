#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include "../MapaYCasillas/mapa.h"

class ColaBomba;

class Jugador
{
public:
    Jugador(Mapa* mapa);

    void presionarTecla(QKeyEvent* evento);
    void soltarTecla(QKeyEvent* evento);
    int obtenerTamanio();
    void actualizarMovimiento(const ColaBomba* bombas = nullptr);
    void actualizarTemporizadores(int milisegundos);
    void recibirDanio(int cantidad);
    int obtenerVida() const;
    int obtenerVidaMaxima() const;
    int obtenerFilaActual() const;
    int obtenerColumnaActual() const;

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
    int vidaMaxima = 2;
    int vida = vidaMaxima;
    int tamanoJugador = 40;
    int cooldownDanioMs = 0;

    bool casillaLibre(int fila, int columna, const ColaBomba* bombas,
                      int filaActual, int columnaActual) const;

};

#endif
