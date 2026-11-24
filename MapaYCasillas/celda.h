#ifndef CELDA_H
#define CELDA_H


#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPen>
#include <QBrush>

#include "../Item/tipoitem.h"
enum Tipo{
    vacio,
    pared,
    caja,
    cajaFuerte

};

class Celda
{


public:
    Celda();
    Celda(Tipo tipoInsertar);
    ~Celda();
    void recibirExplosion();
    bool esObstaculo() const;
    bool esDestructible() const;
    bool estaDestruida() const;
    Tipo obtenerTipo() const;
    void dibujar(QGraphicsScene* escena, int x, int y, int tamanoCelda, int tamanoJugador);
    void asignarItem(TipoItem itemAsignado);
    TipoItem obtenerItem() const;

    void setItemDisponible();
    bool isItemDisponible() const;
    void consumirItem();



private:

    Tipo tipo;
    int resistencia;
    QGraphicsRectItem* forma = nullptr;
    QGraphicsScene* escenaActual = nullptr;
    int posicionX = 0;
    int posicionY = 0;
    int tamanoCeldaActual = 0;
    int tamanoJugadorActual=0;
    TipoItem item = TipoItem::Ninguno;
    QGraphicsRectItem* figuraItem = nullptr;
    bool itemDisponible=false;

};



#endif // CELDA_H

