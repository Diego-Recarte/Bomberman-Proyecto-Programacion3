#include "colabomba.h"

ColaBomba::ColaBomba() {}

ColaBomba::~ColaBomba()
{
    vaciar();
}

bool ColaBomba::estaVacia() const
{
    return primero == nullptr;
}

int ColaBomba::obtenerCantidad() const
{
    return cantidad;
}

void ColaBomba::eliminar()
{
    if (estaVacia()) {
        return;
    }

    NodoBomba* eliminado = primero;
    primero = primero->siguiente;
    if (primero == nullptr) {
        ultimo = nullptr;
    }
    delete eliminado;
    --cantidad;
}

void ColaBomba::vaciar()
{
    while (!estaVacia()) {
        eliminar();
    }
}

bool ColaBomba::agregar(int fila, int columna, int tiempo, int alcance,
                        QGraphicsScene* escena, int tamanoCelda, int tamanoJugador)
{
    if (escena == nullptr || tamanoCelda <= 0 || tamanoJugador <= 0) {
        return false;
    }

    const int filaCasilla = (fila + tamanoJugador / 4) / tamanoCelda;
    const int columnaCasilla = (columna + tamanoJugador / 4) / tamanoCelda;
    if (existeBombaEn(filaCasilla, columnaCasilla, tamanoCelda, tamanoJugador)) {
        return false;
    }

    NodoBomba* nueva = new NodoBomba(fila, columna, tiempo, alcance);
    nueva->bomba.dibujar(escena, tamanoCelda);
    if (estaVacia()) {
        primero = nueva;
        ultimo = nueva;
    } else {
        ultimo->siguiente = nueva;
        ultimo = nueva;
    }
    ++cantidad;
    return true;
}

bool ColaBomba::primeraBombaVencida() const
{
    return !estaVacia() && primero->bomba.tiempoCumplido();
}

bool ColaBomba::obtenerPosicionPrimera(int& x, int& y, int& alcanceExterno) const
{
    if (estaVacia()) {
        return false;
    }

    alcanceExterno = primero->bomba.obtenerAlcance();
    x = primero->bomba.obtenerX();
    y = primero->bomba.obtenerY();
    return true;
}

bool ColaBomba::existeBombaEn(int fila, int columna, int tamanoCelda,
                              int tamanoJugador) const
{
    if (tamanoCelda <= 0 || tamanoJugador <= 0) {
        return false;
    }

    NodoBomba* actual = primero;
    while (actual != nullptr) {
        const int filaActual = (actual->bomba.obtenerY() + tamanoJugador / 4) / tamanoCelda;
        const int columnaActual = (actual->bomba.obtenerX() + tamanoJugador / 4) / tamanoCelda;
        if (filaActual == fila && columnaActual == columna) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

bool ColaBomba::localizarBomba(int fila, int columna, int& x, int& y,
                               int& alcance, int tamanoCelda, int tamanoJugador)
{
    if (tamanoCelda <= 0 || tamanoJugador <= 0) {
        return false;
    }

    NodoBomba* actual = primero;
    while (actual != nullptr) {
        const int filaActual = (actual->bomba.obtenerY() + tamanoJugador / 4) / tamanoCelda;
        const int columnaActual = (actual->bomba.obtenerX() + tamanoJugador / 4) / tamanoCelda;
        if (filaActual == fila && columnaActual == columna) {
            x = actual->bomba.obtenerX();
            y = actual->bomba.obtenerY();
            alcance = actual->bomba.obtenerAlcance();
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

bool ColaBomba::eliminarBombaEn(int fila, int columna, int tamanoCelda,
                                int tamanoJugador)
{
    if (tamanoCelda <= 0 || tamanoJugador <= 0) {
        return false;
    }

    NodoBomba* anterior = nullptr;
    NodoBomba* actual = primero;
    while (actual != nullptr) {
        const int filaActual = (actual->bomba.obtenerY() + tamanoJugador / 4) / tamanoCelda;
        const int columnaActual = (actual->bomba.obtenerX() + tamanoJugador / 4) / tamanoCelda;
        if (filaActual == fila && columnaActual == columna) {
            if (anterior == nullptr) {
                primero = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            if (actual == ultimo) {
                ultimo = anterior;
            }
            delete actual;
            --cantidad;
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return false;
}