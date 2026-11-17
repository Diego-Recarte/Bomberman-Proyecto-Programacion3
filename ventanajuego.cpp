#include "ventanajuego.h"



VentanaJuego::VentanaJuego() {

    setWindowTitle("Bomberman - Mi primera ventana");
    escena = new QGraphicsScene(this);
    setScene(escena);
    escena->setSceneRect(0, 0, 1500,  770);
    showMaximized();
    personaje = escena->addRect(0, 0, VentanaJuego:: tamanoJugador, VentanaJuego:: tamanoJugador     );
    personaje->setPos(100, 100);

    mapa = new Mapa(11, 13, 70);
    mapa->crearMapa();
    construirMapa();



    temporizadorMovimiento = new QTimer(this);
    connect(temporizadorMovimiento, &QTimer::timeout,this, &VentanaJuego::actualizarMovimiento);
    temporizadorMovimiento->start(16);

}
void VentanaJuego::keyPressEvent(QKeyEvent* evento){

        if (evento->key() == Qt::Key_D){
            direccion =Direccion::Derecha;
            evento->accept();
            return;
        }else if (evento->key() == Qt::Key_A){
            direccion =Direccion::Izquierda;
            evento->accept();
            return;
        }else if(evento->key()==Qt::Key_W){
             direccion =Direccion::Arriba;
            evento->accept();
            return;

        }else if(evento->key()==Qt::Key_S){
             direccion =Direccion::Abajo;
            evento->accept();
            return;
        }else if (evento->key() == Qt::Key_Space){
            colocarBomba();
            evento->accept();
            return;
        }
        QGraphicsView::keyPressEvent(evento);

}

void VentanaJuego::keyReleaseEvent(QKeyEvent* evento) {
    if (evento->isAutoRepeat())
    {
        evento->accept();
        return;
    }


    if (evento->key() == Qt::Key_D&&direccion ==Direccion::Derecha)
    {
        direccion=Direccion::Null;
        evento->accept();
        return;
    }else if(evento->key()==Qt::Key_A &&direccion ==Direccion::Izquierda){
        direccion=Direccion::Null;
        evento->accept();
        return;
    }else if (evento->key()==Qt::Key_W && direccion ==Direccion::Arriba){
        direccion=Direccion::Null;
        evento->accept();
        return;
    }else if(evento->key()== Qt::Key_S&& direccion ==Direccion::Abajo){
        direccion=Direccion::Null;
        evento->accept();
        return;
    }
    QGraphicsView::keyReleaseEvent(evento);
}

void VentanaJuego::actualizarMovimiento(){

    int x = personaje->pos().x();
    int y = personaje->pos().y();

    switch (direccion){
    case Direccion::Arriba:{
        int filaDestino = (y - movimiento) / mapa->obtenerTamanoCelda();
        int columnaIzquierda = x / mapa->obtenerTamanoCelda();;
        int columnaDerecha = (x + tamanoJugador - 1) / mapa->obtenerTamanoCelda();;

        if (!mapa->esObstaculo(filaDestino, columnaIzquierda) &&!mapa->esObstaculo(filaDestino, columnaDerecha))
        {
            personaje->moveBy(0, -movimiento);
        }
        break;
    }

    case Direccion::Abajo:{
        int filaDestino = (y + tamanoJugador + movimiento-2) / mapa->obtenerTamanoCelda();
        int columnaIzquierda = x / mapa->obtenerTamanoCelda();
        int columnaDerecha = (x + tamanoJugador - 1) / mapa->obtenerTamanoCelda();

        if (!mapa->esObstaculo(filaDestino, columnaIzquierda) &&!mapa->esObstaculo(filaDestino, columnaDerecha)){
            personaje->moveBy(0, movimiento);
        }
        break;
    }

    case Direccion::Derecha:{
        int columnaDestino = (x + tamanoJugador + movimiento-2) / mapa->obtenerTamanoCelda();
        int filaSuperior = y / mapa->obtenerTamanoCelda();
        int filaInferior = (y + tamanoJugador - 1) / mapa->obtenerTamanoCelda();

        if (!mapa->esObstaculo(filaSuperior, columnaDestino) && !mapa->esObstaculo(filaInferior, columnaDestino)){
            personaje->moveBy(movimiento, 0);
        }
        break;
    }

    case Direccion::Izquierda:{
        int columnaDestino = (x - movimiento) / mapa->obtenerTamanoCelda();
        int filaSuperior = y / mapa->obtenerTamanoCelda();
        int filaInferior = (y + tamanoJugador - 1) / mapa->obtenerTamanoCelda();

        if (!mapa->esObstaculo(filaSuperior, columnaDestino) &&!mapa->esObstaculo(filaInferior, columnaDestino)) {
            personaje->moveBy(-movimiento, 0);
        }
        break;
    }

    case Direccion::Null:{
        break;
    }
    }
}



void VentanaJuego::construirMapa(){
    for (int fila = 0; fila <mapa->obtenerFilas();  fila++){
        for (int columna = 0; columna < mapa->obtenerColumnas(); columna++) {
            if (mapa->obtenerMapa()[fila][columna] == 1){
                escena->addRect(columna * mapa->obtenerTamanoCelda(),fila * mapa->obtenerTamanoCelda(), mapa->obtenerTamanoCelda(), mapa->obtenerTamanoCelda());
            }
        }
    }
}





void VentanaJuego::colocarBomba(){
    bomba = escena->addRect(0, 0, tamanoJugador, tamanoJugador, QPen(Qt::black), QBrush(Qt::black));

    bomba->setPos(personaje->pos());
}

