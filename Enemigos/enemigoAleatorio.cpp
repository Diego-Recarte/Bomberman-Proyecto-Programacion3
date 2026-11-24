#include "enemigoAleatorio.h"
#include "../Bombas/colabomba.h"
#include "../Jugador/jugador.h"
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>
#include <cstdlib>

Enemigo::Enemigo(Mapa* mapa, QGraphicsScene* escena, int fila, int columna)
    : mapa(mapa), filaActual(fila), columnaActual(columna)
{
    if (mapa == nullptr || escena == nullptr) {
        return;
    }

    const int tamanoCelda = mapa->obtenerTamanoCelda();
    if (tamanoCelda <= 0) {
        return;
    }

    const int desplazamiento = (tamanoCelda - tamanoEnemigo) / 2;
    personaje = escena->addRect(0, 0, tamanoEnemigo, tamanoEnemigo,
                                QPen(Qt::black), QBrush(Qt::darkRed));
    if (personaje != nullptr) {
        personaje->setPos(columnaActual * tamanoCelda + desplazamiento,
                          filaActual * tamanoCelda + desplazamiento);
    }
}

Enemigo::~Enemigo()
{
    if (personaje != nullptr) {
        if (personaje->scene() != nullptr) {
            personaje->scene()->removeItem(personaje);
        }
        delete personaje;
    }
}

void Enemigo::actualizar(int milisegundos, Jugador* jugador, const ColaBomba* bombas)
{
    if (vida <= 0 || mapa == nullptr || jugador == nullptr) {
        return;
    }

    if (cooldownAtaqueMs > 0) {
        cooldownAtaqueMs -= milisegundos;
        if (cooldownAtaqueMs < 0) {
            cooldownAtaqueMs = 0;
        }
    }

    if (filaActual == jugador->obtenerFilaActual() &&
        columnaActual == jugador->obtenerColumnaActual()) {
        if (cooldownAtaqueMs == 0) {
            jugador->recibirDanio(1);
            cooldownAtaqueMs = 1200;
        }
        return;
    }

    tiempoMovimientoMs -= milisegundos;
    if (tiempoMovimientoMs <= 0) {
        tiempoMovimientoMs = 450;
        moverAleatoriamente(bombas);
    }
}

void Enemigo::moverAleatoriamente(const ColaBomba* bombas)
{
    if (mapa == nullptr) {
        return;
    }

    const int tamanoCelda = mapa->obtenerTamanoCelda();
    if (tamanoCelda <= 0) {
        return;
    }

    const int desplazamientosFila[4] = {-1, 1, 0, 0};
    const int desplazamientosColumna[4] = {0, 0, -1, 1};
    const int primeraDireccion = rand() % 4;

    for (int intento = 0; intento < 4; ++intento) {
        const int direccion = (primeraDireccion + intento) % 4;
        const int filaDestino = filaActual + desplazamientosFila[direccion];
        const int columnaDestino = columnaActual + desplazamientosColumna[direccion];

        if (mapa->esObstaculo(filaDestino, columnaDestino)) {
            continue;
        }
        if (bombas != nullptr && bombas->existeBombaEn(
                filaDestino, columnaDestino, tamanoCelda, tamanoEnemigo)) {
            continue;
        }

        filaActual = filaDestino;
        columnaActual = columnaDestino;
        if (personaje != nullptr) {
            const int desplazamiento = (tamanoCelda - tamanoEnemigo) / 2;
            personaje->setPos(columnaActual * tamanoCelda + desplazamiento,
                              filaActual * tamanoCelda + desplazamiento);
        }
        return;
    }
}

void Enemigo::recibirDanio(int cantidad)
{
    if (cantidad > 0 && vida > 0) {
        vida -= cantidad;
        if (vida < 0) {
            vida = 0;
        }
    }
}

bool Enemigo::estaVivo() const
{
    return vida > 0;
}

bool Enemigo::estaEnCasilla(int fila, int columna) const
{
    return filaActual == fila && columnaActual == columna;
}

int Enemigo::obtenerTamanio()
{
    return tamanoEnemigo;
}

QGraphicsRectItem* Enemigo::obtenerPersonaje()
{
    return personaje;
}
