#include "ventanajuego.h"
#include<iostream>



VentanaJuego::VentanaJuego() {

    setWindowTitle("Bomberman - Mi primera ventana");
    escena = new QGraphicsScene(this);//QGraphicScence
    setScene(escena);
    escena->setSceneRect(0, 0, 1500,  770);

    this->showFullScreen();


    jugador = new Jugador(100, 100, tamanoJugador, 5);
    escena->addItem(jugador->obtenerFigura());



    mapa = new Mapa(11, 13, 70);
    mapa->crearMapa();
    construirMapa();




    temporizadorMovimiento = new QTimer(this);
    connect(temporizadorMovimiento, &QTimer::timeout,this, &VentanaJuego::actualizarMovimiento);
    connect(temporizadorMovimiento, &QTimer::timeout, this, &VentanaJuego::revisarItemsJugador);
    connect(temporizadorMovimiento, &QTimer::timeout, this, &VentanaJuego::actualizarBombas);
    temporizadorMovimiento->start(16);

}

VentanaJuego::~VentanaJuego(){

}
void VentanaJuego::keyPressEvent(QKeyEvent* evento){ //keypressevent

        if (evento->key() == Qt::Key_D){
            jugador->establecerDireccion(Direccion::Derecha);
            evento->accept();
            return;
        }else if (evento->key() == Qt::Key_A){
            jugador->establecerDireccion(Direccion::Izquierda);
            evento->accept();
            return;
        }else if(evento->key()==Qt::Key_W){
             jugador->establecerDireccion(Direccion::Arriba);
            evento->accept();
            return;

        }else if(evento->key()==Qt::Key_S){
            jugador->establecerDireccion(Direccion::Abajo);
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


    if (evento->key() == Qt::Key_D&& jugador->obtenerDireccion() ==Direccion::Derecha)
    {
        jugador->establecerDireccion(Direccion::Null);
        evento->accept();
        return;
    }else if(evento->key()==Qt::Key_A && jugador->obtenerDireccion() ==Direccion::Izquierda){
        jugador->establecerDireccion(Direccion::Null);
        evento->accept();
        return;
    }else if (evento->key()==Qt::Key_W && jugador->obtenerDireccion() ==Direccion::Arriba){
        jugador->establecerDireccion(Direccion::Null);
        evento->accept();
        return;
    }else if(evento->key()== Qt::Key_S&& jugador->obtenerDireccion() ==Direccion::Abajo){
        jugador->establecerDireccion(Direccion::Null);
        evento->accept();
        return;
    }
    QGraphicsView::keyReleaseEvent(evento);
}

void VentanaJuego::actualizarMovimiento(){


        jugador->actualizarMovimiento(mapa, mapa->obtenerTamanoCelda());
}




void VentanaJuego::construirMapa(){
    for (int fila = 0; fila <mapa->obtenerFilas();  fila++){
        for (int columna = 0; columna < mapa->obtenerColumnas(); columna++) {
            mapa->obtenerCelda(fila, columna)->dibujar(escena,columna * mapa->obtenerTamanoCelda(),fila * mapa->obtenerTamanoCelda(),mapa->obtenerTamanoCelda(),VentanaJuego::tamanoJugador);
        }
    }
}





void VentanaJuego::colocarBomba()
{
    if (!jugador->puedeColocarBomba())
    {
        return;
    }

    int fila = jugador->obtenerFigura()->pos().y();
    int columna = jugador->obtenerFigura()->pos().x();

    jugador->obtenerBombas().agregar(fila, columna, 3000, jugador->obtenerAlcance(), escena);
    jugador->bombaColocada();
}


void VentanaJuego::actualizarBombas(){
    while (jugador->obtenerBombas().primeraBombaVencida()){

        int x = 0;
        int y = 0;
        int alcance;
        if (jugador->obtenerBombas().obtenerPosicionPrimera(x, y, alcance)){
             crearExplosion(x, y, mapa->obtenerTamanoCelda(),alcance);
        }
        jugador->obtenerBombas().eliminar();
        jugador->bombaExplotada();

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
    int limiteDireccion[4] = {alcance, alcance, alcance, alcance};



    int centroY = y + VentanaJuego::tamanoJugador / 4;
    int centroX = x + VentanaJuego::tamanoJugador / 4;


    int filaBomba = centroY / mapa->obtenerTamanoCelda();
    int columnaBomba = centroX / mapa->obtenerTamanoCelda();


    int retrasoPorAnillo = 100;

    for (int i = 0; i < limiteDireccion[0] ||i < limiteDireccion[1] ||i < limiteDireccion[2] || i < limiteDireccion[3]; i++){
        int distancia = i + 1;

        if (direccionValida[0] && i < limiteDireccion[0]){
            int filaFlama = filaBomba - distancia;
            Celda* bomba= mapa->obtenerCelda(filaFlama, columnaBomba);
            if (bomba->esObstaculo()){

                bomba->recibirExplosion();

                bool cajaDestruida = bomba->estaDestruida();

                if (cajaDestruida){
                    direccionAlcance[0]++;
                }
                bool activoItem = (bomba->obtenerItem() == TipoItem::Portal||bomba->obtenerItem() == TipoItem::BombaExtra||bomba->obtenerItem() == TipoItem::Velocidad||bomba->obtenerItem() == TipoItem::cura||bomba->obtenerItem() == TipoItem::masVida  )&& (cajaDestruida);

                bool activoAlcance = bomba->obtenerItem() == TipoItem::Alcance && (cajaDestruida);



                if (activoAlcance){
                    limiteDireccion[0] = limiteDireccion[0] + tamanoItemAlcance;
                }

                if (activoItem){

                    bomba->setItemDisponible();

                   }

                if (!activoAlcance){
                    direccionValida[0] = false;
                }
            }else if (reaccionEnCadena(filaFlama, columnaBomba, retrasoPorAnillo * distancia))
            {
                direccionValida[0] = false;
            }
            else
            {

                direccionAlcance[0]++;
            }
        }

        if (direccionValida[1] && i < limiteDireccion[1])
        {
            int filaFlama = filaBomba + distancia;
            Celda* bomba= mapa->obtenerCelda(filaFlama, columnaBomba);
            if (bomba->esObstaculo()){

                bomba->recibirExplosion();

                bool cajaDestruida = bomba->estaDestruida();

                if (cajaDestruida){
                    direccionAlcance[1]++;
                }
                bool activoItem = (bomba->obtenerItem() == TipoItem::Portal||bomba->obtenerItem() == TipoItem::BombaExtra||bomba->obtenerItem() == TipoItem::Velocidad||bomba->obtenerItem() == TipoItem::cura||bomba->obtenerItem() == TipoItem::masVida  )&& (cajaDestruida);

                bool activoAlcance = bomba->obtenerItem() == TipoItem::Alcance && (cajaDestruida);




                if (activoAlcance){
                    limiteDireccion[1] = limiteDireccion[1] + tamanoItemAlcance;
                }

                if (activoItem){

                    bomba->setItemDisponible();

                     }

                if (!activoAlcance){
                    direccionValida[1] = false;
                }

            }
            else if (reaccionEnCadena(filaFlama, columnaBomba, retrasoPorAnillo * distancia))
            {
                direccionValida[1] = false;
            }
            else
            {

                direccionAlcance[1]++;
            }
        }

        if (direccionValida[2] && i < limiteDireccion[2]){
            int columnaFlama = columnaBomba - distancia;
            Celda* bomba= mapa->obtenerCelda(filaBomba, columnaFlama);
            if (bomba->esObstaculo()){

                bomba->recibirExplosion();

                bool cajaDestruida = bomba->estaDestruida();

                if (cajaDestruida){
                    direccionAlcance[2]++;

                }
                bool activoItem = (bomba->obtenerItem() == TipoItem::Portal||bomba->obtenerItem() == TipoItem::BombaExtra||bomba->obtenerItem() == TipoItem::Velocidad||bomba->obtenerItem() == TipoItem::cura||bomba->obtenerItem() == TipoItem::masVida  )&& (cajaDestruida);

                bool activoAlcance = bomba->obtenerItem() == TipoItem::Alcance && (cajaDestruida);



                if (activoAlcance){
                    limiteDireccion[2] = limiteDireccion[2] + tamanoItemAlcance;
                }

                if (activoItem ){

                    bomba->setItemDisponible();
                }

                if (!activoAlcance ){
                    direccionValida[2] = false;
                }



            }
            else if (reaccionEnCadena(filaBomba,  columnaFlama, retrasoPorAnillo * distancia)) {
                direccionValida[2] = false;
            }
            else
            {


                direccionAlcance[2]++;
            }
        }

        if (direccionValida[3] && i < limiteDireccion[3]){

                int columnaFlama = columnaBomba + distancia;
                Celda* bomba = mapa->obtenerCelda(filaBomba, columnaFlama);

                if (bomba->esObstaculo()) {

                    bomba->recibirExplosion();

                    bool cajaDestruida = bomba->estaDestruida();

                    if (cajaDestruida){
                        direccionAlcance[3]++;
                    }

                    bool activoItem = (bomba->obtenerItem() == TipoItem::Portal||bomba->obtenerItem() == TipoItem::BombaExtra||bomba->obtenerItem() == TipoItem::Velocidad||bomba->obtenerItem() == TipoItem::cura||bomba->obtenerItem() == TipoItem::masVida  )&& (cajaDestruida);
                    bool activoAlcance =bomba->obtenerItem() == TipoItem::Alcance;


                    if (activoAlcance){
                        limiteDireccion[3] = limiteDireccion[3] + tamanoItemAlcance;
                    }

                    if (activoItem){

                        bomba->setItemDisponible();

                    }


                    if (!activoAlcance){
                        direccionValida[3] = false;
                    }
                }
                else if (reaccionEnCadena(filaBomba, columnaFlama, retrasoPorAnillo * distancia))
                {
                    direccionValida[3] = false;
                }
                else
                {
                    direccionAlcance[3]++;
                }

        }
    }

    std::cout << "Flamas derecha al final: " << direccionAlcance[3] << std::endl;


    for (int i = 0; i <   direccionAlcance[0] ||i < direccionAlcance[1] ||i < direccionAlcance[2] || i < direccionAlcance[3]; i++) {
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

void VentanaJuego::revisarItemsJugador(){
    int x = jugador->obtenerFigura()->pos().x();
    int y = jugador->obtenerFigura()->pos().y();

    int fila = (y + tamanoJugador / 4) / mapa->obtenerTamanoCelda();
    int columna = (x + tamanoJugador / 4) / mapa->obtenerTamanoCelda();

    Celda* celda = mapa->obtenerCelda(fila, columna);

    if (celda->isItemDisponible()&&celda->obtenerItem()==TipoItem::Portal){
        std::cout<<"gano"<<std::endl;
    }

    if (celda->isItemDisponible() &&celda->obtenerItem()!=TipoItem::Portal ){
        jugador->recogerItem(celda->obtenerItem());
        celda->consumirItem();
    }
}

bool VentanaJuego::reaccionEnCadena(int filaFlama, int columnaFlama, int retraso){
    int xBombaEncontrada = 0;
    int yBombaEncontrada = 0;
    int alcanceBombaEncontrada = 0;


    if (jugador->obtenerBombas().localizarBomba( filaFlama, columnaFlama,   xBombaEncontrada,yBombaEncontrada, alcanceBombaEncontrada, mapa->obtenerTamanoCelda(),VentanaJuego::tamanoJugador)){

        QTimer::singleShot(retraso, this, [this, xBombaEncontrada, yBombaEncontrada, alcanceBombaEncontrada, filaFlama, columnaFlama]() {
            crearExplosion(xBombaEncontrada, yBombaEncontrada, mapa->obtenerTamanoCelda(), alcanceBombaEncontrada);

            jugador->obtenerBombas().eliminarBombaEn(filaFlama, columnaFlama, mapa->obtenerTamanoCelda(), VentanaJuego::tamanoJugador);

            jugador->bombaExplotada();
        });

        return true;
    }

    return false;
}

