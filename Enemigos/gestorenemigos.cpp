#include "gestorenemigos.h"

#include "enemigoAleatorio.h"
#include "../MapaYCasillas/mapa.h"
#include "jugador.h"
#include "../Bombas/colabomba.h"
#include <QGraphicsScene>

GestorEnemigos::~GestorEnemigos()
{
    for (int i = 0; i < cantidadEnemigos; ++i) {
        delete enemigos[i];
    }
    delete[] enemigos;
}

void GestorEnemigos::crearEnemigos(Mapa* mapa, QGraphicsScene* escena,
                                   int filaJugador, int columnaJugador, int cantidad)
{
    if (mapa == nullptr || escena == nullptr || cantidad <= 0 || enemigos != nullptr) {
        return;
    }

    capacidad = cantidad;
    enemigos = new Enemigo*[capacidad]{};

    for (int fila = mapa->obtenerFilas() - 2;
         fila >= 1 && cantidadEnemigos < capacidad; --fila) {
        for (int columna = mapa->obtenerColumnas() - 2;
             columna >= 1 && cantidadEnemigos < capacidad; --columna) {
            if ((fila == filaJugador && columna == columnaJugador) ||
                mapa->esObstaculo(fila, columna)) {
                continue;
            }

            enemigos[cantidadEnemigos++] = new Enemigo(mapa, escena, fila, columna);
        }
    }
}

void GestorEnemigos::actualizar(int milisegundos, Jugador* jugador,
                                const ColaBomba* bombas)
{
    for (int i = 0; i < cantidadEnemigos;) {
        enemigos[i]->actualizar(milisegundos, jugador, bombas);
        if (!enemigos[i]->estaVivo()) {
            eliminarEnemigo(i);
        } else {
            ++i;
        }
    }
}

void GestorEnemigos::recibirExplosionEnCasilla(int fila, int columna)
{
    for (int i = 0; i < cantidadEnemigos;) {
        if (enemigos[i]->estaEnCasilla(fila, columna)) {
            enemigos[i]->recibirDanio(1);
        }

        if (!enemigos[i]->estaVivo()) {
            eliminarEnemigo(i);
        } else {
            ++i;
        }
    }
}

int GestorEnemigos::obtenerCantidad() const
{
    return cantidadEnemigos;
}

void GestorEnemigos::eliminarEnemigo(int indice)
{
    if (indice < 0 || indice >= cantidadEnemigos) {
        return;
    }

    delete enemigos[indice];
    for (int i = indice; i + 1 < cantidadEnemigos; ++i) {
        enemigos[i] = enemigos[i + 1];
    }
    enemigos[--cantidadEnemigos] = nullptr;
}
