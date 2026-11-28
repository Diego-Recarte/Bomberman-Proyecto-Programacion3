#ifndef ENEMIGOPERSECUTOR_H
#define ENEMIGOPERSECUTOR_H

#include "enemigoAleatorio.h"
#include "jugador.h"
class Jugador;
class EnemigoPersecutor : public Enemigo
{
public:
    EnemigoPersecutor(Mapa* mapa, QGraphicsScene* escena, int fila, int columna,
                    int tamJugador, Jugador* jugador);
    bool hayLineaLibre(int fila1, int col1, int fila2, int col2);
    bool elegirSiguienteCasilla(const ColaBomba* bombas) override;
private:
    Jugador* jugador = nullptr;
};

#endif // ENEMIGOPERSECUTOR_H
