#include "enemigoAleatorio.h"
#include "../Bombas/colabomba.h"
#include "../Jugador/jugador.h"
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>
#include <QtGlobal>
#include <cstdlib>

Enemigo::Enemigo(Mapa* mapa, QGraphicsScene* escena, int fila, int columna)
    : mapa(mapa), filaActual(fila), columnaActual(columna),
      filaDestino(fila), columnaDestino(columna)
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

void Enemigo::actualizar(int milisegundos, Jugador* jugador,
                         const ColaBomba* bombas)
{
    if (vida <= 0 || mapa == nullptr || jugador == nullptr || milisegundos <= 0) {
        return;
    }
    if (cooldownAtaqueMs > 0) {
        cooldownAtaqueMs -= milisegundos;
        if (cooldownAtaqueMs < 0) {
            cooldownAtaqueMs = 0;
        }
    }

    if (estaEnCasilla(jugador->obtenerFilaActual(), jugador->obtenerColumnaActual()) &&
        cooldownAtaqueMs == 0) {
        jugador->recibirDanio(1);
        cooldownAtaqueMs = 1200;
    }

    avanzar(milisegundos, bombas);
    if (!desplazandose) {
        elegirSiguienteCasilla(bombas);
    }
}

bool Enemigo::elegirSiguienteCasilla(const ColaBomba* bombas)
{
    if (mapa == nullptr || personaje == nullptr) {
        return false;
    }
    const int tamanoCelda = mapa->obtenerTamanoCelda();
    if (tamanoCelda <= 0) {
        return false;
    }

    const int desplazamientosFila[4] = {-1, 1, 0, 0};
    const int desplazamientosColumna[4] = {0, 0, -1, 1};
    int opciones[4];
    int cantidadOpciones = 0;
    int opcionRecta = -1;
    for (int direccion = 0; direccion < 4; ++direccion) {
        const int fila = filaActual + desplazamientosFila[direccion];
        const int columna = columnaActual + desplazamientosColumna[direccion];
        if (mapa->esObstaculo(fila, columna)) {
            continue;
        }
        if (bombas != nullptr && bombas->existeBombaEn(
                fila, columna, tamanoCelda, tamanoEnemigo)) {
            continue;
        }
        opciones[cantidadOpciones++] = direccion;
        if (desplazamientosFila[direccion] == direccionFila &&
            desplazamientosColumna[direccion] == direccionColumna) {
            opcionRecta = direccion;
        }
    }
    if (cantidadOpciones == 0) {
        return false;
    }

    int direccionElegida;
    if (opcionRecta >= 0 && (cantidadOpciones == 1 || std::rand() % 4 != 0)) {
        direccionElegida = opcionRecta;
    } else {
        direccionElegida = opciones[std::rand() % cantidadOpciones];
    }

    direccionFila = desplazamientosFila[direccionElegida];
    direccionColumna = desplazamientosColumna[direccionElegida];
    filaDestino = filaActual + direccionFila;
    columnaDestino = columnaActual + direccionColumna;
    desplazandose = true;
    return true;
}
void Enemigo::avanzar(int milisegundos, const ColaBomba* bombas)
{
    if (!desplazandose || personaje == nullptr || mapa == nullptr) {
        return;
    }
    const int tamanoCelda = mapa->obtenerTamanoCelda();
    if (tamanoCelda <= 0) {
        desplazandose = false;
        return;
    }

    // Misma velocidad base que el jugador: 5 píxeles cada 16 ms.
    qreal distanciaRestante = 5.0 * milisegundos / 16.0;
    while (distanciaRestante > 0 && desplazandose) {
        const qreal xObjetivo = columnaDestino * tamanoCelda +
                                (tamanoCelda - tamanoEnemigo) / 2.0;
        const qreal yObjetivo = filaDestino * tamanoCelda +
                                (tamanoCelda - tamanoEnemigo) / 2.0;
        const qreal dx = xObjetivo - personaje->pos().x();
        const qreal dy = yObjetivo - personaje->pos().y();
        const qreal distanciaAlObjetivo = qAbs(dx) + qAbs(dy);
        if (distanciaAlObjetivo <= distanciaRestante) {
            personaje->setPos(xObjetivo, yObjetivo);
            distanciaRestante -= distanciaAlObjetivo;
            filaActual = filaDestino;
            columnaActual = columnaDestino;
            desplazandose = false;
            if (distanciaRestante > 0) {
                elegirSiguienteCasilla(bombas);
            }
            continue;
        }

        const qreal paso = qMin(distanciaRestante, distanciaAlObjetivo);
        if (qAbs(dx) > 0) {
            personaje->moveBy(dx > 0 ? paso : -paso, 0);
        } else {
            personaje->moveBy(0, dy > 0 ? paso : -paso);
        }
        distanciaRestante = 0;
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
    if (personaje == nullptr || mapa == nullptr || mapa->obtenerTamanoCelda() <= 0) {
        return false;
    }
    const qreal centroX = personaje->pos().x() + tamanoEnemigo / 2.0;
    const qreal centroY = personaje->pos().y() + tamanoEnemigo / 2.0;
    const int filaEnemigo = static_cast<int>(centroY) / mapa->obtenerTamanoCelda();
    const int columnaEnemigo = static_cast<int>(centroX) / mapa->obtenerTamanoCelda();
    return filaEnemigo == fila && columnaEnemigo == columna;
}

int Enemigo::obtenerTamanio()
{
    return tamanoEnemigo;
}

QGraphicsRectItem* Enemigo::obtenerPersonaje()
{
    return personaje;
}
