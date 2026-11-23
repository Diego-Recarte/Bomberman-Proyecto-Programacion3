#include "ventanajuego.h"
#include<iostream>


VentanaJuego::VentanaJuego()
{
    setWindowTitle("Bomberman - Mi primera ventana");

    escena = new QGraphicsScene(this);
    setScene(escena);

    escena->setSceneRect(0, 0, 1500, 770);

    this->showFullScreen();

    mapa = new Mapa(11, 13, 70);
    mapa->crearMapa();

    construirMapa();

    jugador = new Jugador(mapa);
    if (jugador != nullptr) {
        sistemaExplosion.configurar(mapa, escena, &bombas, jugador->obtenerTamanio());
        QGraphicsRectItem* personaje = jugador->obtenerPersonaje();
        if (escena != nullptr && personaje != nullptr) {
            escena->addItem(personaje);
        }
    }

    temporizadorMovimiento = new QTimer(this);

    connect(temporizadorMovimiento, &QTimer::timeout,
            this, [this]() {
                if (jugador != nullptr) {
                    jugador->actualizarMovimiento();
                }
            });

    connect(temporizadorMovimiento, &QTimer::timeout,
            this, &VentanaJuego::actualizarBombas);

    temporizadorMovimiento->start(16);
}

VentanaJuego::~VentanaJuego(){
    bombas.vaciar();
}
void VentanaJuego::keyPressEvent(QKeyEvent* evento)
{
    if (evento == nullptr) {
        return;
    }

    if (evento->key() == Qt::Key_Space) {

        if (!evento->isAutoRepeat()) {
            colocarBomba();
        }

        evento->accept();
        return;
    }

    if (jugador != nullptr) {
        jugador->presionarTecla(evento);
    }

    if (!evento->isAccepted()) {
        QGraphicsView::keyPressEvent(evento);
    }
}

void VentanaJuego::keyReleaseEvent(QKeyEvent* evento)
{
    if (evento == nullptr) {
        return;
    }

    if (jugador != nullptr) {
        jugador->soltarTecla(evento);
    }

    if (!evento->isAccepted()) {
        QGraphicsView::keyReleaseEvent(evento);
    }
}



void VentanaJuego::construirMapa(){
    if (mapa == nullptr || escena == nullptr) {
        return;
    }

    for (int fila = 0; fila <mapa->obtenerFilas();  fila++){
        for (int columna = 0; columna < mapa->obtenerColumnas(); columna++) {
                Celda* celda = mapa->obtenerCelda(fila, columna);
                if (celda != nullptr) {
                    celda->dibujar(escena, columna * mapa->obtenerTamanoCelda(),
                                   fila * mapa->obtenerTamanoCelda(), mapa->obtenerTamanoCelda());
                }

        }
    }
}



void VentanaJuego::colocarBomba(){
    if (jugador == nullptr || escena == nullptr || mapa == nullptr) {
        return;
    }

    QGraphicsRectItem* personaje = jugador->obtenerPersonaje();
    if (personaje == nullptr) {
        return;
    }

    int fila = personaje->pos().y();
    int columna = personaje->pos().x();
    std::cout<<"Agregar"<<std::endl;
    bombas.agregar(fila, columna, 3000,escena);

}


void VentanaJuego::actualizarBombas(){
    if (mapa == nullptr) {
        return;
    }

    while (bombas.primeraBombaVencida()){

        int x = 0;
        int y = 0;
        int alcance;
        if (bombas.obtenerPosicionPrimera(x, y, alcance)){
             sistemaExplosion.crearExplosion(x, y, mapa->obtenerTamanoCelda(),alcance);
        }
        bombas.eliminar();


    }
}
