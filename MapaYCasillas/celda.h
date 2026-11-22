#ifndef CELDA_H
#define CELDA_H


#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPen>
#include <QBrush>
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
    void dibujar(QGraphicsScene* escena, int x, int y, int tamanoCelda);


private:

    Tipo tipo;
    int resistencia;
    QGraphicsRectItem* forma = nullptr;

};



#endif // CELDA_H
