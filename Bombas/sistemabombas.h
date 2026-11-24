#ifndef SISTEMABOMBAS_H
#define SISTEMABOMBAS_H

#include "Bombas/sistemaexplosion.h"

class ColaBomba;
class GestorEnemigos;
class Jugador;
class Mapa;
class QGraphicsScene;

class SistemaBombas
{
public:
    void configurar(Mapa* mapa, QGraphicsScene* escena, Jugador* jugador,
                    GestorEnemigos* enemigos, int tamanoJugador);
    void colocarBomba();
    void actualizar(int milisegundos);

private:
    Mapa* mapa = nullptr;
    QGraphicsScene* escena = nullptr;
    Jugador* jugador = nullptr;
    int tamanoJugador = 0;
    const int duracionBombaMs = 3000;
    SistemaExplosion sistemaExplosion;
};

#endif // SISTEMABOMBAS_H
