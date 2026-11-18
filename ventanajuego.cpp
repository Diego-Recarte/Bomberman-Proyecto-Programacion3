#include "ventanajuego.h"
#include<iostream>



VentanaJuego::VentanaJuego() {

    setWindowTitle("Bomberman - Mi primera ventana");
    escena = new QGraphicsScene(this);//QGraphicScence
    setScene(escena);
    escena->setSceneRect(0, 0, 1500,  770);
    this->showFullScreen();

    personaje = escena->addRect(0, 0, VentanaJuego:: tamanoJugador, VentanaJuego:: tamanoJugador     );
    personaje->setPos(100, 100);

    mapa = new Mapa(11, 13, 70);
    mapa->crearMapa();
    construirMapa();




    temporizadorMovimiento = new QTimer(this);
    connect(temporizadorMovimiento, &QTimer::timeout,this, &VentanaJuego::actualizarMovimiento);
    connect(temporizadorMovimiento, &QTimer::timeout, this, &VentanaJuego::actualizarBombas);
    temporizadorMovimiento->start(16);

}

VentanaJuego::~VentanaJuego(){
    bombas.vaciar();
}
void VentanaJuego::keyPressEvent(QKeyEvent* evento){ //keypressevent

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

            if (!evento->isAutoRepeat()){
                colocarBomba();
            }


            evento->accept();
            return;
        }
        QGraphicsView::keyPressEvent(evento);

}

void VentanaJuego::keyReleaseEvent(QKeyEvent* evento) {//KeyreleseEvent
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

    int fila = personaje->pos().y();
    int columna = personaje->pos().x();
    std::cout<<"Agregar"<<std::endl;
    bombas.agregar(fila, columna, 3000,escena);

}


void VentanaJuego::actualizarBombas(){
    while (bombas.primeraBombaVencida()){

        int x = 0;
        int y = 0;
        int alcance;
        if (bombas.obtenerPosicionPrimera(x, y, alcance)){
             crearExplosion(x, y, mapa->obtenerTamanoCelda(),alcance);
        }
        bombas.eliminar();


    }
}


void VentanaJuego::crearExplosion(int x, int y,  int tamanoCelda, int alcance){
    x=x+tamanoJugador/4;
    y=y+tamanoJugador/4;
    QGraphicsRectItem* flamaCentral = escena->addRect(  0, 0, VentanaJuego::tamanoFlama, VentanaJuego::tamanoFlama,  QPen(Qt::red), QBrush(Qt::yellow));
    flamaCentral->setPos(x, y);
    QTimer::singleShot(500, this, [flamaCentral]() {
        delete flamaCentral;
    });
    bool direccionValida[4] = {true, true, true, true};
    int direccionAlcance[4] = {0, 0, 0, 0};

    int filaBomba = y / mapa->obtenerTamanoCelda();
    int columnaBomba = x / mapa->obtenerTamanoCelda();

    for (int i = 0; i < alcance; i++)
    {
        int distancia = i + 1;

        if (direccionValida[0])
        {
            int filaFlama = filaBomba - distancia;

            if (mapa->esObstaculo(filaFlama, columnaBomba))
            {
                direccionValida[0] = false;
            }
            else
            {
                direccionAlcance[0]++;
            }
        }

        if (direccionValida[1])
        {
            int filaFlama = filaBomba + distancia;

            if (mapa->esObstaculo(filaFlama, columnaBomba))
            {
                direccionValida[1] = false;
            }
            else
            {
                direccionAlcance[1]++;
            }
        }

        if (direccionValida[2])
        {
            int columnaFlama = columnaBomba - distancia;

            if (mapa->esObstaculo(filaBomba, columnaFlama))
            {
                direccionValida[2] = false;
            }
            else
            {
                direccionAlcance[2]++;
            }
        }

        if (direccionValida[3])
        {
            int columnaFlama = columnaBomba + distancia;

            if (mapa->esObstaculo(filaBomba, columnaFlama))
            {
                direccionValida[3] = false;
            }
            else
            {
                direccionAlcance[3]++;
            }
        }
    }

    int retrasoPorAnillo = 100;

    for (int i = 0; i < alcance; i++)
    {
        int desplazamiento = tamanoCelda * (i + 1);
        int retraso = retrasoPorAnillo * i;

        QTimer::singleShot(retraso, this, [this, x, y, desplazamiento, i, direccionAlcance](){
           if (direccionAlcance[0] > i){
               QGraphicsRectItem* flama = escena->addRect(0, 0,   VentanaJuego::tamanoFlama, VentanaJuego::tamanoFlama,  QPen(Qt::red),  QBrush(Qt::yellow));

               flama->setPos(x, y - desplazamiento);

               QTimer::singleShot(500, this, [flama](){
                      delete flama;
                });
           }

           if (direccionAlcance[1] > i){
               QGraphicsRectItem* flama = escena->addRect( 0, 0,VentanaJuego::tamanoFlama, VentanaJuego::tamanoFlama,QPen(Qt::red),QBrush(Qt::yellow) );

               flama->setPos(x, y + desplazamiento);

               QTimer::singleShot(500, this, [flama](){ delete flama; });
           }

           if (direccionAlcance[2] > i){
               QGraphicsRectItem* flama = escena->addRect(0, 0, VentanaJuego::tamanoFlama, VentanaJuego::tamanoFlama, QPen(Qt::red),QBrush(Qt::yellow));

               flama->setPos(x - desplazamiento, y);

               QTimer::singleShot(500, this, [flama](){
                   delete flama;
                 });
           }

           if (direccionAlcance[3] > i){
               QGraphicsRectItem* flama = escena->addRect(0, 0, VentanaJuego::tamanoFlama, VentanaJuego::tamanoFlama, QPen(Qt::red),QBrush(Qt::yellow));

               flama->setPos(x + desplazamiento, y);

               QTimer::singleShot(500, this, [flama]() {
                   delete flama;
                });
           }
       });
    }






}