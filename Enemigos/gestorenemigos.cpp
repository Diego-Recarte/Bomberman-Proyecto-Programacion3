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

    while (primerosImpactos != nullptr) {
        NodoImpactoExplosion* eliminado = primerosImpactos;
        primerosImpactos = primerosImpactos->siguiente;
        delete eliminado;
    }
}

void GestorEnemigos::crearEnemigos(Mapa* mapa, QGraphicsScene* escena,int filaJugador, int columnaJugador, int cantidad, int tamJugador)
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

            enemigos[cantidadEnemigos++] = new Enemigo(mapa, escena, fila, columna, tamJugador );
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

void GestorEnemigos::recibirExplosionEnCasilla(
    int fila, int columna, int identificadorExplosion)
{
    for (int i = 0; i < cantidadEnemigos;) {
        Enemigo* enemigo = enemigos[i];
        if (enemigo->estaEnCasilla(fila, columna) &&
            !yaRecibioExplosion(enemigo, identificadorExplosion)) {
            registrarImpacto(enemigo, identificadorExplosion);
            enemigo->recibirDanio(1);
        }

        if (!enemigo->estaVivo()) {
            eliminarEnemigo(i);
        } else {
            ++i;
        }
    }
}

void GestorEnemigos::finalizarExplosion(int identificadorExplosion)
{
    NodoImpactoExplosion* anterior = nullptr;
    NodoImpactoExplosion* actual = primerosImpactos;
    while (actual != nullptr) {
        if (actual->identificadorExplosion == identificadorExplosion) {
            NodoImpactoExplosion* eliminado = actual;
            actual = actual->siguiente;
            if (anterior == nullptr) {
                primerosImpactos = actual;
            } else {
                anterior->siguiente = actual;
            }
            delete eliminado;
        } else {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}

bool GestorEnemigos::yaRecibioExplosion(
    const Enemigo* enemigo, int identificadorExplosion) const
{
    NodoImpactoExplosion* actual = primerosImpactos;
    while (actual != nullptr) {
        if (actual->enemigo == enemigo &&
            actual->identificadorExplosion == identificadorExplosion) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

void GestorEnemigos::registrarImpacto(
    const Enemigo* enemigo, int identificadorExplosion)
{
    primerosImpactos = new NodoImpactoExplosion{
        enemigo, identificadorExplosion, primerosImpactos};
}

void GestorEnemigos::eliminarImpactosDelEnemigo(const Enemigo* enemigo)
{
    NodoImpactoExplosion* anterior = nullptr;
    NodoImpactoExplosion* actual = primerosImpactos;
    while (actual != nullptr) {
        if (actual->enemigo == enemigo) {
            NodoImpactoExplosion* eliminado = actual;
            actual = actual->siguiente;
            if (anterior == nullptr) {
                primerosImpactos = actual;
            } else {
                anterior->siguiente = actual;
            }
            delete eliminado;
        } else {
            anterior = actual;
            actual = actual->siguiente;
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

    eliminarImpactosDelEnemigo(enemigos[indice]);
    delete enemigos[indice];
    for (int i = indice; i + 1 < cantidadEnemigos; ++i) {
        enemigos[i] = enemigos[i + 1];
    }
    enemigos[--cantidadEnemigos] = nullptr;
}
