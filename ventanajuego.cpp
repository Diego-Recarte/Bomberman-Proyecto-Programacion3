#include "ventanajuego.h"
#include<iostream>
#include <QBrush>
#include <QGraphicsTextItem>
#include <QFont>
#include <QPen>


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
        enemigos.crearEnemigos(mapa, escena,
                               jugador->obtenerFilaActual(),
                               jugador->obtenerColumnaActual(), 3);
        sistemaExplosion.configurar(mapa, escena, &bombas,
                                    jugador->obtenerTamanio(), &enemigos);
        QGraphicsRectItem* personaje = jugador->obtenerPersonaje();
        if (escena != nullptr && personaje != nullptr) {
            escena->addItem(personaje);
        }
    }

    crearInterfaz();

    temporizadorMovimiento = new QTimer(this);

    connect(temporizadorMovimiento, &QTimer::timeout,
            this, [this]() {
                if (jugador != nullptr) {
                    jugador->actualizarMovimiento(&bombas);
                }
            });

    connect(temporizadorMovimiento, &QTimer::timeout,
            this, &VentanaJuego::actualizarBombas);

    connect(temporizadorMovimiento, &QTimer::timeout,
            this, &VentanaJuego::actualizarPartida);

    temporizadorMovimiento->start(16);
}

void VentanaJuego::crearInterfaz()
{
    if (escena == nullptr) {
        return;
    }

    barraVidaFondo = escena->addRect(0, 0, 184, 24, QPen(Qt::black), QBrush(Qt::darkGray));
    barraVida = escena->addRect(0, 0, 180, 20, QPen(Qt::NoPen), QBrush(Qt::red));
    if (barraVidaFondo != nullptr) {
        barraVidaFondo->setPos(18, 18);
        barraVidaFondo->setZValue(100);
    }
    if (barraVida != nullptr) {
        barraVida->setPos(20, 20);
        barraVida->setZValue(101);
    }

    textoVida = escena->addText("");
    if (textoVida != nullptr) {
        textoVida->setDefaultTextColor(Qt::white);
        textoVida->setFont(QFont("Arial", 12, QFont::Bold));
        textoVida->setPos(20, 45);
        textoVida->setZValue(102);
    }

    textoResultado = escena->addText("");
    if (textoResultado != nullptr) {
        textoResultado->setDefaultTextColor(Qt::white);
        textoResultado->setFont(QFont("Arial", 28, QFont::Bold));
        textoResultado->setPos(560, 340);
        textoResultado->setZValue(200);
        textoResultado->setVisible(false);
    }

    actualizarInterfazVida();
}

void VentanaJuego::actualizarPartida()
{
    if (estadoPartida != EstadoPartida::EnCurso) {
        return;
    }

    if (jugador != nullptr) {
        jugador->actualizarTemporizadores(16);
        enemigos.actualizar(16, jugador, &bombas);
    }

    actualizarInterfazVida();

    if (jugador == nullptr || jugador->obtenerVida() <= 0) {
        finalizarPartida(false);
    } else if (enemigos.obtenerCantidad() == 0) {
        finalizarPartida(true);
    }
}

void VentanaJuego::actualizarInterfazVida()
{
    if (jugador == nullptr) {
        return;
    }

    const int vida = jugador->obtenerVida();
    const int vidaMaxima = jugador->obtenerVidaMaxima();
    if (barraVida != nullptr && vidaMaxima > 0) {
        const qreal ancho = 180.0 * vida / vidaMaxima;
        barraVida->setRect(0, 0, ancho, 20);
    }
    if (textoVida != nullptr) {
        textoVida->setPlainText(QString("Vida: %1 / %2").arg(vida).arg(vidaMaxima));
    }
}

void VentanaJuego::finalizarPartida(bool victoria)
{
    if (estadoPartida != EstadoPartida::EnCurso) {
        return;
    }

    estadoPartida = victoria ? EstadoPartida::Victoria : EstadoPartida::Derrota;
    if (temporizadorMovimiento != nullptr) {
        temporizadorMovimiento->stop();
    }
    if (textoResultado != nullptr) {
        textoResultado->setPlainText(victoria ? "¡Victoria!" : "¡Derrota!");
        textoResultado->setVisible(true);
    }
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
    bombas.agregar(fila, columna, 3000, escena,
                   mapa->obtenerTamanoCelda(), jugador->obtenerTamanio());

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
