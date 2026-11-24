#include "sistemabombas.h"
#include "Bombas/colabomba.h"
#include "Enemigos/gestorenemigos.h"
#include "Jugador/jugador.h"
#include "MapaYCasillas/mapa.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>

void SistemaBombas::configurar(Mapa* mapa, QGraphicsScene* escena,Jugador* jugador, GestorEnemigos* enemigos,int tamanoJugador){
    this->mapa = mapa;
    this->escena = escena;
    this->jugador = jugador;
    this->tamanoJugador = tamanoJugador;
    if (jugador != nullptr) {
        sistemaExplosion.configurar(mapa, escena, &jugador->obtenerBombas(), tamanoJugador, enemigos, jugador);
    }
}

void SistemaBombas::colocarBomba(){
    if (jugador == nullptr || escena == nullptr || mapa == nullptr ||
        !jugador->puedeColocarBomba()) {
        return;
    }
    QGraphicsRectItem* figura = jugador->obtenerFigura();
    if (figura == nullptr) {
        return;
    }

    const int x = static_cast<int>(figura->pos().x());
    const int y = static_cast<int>(figura->pos().y());
    const bool agregada = jugador->obtenerBombas().agregar( y, x, duracionBombaMs, jugador->obtenerAlcance(), escena, mapa->obtenerTamanoCelda(), tamanoJugador);
    if (agregada) {
        jugador->bombaColocada();
    }
}

void SistemaBombas::actualizar(){
    if (mapa == nullptr || jugador == nullptr) {
        return;
    }
    ColaBomba& cola = jugador->obtenerBombas();
    while (cola.primeraBombaVencida()) {
        int x = 0;
        int y = 0;
        int alcance = 0;
        if (!cola.obtenerPosicionPrimera(x, y, alcance)) {
            break;
        }
        cola.eliminar();
        jugador->bombaExplotada();
        sistemaExplosion.crearExplosion(x, y, mapa->obtenerTamanoCelda(), alcance);
    }
}
