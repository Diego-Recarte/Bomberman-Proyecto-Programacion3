#ifndef CONTROLADORJUEGO_H
#define CONTROLADORJUEGO_H

#include "MapaYCasillas/mapa.h"
#include "Jugador/jugador.h"
#include "Enemigos/gestorenemigos.h"
#include "controladorjugador.h"
#include "sistemaitems.h"
#include "sistemabombas.h"

class QGraphicsScene;
class QKeyEvent;

class ControladorJuego
{
public:
    explicit ControladorJuego(QGraphicsScene* escena);
    ~ControladorJuego();

    void actualizar(int milisegundos);
    bool procesarTeclaPresionada(QKeyEvent* evento);
    bool procesarTeclaLiberada(QKeyEvent* evento);
    int obtenerVidaActual() const;
    int obtenerVidaMaxima() const;
    int obtenerCantidadEnemigos() const;

private:
    QGraphicsScene* escena = nullptr;
    Mapa* mapa = nullptr;
    Jugador* jugador = nullptr;
    GestorEnemigos enemigos;
    ControladorJugador controladorJugador;
    SistemaItems sistemaItems;
    SistemaBombas sistemaBombas;
    const int tamanoJugador = 30;
};

#endif // CONTROLADORJUEGO_H
