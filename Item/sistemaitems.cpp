#include "sistemaitems.h"
#include "Jugador/jugador.h"
#include "MapaYCasillas/celda.h"
#include "MapaYCasillas/mapa.h"
#include <QGraphicsRectItem>

void SistemaItems::configurar(Mapa* mapa, Jugador* jugador, int tamanoJugador){
    this->mapa = mapa;
    this->jugador = jugador;
    this->tamanoJugador = tamanoJugador;
}
void SistemaItems::actualizar()
{
    if (jugador == nullptr || mapa == nullptr) {
        return;
    }

    int fila = 0;
    int columna = 0;

    if (!jugador->calcularCasillaInteraccion(fila, columna)) {
        return;
    }

    Celda* celda = mapa->obtenerCelda(fila, columna);

    if (celda == nullptr ||!celda->isItemDisponible() ||celda->obtenerItem() == TipoItem::Portal) {
        return;
    }

    jugador->recogerItem(celda->obtenerItem());
    celda->consumirItem();
}