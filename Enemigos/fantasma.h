#ifndef FANTASMA_H
#define FANTASMA_H

#include "enemigoAleatorio.h"
#include "mapa.h"
class fantasma : public Enemigo
{
public:
    fantasma(Mapa *mapa, QGraphicsScene *escena, int fila, int columna, int tamJugador);
    bool elegirSiguienteCasilla(const ColaBomba* bombas) override;

};

#endif // FANTASMA_H
