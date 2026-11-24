#include "sistemaitems.h"
#include "Jugador/jugador.h"
#include "MapaYCasillas/celda.h"
#include "MapaYCasillas/mapa.h"
#include <QGraphicsRectItem>

void SistemaItems::configurar(Mapa* mapa, Jugador* jugador, int tamanoJugador)
{
    this->mapa = mapa;
    this->jugador = jugador;
    this->tamanoJugador = tamanoJugador;
}

void SistemaItems::actualizar()
{
    if (jugador == nullptr || mapa == nullptr || tamanoJugador <= 0) {
        return;
    }
    QGraphicsRectItem* figura = jugador->obtenerFigura();
    const int tamanoCelda = mapa->obtenerTamanoCelda();
    if (figura == nullptr || tamanoCelda <= 0) {
        return;
    }

    const int x = static_cast<int>(figura->pos().x());
    const int y = static_cast<int>(figura->pos().y());
    const int fila = (y + tamanoJugador / 4) / tamanoCelda;
    const int columna = (x + tamanoJugador / 4) / tamanoCelda;
    Celda* celda = mapa->obtenerCelda(fila, columna);
    if (celda == nullptr || !celda->isItemDisponible() ||
        celda->obtenerItem() == TipoItem::Portal) {
        return;
    }

    jugador->recogerItem(celda->obtenerItem());
    celda->consumirItem();
}
