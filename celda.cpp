#include "celda.h"

Celda::Celda()
{
    tipo = Tipo::vacio;
    resistencia = 0;
}

Celda::Celda(Tipo tipoInicial){
    tipo = tipoInicial;

    if (tipo == Tipo::caja)
    {
        resistencia = 1;
    }
    else if (tipo == Tipo::cajaFuerte)
    {
        resistencia = 2;
    }
    else
    {
        resistencia = 0;
    }
}

Celda::~Celda(){
    if (forma != nullptr){
        if (forma->scene() != nullptr){
            forma->scene()->removeItem(forma);
        }

        delete forma;
        forma = nullptr;
    }
}

Tipo Celda::obtenerTipo() const{
    return tipo;
}

bool Celda::esObstaculo() const{
    return tipo == Tipo::pared || tipo == Tipo::caja ||tipo == Tipo::cajaFuerte;
}

bool Celda::esDestructible() const{
    return tipo == Tipo::caja || tipo == Tipo::cajaFuerte;
}

bool Celda::estaDestruida() const
{
    return tipo == Tipo::vacio;
}

void Celda::recibirExplosion()
{
    if (!esDestructible())
    {
        return;
    }

    resistencia--;

    if (resistencia <= 0)
    {
        tipo = Tipo::vacio;
        if (forma != nullptr){
            if (forma->scene() != nullptr){
                forma->scene()->removeItem(forma);
            }

            delete forma;
            forma = nullptr;
        }
    }
}

void Celda::dibujar(QGraphicsScene* escena, int x, int y, int tamanoCelda)
{
    if (forma != nullptr)
    {
        return;
    }

    if (tipo == Tipo::vacio)
    {
        return;
    }

    QPen borde(Qt::black);
    QBrush relleno;

    if (tipo == Tipo::pared)
    {
        relleno = QBrush(Qt::darkGray);
    }
    else if (tipo == Tipo::caja)
    {
        relleno = QBrush(Qt::gray);
    }
    else if (tipo == Tipo::cajaFuerte)
    {
        relleno = QBrush(Qt::darkRed);
    }

    forma = escena->addRect( 0, 0,  tamanoCelda, tamanoCelda,  borde, relleno  );

    forma->setPos(x, y);
}