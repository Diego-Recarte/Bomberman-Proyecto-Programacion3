#include "celda.h"
#include <iostream>

Celda::Celda()
{
    tipo = Tipo::vacio;
    resistencia = 0;
    item = TipoItem::Ninguno;
}

Celda::Celda(Tipo tipoInicial){
    tipo = tipoInicial;
    item = TipoItem::Ninguno;

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
    std::cout<<"Ingreso a vacio"<<std::endl;
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
        if (item != TipoItem::Ninguno && escenaActual != nullptr && item!=TipoItem::Alcance)
        {
            dibujar(escenaActual,posicionX,posicionY,tamanoCeldaActual,tamanoJugadorActual);
        }
    }
}
void Celda::dibujar(QGraphicsScene* escena,int x,int y,int tamanoCelda,int tamanoJugador){
    if (forma != nullptr){
        return;
    }

    if (tipo == Tipo::vacio && item == TipoItem::Ninguno){
        return;
    }

    QPen borde(Qt::black);
    QBrush relleno;

    if (tipo == Tipo::pared){
        relleno = QBrush(Qt::darkGray);
    }
    else if (tipo == Tipo::caja){
        relleno = QBrush(Qt::gray);
    }
    else if (tipo == Tipo::cajaFuerte){
        relleno = QBrush(Qt::darkRed);
    }
    else if (item != TipoItem::Ninguno){

        switch (item){
        case TipoItem::Alcance:{
            item = TipoItem::Ninguno;
            break;
        }
        case TipoItem::BombaExtra:{
            relleno = QBrush(Qt::blue);
            break;
        }
        case TipoItem::Velocidad:{
            relleno = QBrush(Qt::cyan);
            break;
        }
        case TipoItem::Portal:{
            relleno = QBrush(Qt::magenta);
            break;
        }
        case TipoItem::cura:{
            relleno = QBrush(Qt::green);
            break;
        }
        case TipoItem::masVida:{
            relleno = QBrush(Qt::red);
            break;
        }
        case TipoItem::Ninguno:{

            break;
        }



        }

    }

    if ((item != TipoItem::Ninguno && item!=TipoItem::Portal) && Tipo::vacio==tipo){
        int desplazamiento = (tamanoCelda - tamanoJugador) / 2;

        forma = escena->addRect(0, 0,tamanoJugador, tamanoJugador,borde, relleno);

        forma->setPos( x + desplazamiento, y + desplazamiento );
    }
    else{
        forma = escena->addRect(0, 0,tamanoCelda, tamanoCelda,borde, relleno);

        forma->setPos(x, y);
    }

    escenaActual = escena;
    posicionX = x;
    posicionY = y;
    tamanoCeldaActual = tamanoCelda;
    tamanoJugadorActual = tamanoJugador;
}

void Celda::asignarItem(TipoItem itemAsignado){
    item = itemAsignado;
}

TipoItem Celda::obtenerItem() const{
    return item;
}


void Celda::setItemDisponible(){
    itemDisponible = true;

}
bool Celda::isItemDisponible() const{
    return itemDisponible;
}

void Celda::consumirItem()
{
    if (forma != nullptr)
    {
        if (forma->scene() != nullptr)
        {
            forma->scene()->removeItem(forma);
        }

        delete forma;
        forma = nullptr;
    }

    item = TipoItem::Ninguno;
    itemDisponible = false;
}