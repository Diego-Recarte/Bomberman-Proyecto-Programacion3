#include "controladorjugador.h"
#include <QKeyEvent>

void ControladorJugador::configurar(Jugador* jugador, Mapa* mapa){
    this->jugador = jugador;
    this->mapa = mapa;
}

bool ControladorJugador::procesarTeclaPresionada(QKeyEvent* evento){
    if (evento == nullptr || jugador == nullptr) {
        return false;
    }
    switch (evento->key()) {

        case Qt::Key_W:{

            jugador->establecerDireccion(Direccion::Arriba);
            break;
        }
        case Qt::Key_S:{

            jugador->establecerDireccion(Direccion::Abajo);
            break;
        }
        case Qt::Key_A:{
            jugador->establecerDireccion(Direccion::Izquierda);
            break;
        }
        case Qt::Key_D: {
            jugador->establecerDireccion(Direccion::Derecha);
            break;
        }
        default:
            return false;
        }
    return true;
}

bool ControladorJugador::procesarTeclaLiberada(QKeyEvent* evento){
    if (evento == nullptr || jugador == nullptr) {
        return false;
    }
    if (evento->isAutoRepeat()) {
        return true;
    }

    const Direccion direccion = jugador->obtenerDireccion();
    const bool detener =(evento->key() == Qt::Key_W && direccion == Direccion::Arriba) ||(evento->key() == Qt::Key_S && direccion == Direccion::Abajo) ||(evento->key() == Qt::Key_A && direccion == Direccion::Izquierda) ||(evento->key() == Qt::Key_D && direccion == Direccion::Derecha);
    if (!detener) {
        return false;
    }

    jugador->establecerDireccion(Direccion::Null);
    return true;
}

void ControladorJugador::actualizarMovimiento(){
    if (jugador != nullptr && mapa != nullptr) {
        jugador->actualizarMovimiento(mapa, mapa->obtenerTamanoCelda(), &jugador->obtenerBombas());
    }
}

void ControladorJugador::actualizarTemporizadores(int milisegundos)
{
    if (jugador != nullptr) {
        jugador->actualizarTemporizadores(milisegundos);
    }
}
