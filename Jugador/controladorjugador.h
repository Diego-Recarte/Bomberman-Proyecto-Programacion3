#ifndef CONTROLADORJUGADOR_H
#define CONTROLADORJUGADOR_H

#include "Jugador/jugador.h"

class QKeyEvent;

class ControladorJugador
{
public:
    void configurar(Jugador* jugador, Mapa* mapa);
    bool procesarTeclaPresionada(QKeyEvent* evento);
    bool procesarTeclaLiberada(QKeyEvent* evento);
    void actualizarMovimiento();
    void actualizarTemporizadores(int milisegundos);

private:
    Jugador* jugador = nullptr;
    Mapa* mapa = nullptr;
};

#endif // CONTROLADORJUGADOR_H
