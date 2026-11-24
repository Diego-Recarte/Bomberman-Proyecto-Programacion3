#include "controladorjuego.h"
#include "MapaYCasillas/celda.h"
#include <QGraphicsScene>
#include <QKeyEvent>

ControladorJuego::ControladorJuego(QGraphicsScene* escena): escena(escena)
{
    if (this->escena == nullptr) {
        return;
    }

    mapa = new Mapa(11, 13, 70);
    mapa->crearMapa();
    mapa->dibujar(escena, tamanoJugador);

    jugador = new Jugador(100, 100, tamanoJugador, 5, mapa);
    escena->addItem(jugador->obtenerFigura());

    enemigos.crearEnemigos(mapa, escena, jugador->obtenerFilaActual(),jugador->obtenerColumnaActual(), 3);
    controladorJugador.configurar(jugador, mapa);
    sistemaItems.configurar(mapa, jugador, tamanoJugador);
    sistemaBombas.configurar(mapa, escena, jugador, &enemigos, tamanoJugador);
}

ControladorJuego::~ControladorJuego()
{
    delete jugador;
    jugador = nullptr;
    delete mapa;
    mapa = nullptr;
}

void ControladorJuego::actualizar(int milisegundos)
{
    if (jugador == nullptr || mapa == nullptr || milisegundos <= 0) {
        return;
    }
    controladorJugador.actualizarMovimiento();
    sistemaItems.actualizar();
    sistemaBombas.actualizar();
    controladorJugador.actualizarTemporizadores(milisegundos);
    enemigos.actualizar(milisegundos, jugador, &jugador->obtenerBombas());
}

bool ControladorJuego::procesarTeclaPresionada(QKeyEvent* evento){
    if (evento == nullptr || jugador == nullptr) {
        return false;
    }
    if (evento->key() == Qt::Key_Space) {
        if (!evento->isAutoRepeat()) {
            sistemaBombas.colocarBomba();
        }
        return true;
    }
    return controladorJugador.procesarTeclaPresionada(evento);
}

bool ControladorJuego::procesarTeclaLiberada(QKeyEvent* evento){
    return controladorJugador.procesarTeclaLiberada(evento);
}

int ControladorJuego::obtenerVidaActual() const{
    return jugador != nullptr ? jugador->obtenerVidaActual() : 0;
}

int ControladorJuego::obtenerVidaMaxima() const{
    return jugador != nullptr ? jugador->obtenerVidaMaxima() : 0;
}

int ControladorJuego::obtenerCantidadEnemigos() const
{
    return enemigos.obtenerCantidad();
}
