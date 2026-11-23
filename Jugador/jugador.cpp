#include "jugador.h"

Jugador::Jugador(Mapa* mapa)
{
    this->mapa = mapa;

    personaje = new QGraphicsRectItem(
        0, 0, tamanoJugador, tamanoJugador
        );

    personaje->setPos(100, 100);
}

QGraphicsRectItem* Jugador::obtenerPersonaje()
{
    return personaje;
}

void Jugador::presionarTecla(QKeyEvent* evento)
{
    if (evento == nullptr) {
        return;
    }

    if (evento->key() == Qt::Key_D) {
        direccion = Direccion::Derecha;
    }
    else if (evento->key() == Qt::Key_A) {
        direccion = Direccion::Izquierda;
    }
    else if (evento->key() == Qt::Key_W) {
        direccion = Direccion::Arriba;
    }
    else if (evento->key() == Qt::Key_S) {
        direccion = Direccion::Abajo;
    }
    else {
        return;
    }

    evento->accept();
}

void Jugador::soltarTecla(QKeyEvent* evento)
{
    if (evento == nullptr) {
        return;
    }

    if (evento->isAutoRepeat()) {
        evento->accept();
        return;
    }

    if (evento->key() == Qt::Key_D &&
        direccion == Direccion::Derecha) {
        direccion = Direccion::Null;
    }
    else if (evento->key() == Qt::Key_A &&
             direccion == Direccion::Izquierda) {
        direccion = Direccion::Null;
    }
    else if (evento->key() == Qt::Key_W &&
             direccion == Direccion::Arriba) {
        direccion = Direccion::Null;
    }
    else if (evento->key() == Qt::Key_S &&
             direccion == Direccion::Abajo) {
        direccion = Direccion::Null;
    }
    else {
        return;
    }

    evento->accept();
}

void Jugador::actualizarMovimiento()
{
    if (personaje == nullptr || mapa == nullptr || movimiento <= 0) {
        return;
    }

    int x = personaje->pos().x();
    int y = personaje->pos().y();

    int celda = mapa->obtenerTamanoCelda();
    if (celda <= 0) {
        return;
    }

    switch (direccion) {

    case Direccion::Arriba: {

        int filaDestino = (y - movimiento) / celda;
        int columnaIzquierda = x / celda;
        int columnaDerecha = (x + tamanoJugador - 1) / celda;

        if (!mapa->esObstaculo(filaDestino, columnaIzquierda) &&
            !mapa->esObstaculo(filaDestino, columnaDerecha)) {

            personaje->moveBy(0, -movimiento);
        }

        break;
    }

    case Direccion::Abajo: {

        int filaDestino =
            (y + tamanoJugador + movimiento - 2) / celda;

        int columnaIzquierda = x / celda;
        int columnaDerecha = (x + tamanoJugador - 1) / celda;

        if (!mapa->esObstaculo(filaDestino, columnaIzquierda) &&
            !mapa->esObstaculo(filaDestino, columnaDerecha)) {

            personaje->moveBy(0, movimiento);
        }

        break;
    }

    case Direccion::Derecha: {

        int columnaDestino =
            (x + tamanoJugador + movimiento - 2) / celda;

        int filaSuperior = y / celda;
        int filaInferior = (y + tamanoJugador - 1) / celda;

        if (!mapa->esObstaculo(filaSuperior, columnaDestino) &&
            !mapa->esObstaculo(filaInferior, columnaDestino)) {

            personaje->moveBy(movimiento, 0);
        }

        break;
    }

    case Direccion::Izquierda: {

        int columnaDestino = (x - movimiento) / celda;

        int filaSuperior = y / celda;
        int filaInferior = (y + tamanoJugador - 1) / celda;

        if (!mapa->esObstaculo(filaSuperior, columnaDestino) &&
            !mapa->esObstaculo(filaInferior, columnaDestino)) {

            personaje->moveBy(-movimiento, 0);
        }

        break;
    }

    case Direccion::Null:
        break;
    }
}
int Jugador::obtenerTamanio(){
    return tamanoJugador;
}
