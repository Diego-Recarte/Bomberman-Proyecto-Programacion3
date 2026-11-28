#include "enemigoPersecutor.h"
#include "colabomba.h"
#include <QBrush>

EnemigoPersecutor::EnemigoPersecutor(Mapa* mapa, QGraphicsScene* escena, int fila,
                                 int columna, int tamJugador, Jugador* jugador)
    : Enemigo(mapa, escena, fila, columna, tamJugador), jugador(jugador)
{
    if (personaje != nullptr) {
        personaje->setBrush(QBrush(Qt::darkBlue));
    }
}
bool EnemigoPersecutor::elegirSiguienteCasilla(const ColaBomba* bombas)
{
    if (mapa == nullptr || personaje == nullptr) {
        return false;
    }
    const int tamanoCelda = mapa->obtenerTamanoCelda();
    if (tamanoCelda <= 0) {
        return false;
    }


    int direccionPersecucion = -1;
    if (jugador != nullptr && hayLineaLibre(
            filaActual, columnaActual,
            jugador->obtenerFilaActual(), jugador->obtenerColumnaActual()))
    {
        if (filaActual == jugador->obtenerFilaActual())
        {
            // Misma fila: persecución horizontal
            direccionPersecucion =
                (jugador->obtenerColumnaActual() > columnaActual) ? 3 : 2;
        }
        else if (columnaActual == jugador->obtenerColumnaActual())
        {
            // Misma columna: persecución vertical
            direccionPersecucion =
                (jugador->obtenerFilaActual() > filaActual) ? 1 : 0;
        }
    }

    int direccionElegida;
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


    bool puedePerseguir = false;

    for (int i = 0; i < cantidadOpciones; ++i)
    {
        if (opciones[i] == direccionPersecucion)
        {
            puedePerseguir = true;
            break;
        }
    }
    if (puedePerseguir)
    {
        direccionElegida = direccionPersecucion;
    }
    else if (opcionRecta >= 0 && (cantidadOpciones == 1 || std::rand() % 4 != 0)) {
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
bool EnemigoPersecutor::hayLineaLibre(int fila1, int col1, int fila2, int col2) {
    if (fila1 != fila2 && col1 != col2)
        return false; // No están en la misma fila ni columna

    if (fila1 == fila2) { // Revisar horizontalmente
        int paso = (col2 > col1) ? 1 : -1;

        for (int col = col1 + paso; col != col2; col += paso) {
            if (mapa->esObstaculo(fila1, col))
                return false;
        }
    } else { // Revisar verticalmente
        int paso = (fila2 > fila1) ? 1 : -1;

        for (int fila = fila1 + paso; fila != fila2; fila += paso) {
            if (mapa->esObstaculo(fila, col1))
                return false;
        }
    }

    return true;
}
