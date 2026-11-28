#include "fantasma.h"
#include "colabomba.h"

fantasma::fantasma(Mapa* mapa, QGraphicsScene* escena, int fila, int columna, int tamJugador):
    Enemigo(mapa, escena, fila, columna, tamJugador) {

    if (personaje != nullptr) {
        personaje->setBrush(QBrush(Qt::darkGray));
    }
}
bool fantasma::elegirSiguienteCasilla(const ColaBomba* bombas)
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
        if (mapa->esPared(fila, columna)) {
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