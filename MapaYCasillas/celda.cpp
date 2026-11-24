#include "celda.h"
#include <iostream>
#include <QPixmap>

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
        if (escenaActual != nullptr )
        {
            dibujar(escenaActual,posicionX,posicionY,tamanoCeldaActual,tamanoJugadorActual);
        }
    }
}
void Celda::dibujar(QGraphicsScene* escena,int x,int y,int tamanoCelda,int tamanoJugador){
    if (forma != nullptr){
        return;
    }

    QPen borde(Qt::black);
    QBrush relleno;
    if (tipo == Tipo::vacio && item == TipoItem::Ninguno){
        static const QPixmap imagenPared(":/piso.png");
        if (imagenPared.isNull()){
            relleno = QBrush(Qt::darkGray);
        }else{
            const QPixmap imagenAjustada = imagenPared.scaled(tamanoCelda,tamanoCelda ,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            relleno = QBrush(imagenAjustada);
        }



    }

    if (tipo == Tipo::pared){
        static const QPixmap imagenPared(":/pared.png");
        if (imagenPared.isNull()){
            relleno = QBrush(Qt::darkGray);
        }else{
            const QPixmap imagenAjustada = imagenPared.scaled(tamanoCelda,tamanoCelda,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            relleno = QBrush(imagenAjustada);
        }

    }
    else if (tipo == Tipo::caja){

        static const QPixmap imagenCaja(":/caja.png");

        if (imagenCaja.isNull()){
            relleno = QBrush(Qt::gray);
        }
        else{
            const QPixmap imagenAjustada = imagenCaja.scaled(tamanoCelda ,tamanoCelda ,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

            relleno = QBrush(imagenAjustada);
        }
    }
    else if (tipo == Tipo::cajaFuerte){
        relleno = QBrush(Qt::darkRed);
    }
    else if (item != TipoItem::Ninguno){

        static const QPixmap imagenPared(":/piso.png");
        if (imagenPared.isNull()){
            relleno = QBrush(Qt::darkGray);
        }else{
            const QPixmap imagenAjustada = imagenPared.scaled(tamanoCelda,tamanoCelda,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            relleno = QBrush(imagenAjustada);
        }


        forma = escena->addRect(0, 0,tamanoCelda, tamanoCelda,borde, relleno);

        forma->setPos(x, y);
        forma->setZValue(-1);

        switch (item){
        case TipoItem::Alcance:{




            item = TipoItem::Ninguno;
            break;
        }
        case TipoItem::BombaExtra:{
            static const QPixmap imagenPared(":/masbombas");
            if (imagenPared.isNull()){
                relleno = QBrush(Qt::darkGray);
            }else{
                const QPixmap imagenAjustada = imagenPared.scaled(tamanoJugador* 2,tamanoJugador* 2,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                relleno = QBrush(imagenAjustada);
            }
            break;
        }
        case TipoItem::Velocidad:{
            static const QPixmap imagenPared(":/velocidad");
            if (imagenPared.isNull()){
                relleno = QBrush(Qt::darkGray);
            }else{
                const QPixmap imagenAjustada = imagenPared.scaled(tamanoJugador* 2,tamanoJugador* 2,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                relleno = QBrush(imagenAjustada);
            }
            break;
        }
        case TipoItem::Portal:{
            relleno = QBrush(Qt::magenta);
            break;
        }
        case TipoItem::cura:{

            static const QPixmap imagenPared(":/cura");
            if (imagenPared.isNull()){
                relleno = QBrush(Qt::darkGray);
            }else{
                const QPixmap imagenAjustada = imagenPared.scaled(tamanoJugador* 2,tamanoJugador* 2,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                relleno = QBrush(imagenAjustada);
            }

            break;
        }
        case TipoItem::masVida:{
            static const QPixmap imagenPared(":/mascorazones");
            if (imagenPared.isNull()){
                relleno = QBrush(Qt::darkGray);
            }else{
                const QPixmap imagenAjustada = imagenPared.scaled(tamanoJugador* 2,tamanoJugador* 2,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                relleno = QBrush(imagenAjustada);
            }
            break;
        }
        case TipoItem::Ninguno:{

            break;
        }



        }

    }

    if (tipo == Tipo::vacio &&item != TipoItem::Ninguno &&item != TipoItem::Portal){
        const int tamanoItem = tamanoJugador *2;

        const double desplazamiento =(tamanoCelda - tamanoItem) / 2.0;

        forma = escena->addRect(0,0,tamanoItem,tamanoItem,QPen(Qt::NoPen),relleno);

        forma->setPos(x + desplazamiento,y + desplazamiento);
        forma->setZValue(-0.5);
    }
    else{
        forma = escena->addRect(0, 0,tamanoCelda, tamanoCelda,borde, relleno);

        forma->setPos(x, y);
    }
    if (tipo == Tipo::vacio && item == TipoItem::Ninguno)
    {
        forma->setZValue(-1);
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