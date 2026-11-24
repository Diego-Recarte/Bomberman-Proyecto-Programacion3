#include "bomba.h"
#include<iostream>
Bomba:: Bomba(int filaInicial, int columnaInicial, int duracionInicialMs, int alcanceInicial){

    std::cout<<"Bomba creada ya"<<std::endl;
    fila = filaInicial;
    columna = columnaInicial;
    tiempo = duracionInicialMs;
    reloj.start();
    alcance=alcanceInicial;

}


Bomba::~Bomba()
{
    if (forma != nullptr)
    {
        if (forma->scene() != nullptr){
            forma->scene()->removeItem(forma);
        }

        delete forma;
        forma = nullptr;
    }
}
void Bomba::dibujar(QGraphicsScene* escena, int tamanoCelda, int tamanioJugador){
    if (forma != nullptr) {
        return;
    }

    forma = escena->addRect(0, 0,   tamanioJugador,  tamanioJugador);
    forma->setBrush(QBrush(Qt::black));
    forma->setPos(columna, fila);
}

bool Bomba::tiempoCumplido()const{

    return reloj.elapsed()>=tiempo; //Qelapsedtimer
}

int Bomba::obtenerX() const
{
    return columna;
}

int Bomba::obtenerY() const
{
    return fila;
}

int Bomba::obtenerAlcance() const{

    return alcance;
}

void Bomba::cambiarAlcance( int i) {

    alcance=i;
}

bool Bomba::seSuperponeCon(double x,double y,double ancho,double alto, int anchoBomba, int altoBomba) const
{

    return x < columna + anchoBomba &&x + ancho > columna &&y < fila + altoBomba &&y + alto > fila;
}