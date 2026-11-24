
#include "jugador.h"

Jugador::Jugador(int x, int y, int tamanio, int velocidadInicial, Mapa* mapa)
    : mapa(mapa)
{
    figura = new QGraphicsRectItem(0, 0, tamanio, tamanio);
    figura->setPos(x, y);
    figura->setBrush(QBrush(Qt::white));
    direccion = Direccion::Null;

    velocidad = velocidadInicial;
     bombasMaximas=3;
     bombasActivas=0;

     vidaActual=3;
      vidaMaxima=3;
}

Jugador::~Jugador()
{
    if (figura != nullptr) {
        if (figura->scene() != nullptr) {
            figura->scene()->removeItem(figura);
        }
        delete figura;
    }
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


void Jugador::actualizarMovimiento(Mapa* mapa, int tamanoCelda,
                                   const ColaBomba* bombasActivas){
    if (mapa == nullptr || tamanoCelda <= 0) {
        return;
    }
    int x = figura->pos().x();
    int y = figura->pos().y();
    const int filaActual = (y + tamanioJugador / 2) / tamanoCelda;
    const int columnaActual = (x + tamanioJugador / 2) / tamanoCelda;

    switch (direccion)
    {
    case Direccion::Arriba:{
        int filaDestino = (y - velocidad) / tamanoCelda;
        int columnaIzquierda = x / tamanoCelda;
        int columnaDerecha = (x + tamanioJugador - 1) / tamanoCelda;

        if (casillaLibre(mapa, filaDestino, columnaIzquierda, tamanoCelda,
                         bombasActivas, filaActual, columnaActual) &&
            casillaLibre(mapa, filaDestino, columnaDerecha, tamanoCelda,
                         bombasActivas, filaActual, columnaActual))
        {

            figura->moveBy(0, -velocidad);
        }
        break;
    }

    case Direccion::Abajo:{
        int filaDestino = (y + tamanioJugador + velocidad-2) / tamanoCelda;
        int columnaIzquierda = x / tamanoCelda;
        int columnaDerecha = (x + tamanioJugador - 1) / mapa->obtenerTamanoCelda();

        if (!mapa->esObstaculo(filaDestino, columnaIzquierda) &&
            !mapa->esObstaculo(filaDestino, columnaDerecha) &&
            casillaLibre(mapa, filaDestino, columnaIzquierda, tamanoCelda,
                         bombasActivas, filaActual, columnaActual) &&
            casillaLibre(mapa, filaDestino, columnaDerecha, tamanoCelda,
                         bombasActivas, filaActual, columnaActual)){
            figura->moveBy(0, velocidad);
        }
        break;
    }

    case Direccion::Derecha:{
        int columnaDestino = (x + tamanioJugador + velocidad-2) / tamanoCelda;
        int filaSuperior = y / mapa->obtenerTamanoCelda();
        int filaInferior = (y + tamanioJugador - 1) /tamanoCelda;

        if (casillaLibre(mapa, filaSuperior, columnaDestino, tamanoCelda,
                         bombasActivas, filaActual, columnaActual) &&
            casillaLibre(mapa, filaInferior, columnaDestino, tamanoCelda,
                         bombasActivas, filaActual, columnaActual)){
            figura->moveBy(velocidad, 0);
        }
        break;
    }

    case Direccion::Izquierda:{
        int columnaDestino = (x - velocidad) / tamanoCelda;
        int filaSuperior = y / mapa->obtenerTamanoCelda();
        int filaInferior = (y + tamanioJugador - 1) / tamanoCelda;

        if (casillaLibre(mapa, filaSuperior, columnaDestino, tamanoCelda,
                         bombasActivas, filaActual, columnaActual) &&
            casillaLibre(mapa, filaInferior, columnaDestino, tamanoCelda,
                         bombasActivas, filaActual, columnaActual)) {
            figura->moveBy(-velocidad, 0);
        }
        break;
    }

    case Direccion::Null:{
        break;
    }

    }
}

bool Jugador::casillaLibre(Mapa* mapa, int fila, int columna, int tamanoCelda,
                           const ColaBomba* bombasActivas,
                           int filaActual, int columnaActual) const
{
    if (mapa == nullptr || mapa->esObstaculo(fila, columna)) {
        return false;
    }
    if (bombasActivas == nullptr ||
        !bombasActivas->existeBombaEn(fila, columna, tamanoCelda, tamanioJugador)) {
        return true;
    }
    return fila == filaActual && columna == columnaActual;
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


int Jugador::obtenerVidaMaxima() const{
    return vidaMaxima;
}
int Jugador::obtenerVidaActual() const{
    return vidaActual;

}

int Jugador::obtenerVida() const
{
    return vidaActual;
}

void Jugador::recibirDanio(int cantidad)
{
    if (cantidad <= 0 || vidaActual <= 0 || cooldownDanioMs > 0) {
        return;
    }
    vidaActual -= cantidad;
    if (vidaActual < 0) {
        vidaActual = 0;
    }
    cooldownDanioMs = 800;
}

void Jugador::actualizarTemporizadores(int milisegundos)
{
    if (cooldownDanioMs > 0) {
        cooldownDanioMs -= milisegundos;
        if (cooldownDanioMs < 0) {
            cooldownDanioMs = 0;
        }
    }
}

int Jugador::obtenerFilaActual() const
{
    if (figura == nullptr || mapa == nullptr || mapa->obtenerTamanoCelda() <= 0) {
        return -1;
    }
    return (static_cast<int>(figura->pos().y()) + tamanioJugador / 2) /
           mapa->obtenerTamanoCelda();
}

int Jugador::obtenerColumnaActual() const
{
    if (figura == nullptr || mapa == nullptr || mapa->obtenerTamanoCelda() <= 0) {
        return -1;
    }
    return (static_cast<int>(figura->pos().x()) + tamanioJugador / 2) /
           mapa->obtenerTamanoCelda();
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
