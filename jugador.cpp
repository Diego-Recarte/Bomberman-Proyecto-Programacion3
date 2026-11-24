
#include "jugador.h"

Jugador::Jugador(int x, int y, int tamanio, int velocidadInicial)
{
    figura = new QGraphicsRectItem(0, 0, tamanio, tamanio);
    figura->setPos(x, y);

    direccion = Direccion::Null;

    velocidad = velocidadInicial;
     bombasMaximas=3;
     bombasActivas=0;

     vidaActual=3;
      vidaMaxima=3;
}

QGraphicsRectItem*  Jugador::obtenerFigura(){

    return figura;
}
int Jugador::obtenerVelocidad() const{
    return velocidad;
}


void Jugador::establecerDireccion(Direccion nuevaDireccion){
    direccion = nuevaDireccion;
}

Direccion Jugador::obtenerDireccion() const{
    return direccion;
}


void Jugador::actualizarMovimiento(Mapa* mapa, int tamanoCelda){
    int x = figura->pos().x();
    int y = figura->pos().y();

    switch (direccion)
    {
    case Direccion::Arriba:{
        int filaDestino = (y - velocidad) / tamanoCelda;
        int columnaIzquierda = x / tamanoCelda;
        int columnaDerecha = (x + tamanioJugador - 1) / tamanoCelda;

        if (!mapa->esObstaculo(filaDestino, columnaIzquierda) &&!mapa->esObstaculo(filaDestino, columnaDerecha))
        {

            figura->moveBy(0, -velocidad);
        }
        break;
    }

    case Direccion::Abajo:{
        int filaDestino = (y + tamanioJugador + velocidad-2) / tamanoCelda;
        int columnaIzquierda = x / tamanoCelda;
        int columnaDerecha = (x + tamanioJugador - 1) / mapa->obtenerTamanoCelda();

        if (!mapa->esObstaculo(filaDestino, columnaIzquierda) &&!mapa->esObstaculo(filaDestino, columnaDerecha)){
            figura->moveBy(0, velocidad);
        }
        break;
    }

    case Direccion::Derecha:{
        int columnaDestino = (x + tamanioJugador + velocidad-2) / tamanoCelda;
        int filaSuperior = y / mapa->obtenerTamanoCelda();
        int filaInferior = (y + tamanioJugador - 1) /tamanoCelda;

        if (!mapa->esObstaculo(filaSuperior, columnaDestino) && !mapa->esObstaculo(filaInferior, columnaDestino)){
            figura->moveBy(velocidad, 0);
        }
        break;
    }

    case Direccion::Izquierda:{
        int columnaDestino = (x - velocidad) / tamanoCelda;
        int filaSuperior = y / mapa->obtenerTamanoCelda();
        int filaInferior = (y + tamanioJugador - 1) / tamanoCelda;

        if (!mapa->esObstaculo(filaSuperior, columnaDestino) &&!mapa->esObstaculo(filaInferior, columnaDestino)) {
            figura->moveBy(-velocidad, 0);
        }
        break;
    }

    case Direccion::Null:{
        break;
    }

    }
}

void Jugador::aumentarBombasMaximas(){
    bombasMaximas++;
}

int Jugador::obtenerAlcance() const{
    return alcance;
}

bool Jugador::puedeColocarBomba() const
{
    return bombasActivas < bombasMaximas;
}

void Jugador::bombaColocada()
{
    bombasActivas++;
}

void Jugador::bombaExplotada()
{
    if (bombasActivas > 0)
    {
        bombasActivas--;
    }
}
ColaBomba& Jugador::obtenerBombas(){
    return bombas;
}


int  Jugador::obtenerVidaMaxima(){
    return vidaMaxima;
}
int Jugador::obtenerVidaActual(){
    return vidaActual;

}
void Jugador::aumentarVelocidad(){
    velocidad = velocidad+ 3;
}

PilaItem& Jugador::obtenerItems(){
    return items;
}

void Jugador::aumentarVida(){
    vidaMaxima++;
}
void Jugador::curar(){
    if (vidaMaxima>vidaActual){
        vidaActual++;
    }
}


void Jugador::recogerItem(TipoItem item){




    switch (item){
    case TipoItem::Alcance:{

        break;
    }
    case TipoItem::BombaExtra:{
         aumentarBombasMaximas();
         items.apilar(item);
        break;
    }
    case TipoItem::Velocidad:{
        aumentarVelocidad();
         items.apilar(item);
        break;
    }
    case TipoItem::Portal:{
        break;
    }
    case TipoItem::cura:{
        curar();
        break;
    }
    case TipoItem::masVida:{
        aumentarVida();
        items.apilar(item);
        break;
    }
    case TipoItem::Ninguno:{

        break;
    }
    }


}