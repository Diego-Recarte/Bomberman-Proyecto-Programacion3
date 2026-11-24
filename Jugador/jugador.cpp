#include "jugador.h"
#include "../Bombas/colabomba.h"

Jugador::Jugador(Mapa* mapa)
{
    this->mapa = mapa;

    personaje = new QGraphicsRectItem(
        0, 0, tamanoJugador, tamanoJugador
        );
    personaje->setBrush(QBrush(Qt::blue));
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

void Jugador::actualizarMovimiento(const ColaBomba* bombas)
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

    const int filaActual = (y + tamanoJugador / 2) / celda;
    const int columnaActual = (x + tamanoJugador / 2) / celda;

    switch (direccion) {

    case Direccion::Arriba: {

        int filaDestino = (y - movimiento) / celda;
        int columnaIzquierda = x / celda;
        int columnaDerecha = (x + tamanoJugador - 1) / celda;

        if (casillaLibre(filaDestino, columnaIzquierda, bombas, filaActual, columnaActual) &&
            casillaLibre(filaDestino, columnaDerecha, bombas, filaActual, columnaActual)) {

            personaje->moveBy(0, -movimiento);
        }

        break;
    }

    case Direccion::Abajo: {

        int filaDestino =
            (y + tamanoJugador + movimiento - 2) / celda;

        int columnaIzquierda = x / celda;
        int columnaDerecha = (x + tamanoJugador - 1) / celda;

        if (casillaLibre(filaDestino, columnaIzquierda, bombas, filaActual, columnaActual) &&
            casillaLibre(filaDestino, columnaDerecha, bombas, filaActual, columnaActual)) {

            personaje->moveBy(0, movimiento);
        }

        break;
    }

    case Direccion::Derecha: {

        int columnaDestino =
            (x + tamanoJugador + movimiento - 2) / celda;

        int filaSuperior = y / celda;
        int filaInferior = (y + tamanoJugador - 1) / celda;

        if (casillaLibre(filaSuperior, columnaDestino, bombas, filaActual, columnaActual) &&
            casillaLibre(filaInferior, columnaDestino, bombas, filaActual, columnaActual)) {

            personaje->moveBy(movimiento, 0);
        }

        break;
    }

    case Direccion::Izquierda: {

        int columnaDestino = (x - movimiento) / celda;

        int filaSuperior = y / celda;
        int filaInferior = (y + tamanoJugador - 1) / celda;

        if (casillaLibre(filaSuperior, columnaDestino, bombas, filaActual, columnaActual) &&
            casillaLibre(filaInferior, columnaDestino, bombas, filaActual, columnaActual)) {

            personaje->moveBy(-movimiento, 0);
        }

        break;
    }

    case Direccion::Null:
        break;
    }
}

bool Jugador::casillaLibre(int fila, int columna, const ColaBomba* bombas,
                           int filaActual, int columnaActual) const
{
    if (mapa == nullptr || mapa->esObstaculo(fila, columna)) {
        return false;
    }

    if (bombas == nullptr ||
        !bombas->existeBombaEn(fila, columna, mapa->obtenerTamanoCelda(), tamanoJugador)) {
        return true;
    }

    // Permite salir de la casilla donde el jugador colocó la bomba.
    return fila == filaActual && columna == columnaActual;
}

void Jugador::actualizarTemporizadores(int milisegundos)
{
    if (cooldownDanioMs > 0) {
        cooldownDanioMs -= milisegundos;
        if (cooldownDanioMs < 0) {
            cooldownDanioMs = 0;
        }
    }
}

void Jugador::recibirDanio(int cantidad)
{
    if (cantidad <= 0 || vida <= 0 || cooldownDanioMs > 0) {
        return;
    }

    vida -= cantidad;
    if (vida < 0) {
        vida = 0;
    }
    cooldownDanioMs = 800;
}

int Jugador::obtenerVida() const
{
    return vida;
}

int Jugador::obtenerVidaMaxima() const
{
    return vidaMaxima;
}

int Jugador::obtenerFilaActual() const
{
    if (personaje == nullptr || mapa == nullptr || mapa->obtenerTamanoCelda() <= 0) {
        return -1;
    }
    return (static_cast<int>(personaje->pos().y()) + tamanoJugador / 2) /
           mapa->obtenerTamanoCelda();
}

int Jugador::obtenerColumnaActual() const
{
    if (personaje == nullptr || mapa == nullptr || mapa->obtenerTamanoCelda() <= 0) {
        return -1;
    }
    return (static_cast<int>(personaje->pos().x()) + tamanoJugador / 2) /
           mapa->obtenerTamanoCelda();
}

int Jugador::obtenerTamanio(){
    return tamanoJugador;
}
