
#include "jugador.h"

Jugador::Jugador(int x, int y, int tamanio, int velocidadInicial, Mapa* mapa): mapa(mapa)
{
    figura = new QGraphicsRectItem(0, 0, tamanio, tamanio);
    figura->setPos(x, y);
    figura->setBrush(QBrush(Qt::white));
    direccion = Direccion::Null;
    tamanioJugador = tamanio;

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


void Jugador::actualizarMovimiento(Mapa* mapa, int tamanoCelda){
    if (mapa == nullptr || figura == nullptr || tamanoCelda <= 0) {
        return;
    }


    int dx = 0;
    int dy = 0;

    switch (direccion) {
    case Direccion::Arriba:
        dy = -velocidad;
        break;

    case Direccion::Abajo:
        dy = velocidad;
        break;

    case Direccion::Derecha:
        dx = velocidad;
        break;

    case Direccion::Izquierda:
        dx = -velocidad;
        break;

    case Direccion::Null:
        return;
    }
    if (bombas.obtenerCantidad() != 0 &&bombas.bloqueaMovimiento(figura->pos().x(),figura->pos().y(),tamanioJugador,tamanioJugador,dx,dy,tamanioJugador)) {
        return;
    }



    int x = figura->pos().x();
    int y = figura->pos().y();

    switch (direccion)
    {
    case Direccion::Arriba:{
        int filaDestino = (y - velocidad) / tamanoCelda;
        int columnaIzquierda = x / tamanoCelda;
        int columnaDerecha = (x + tamanioJugador - 1) / tamanoCelda;

        if (casillaLibre(mapa, filaDestino, columnaIzquierda) && casillaLibre(mapa, filaDestino, columnaDerecha)){

            figura->moveBy(0, -velocidad);
        }
        break;
    }

    case Direccion::Abajo:{
        int filaDestino = (y + tamanioJugador + velocidad-2) / tamanoCelda;
        int columnaIzquierda = x / tamanoCelda;
        int columnaDerecha = (x + tamanioJugador - 1) / mapa->obtenerTamanoCelda();

        if (!mapa->esObstaculo(filaDestino, columnaIzquierda) &&!mapa->esObstaculo(filaDestino, columnaDerecha) &&casillaLibre(mapa, filaDestino, columnaIzquierda) &&casillaLibre(mapa, filaDestino, columnaDerecha)){
            figura->moveBy(0, velocidad);
        }
        break;
    }

    case Direccion::Derecha:{
        int columnaDestino = (x + tamanioJugador + velocidad-2) / tamanoCelda;
        int filaSuperior = y / mapa->obtenerTamanoCelda();
        int filaInferior = (y + tamanioJugador - 1) /tamanoCelda;

        if (casillaLibre(mapa, filaSuperior, columnaDestino) &&casillaLibre(mapa, filaInferior, columnaDestino)){
            figura->moveBy(velocidad, 0);
        }
        break;
    }

    case Direccion::Izquierda:{
        int columnaDestino = (x - velocidad) / tamanoCelda;
        int filaSuperior = y / mapa->obtenerTamanoCelda();
        int filaInferior = (y + tamanioJugador - 1) / tamanoCelda;

        if (casillaLibre(mapa, filaSuperior, columnaDestino) &&casillaLibre(mapa, filaInferior, columnaDestino)) {
            figura->moveBy(-velocidad, 0);
        }
        break;
    }

    case Direccion::Null:{
        break;
    }

    }
}

bool Jugador::casillaLibre( Mapa* mapa, int fila, int columna) const
{
    return mapa != nullptr &&!mapa->esObstaculo(fila, columna);
}

void Jugador::aumentarBombasMaximas(){
    bombasMaximas++;
}

int Jugador::obtenerAlcance() const{
    return alcance;
}

bool Jugador::puedeColocarBomba() const{
    return bombasActivas < bombasMaximas;
}

void Jugador::bombaColocada(){
    bombasActivas++;
}

void Jugador::bombaExplotada(){
    if (bombasActivas > 0){
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
    return (static_cast<int>(figura->pos().y()) + tamanioJugador / 4) /mapa->obtenerTamanoCelda();
}

int Jugador::obtenerColumnaActual() const
{
    if (figura == nullptr || mapa == nullptr || mapa->obtenerTamanoCelda() <= 0) {
        return -1;
    }
    return (static_cast<int>(figura->pos().x()) + tamanioJugador / 4) / mapa->obtenerTamanoCelda();
}
void Jugador::aumentarVelocidad(){
    velocidad = velocidad+ 2;
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

bool Jugador::calcularCasillaInteraccion(int& fila,int& columna,int dx,int dy) const{
    if (figura == nullptr || mapa == nullptr) {
        return false;
    }

    const int tamanoCelda = mapa->obtenerTamanoCelda();

    if (tamanoCelda <= 0) {
        return false;
    }

    const int x = static_cast<int>(figura->pos().x());
    const int y = static_cast<int>(figura->pos().y());

    const int puntoX = x + dx + tamanioJugador / 4;
    const int puntoY = y + dy + tamanioJugador / 4;

    if (puntoX < 0 || puntoY < 0) {
        return false;
    }

    fila = puntoY / tamanoCelda;
    columna = puntoX / tamanoCelda;

    return true;
}
