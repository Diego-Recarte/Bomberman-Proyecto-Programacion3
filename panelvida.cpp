#include "panelvida.h"


#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

PanelVida::PanelVida(QGraphicsScene* escena, int x, int y)
{
    this->escena = escena;
    this->x = x;
    this->y = y;

    imagenCorazon = QPixmap(":/corazon");
    imagenCorazonRoto = QPixmap(":/corazonRoto");

    if (imagenCorazon.isNull() || imagenCorazonRoto.isNull()){

        return;
    }

    imagenCorazon = imagenCorazon.scaled(100,100,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    imagenCorazonRoto = imagenCorazonRoto.scaled(100,100,Qt::KeepAspectRatio,Qt::SmoothTransformation);
}

PanelVida::~PanelVida()
{
    while (primero != nullptr)
    {
        NodoCorazon* eliminar = primero;
        primero = primero->siguiente;

        delete eliminar->imagen;
        delete eliminar;
    }

    cantidadCorazones = 0;
}

void PanelVida::agregarCorazon()
{
    if (escena == nullptr || imagenCorazon.isNull())
    {
        return;
    }

    NodoCorazon* nuevo = new NodoCorazon;

    nuevo->imagen = escena->addPixmap(imagenCorazon);

    nuevo->imagen->setPos( x + cantidadCorazones * 50, y );

    nuevo->imagen->setZValue(110);

    if (primero == nullptr){
        primero = nuevo;
    }else{
        NodoCorazon* actual = primero;

        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }

        actual->siguiente = nuevo;
    }

    cantidadCorazones++;
}

void PanelVida::actualizar(int vidaActual, int vidaMaxima)
{
    if (escena == nullptr ||imagenCorazon.isNull() ||imagenCorazonRoto.isNull()){
        return;
    }

    if (vidaMaxima < 0){
        vidaMaxima = 0;
    }

    if (vidaActual < 0){
        vidaActual = 0;
    }
    else if (vidaActual > vidaMaxima){
        vidaActual = vidaMaxima;
    }

    while (cantidadCorazones < vidaMaxima){
        agregarCorazon();
    }

    NodoCorazon* actual = primero;
    int indice = 0;

    while (actual != nullptr){
        actual->imagen->setVisible(indice < vidaMaxima);

        if (indice < vidaActual){
            actual->imagen->setPixmap(imagenCorazon);
        }
        else{
            actual->imagen->setPixmap(imagenCorazonRoto);
        }

        actual = actual->siguiente;
        indice++;
    }
}