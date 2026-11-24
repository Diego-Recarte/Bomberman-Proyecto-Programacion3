#ifndef ENEMIGOALEATORIO_H
#define ENEMIGOALEATORIO_H

#include <QGraphicsRectItem>
#include "../MapaYCasillas/mapa.h"

class ColaBomba;
class Jugador;
class QGraphicsScene;

class Enemigo
{
public:
    Enemigo(Mapa* mapa, QGraphicsScene* escena, int fila, int columna);
    ~Enemigo();
    int obtenerTamanio();
    void actualizar(int milisegundos, Jugador* jugador, const ColaBomba* bombas);
    void recibirDanio(int cantidad);
    bool estaVivo() const;
    bool estaEnCasilla(int fila, int columna) const;
    QGraphicsRectItem* obtenerPersonaje();
private:
    QGraphicsRectItem* personaje = nullptr;
    Mapa* mapa = nullptr;

    int vida = 1;
    int tamanoEnemigo = 40;
    int filaActual = 0;
    int columnaActual = 0;
    int cooldownAtaqueMs = 0;
    int tiempoMovimientoMs = 450;

    void moverAleatoriamente(const ColaBomba* bombas);
};

#endif // ENEMIGOALEATORIO_H
