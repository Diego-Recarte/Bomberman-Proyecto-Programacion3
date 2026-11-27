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
    Enemigo(Mapa* mapa, QGraphicsScene* escena, int fila, int columna,  int tamJugador);
    virtual ~Enemigo();
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
    int filaDestino = 0;
    int columnaDestino = 0;
    int direccionFila = 0;
    int direccionColumna = 0;
    int cooldownAtaqueMs = 0;
    bool desplazandose = false;

    bool elegirSiguienteCasilla(const ColaBomba* bombas);
    void avanzar(int milisegundos, const ColaBomba* bombas);
};

#endif // ENEMIGOALEATORIO_H
