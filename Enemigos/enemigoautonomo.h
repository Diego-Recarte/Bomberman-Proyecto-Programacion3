#ifndef ENEMIGOAUTONOMO_H
#define ENEMIGOAUTONOMO_H

#include "enemigoAleatorio.h"

class EnemigoAutonomo : public Enemigo
{
public:
    EnemigoAutonomo(Mapa* mapa, QGraphicsScene* escena, int fila, int columna,  int tamJugador);
};

#endif // ENEMIGOAUTONOMO_H
