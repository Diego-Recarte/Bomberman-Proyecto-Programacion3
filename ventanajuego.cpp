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
        tamanoJugador = jugador->obtenerTamanio();
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
             crearExplosion(x, y, mapa->obtenerTamanoCelda(),alcance);
        }
        bombas.eliminar();


    }
}


void VentanaJuego::crearExplosion(int x, int y,  int tamanoCelda, int alcance){
    if (mapa == nullptr || escena == nullptr || tamanoCelda <= 0 ||
        alcance <= 0 || tamanoJugador <= 0) {
        return;
    }

    x=x+tamanoJugador/4;
    y=y+tamanoJugador/4;
    const int centroY = y + tamanoJugador / 4;
    const int centroX = x + tamanoJugador / 4;
    const int filaBomba = centroY / tamanoCelda;
    const int columnaBomba = centroX / tamanoCelda;
    if (mapa->obtenerCelda(filaBomba, columnaBomba) == nullptr) {
        return;
    }

    QGraphicsRectItem* flamaCentral = escena->addRect(  0, 0, VentanaJuego::tamanoFlama, VentanaJuego::tamanoFlama,  QPen(Qt::red), QBrush(Qt::yellow));
    if (flamaCentral == nullptr) {
        return;
    }
    flamaCentral->setPos(x, y);
    QTimer::singleShot(500, this, [flamaCentral]() {
        delete flamaCentral;
    });
    bool direccionValida[4] = {true, true, true, true};
    int direccionAlcance[4] = {0, 0, 0, 0};



    int retrasoPorAnillo = 100;

    for (int i = 0; i < alcance; i++)
    {
        int distancia = i + 1;
        int desplazamiento = tamanoCelda * (i + 1);
        int retraso = retrasoPorAnillo * i;
        //Validacion para no dibujar la explosion donde no corresponde
        //NORTE
        if (direccionValida[0]){
            int filaFlama = filaBomba - distancia;
            Celda* bomba = mapa->obtenerCelda(filaFlama, columnaBomba);
            if (bomba == nullptr) {
                direccionValida[0] = false;
            }
            else if (bomba->esObstaculo())
            {
                bomba->recibirExplosion();
                direccionValida[0] = false;
            }
            else if (reaccionEnCadena(filaFlama, columnaBomba, retrasoPorAnillo * distancia))
            {
                direccionValida[0] = false;
            }
            else
            {



                direccionAlcance[0]++;
            }
        }
        //SUR
        if (direccionValida[1])
        {
            int filaFlama = filaBomba + distancia;
            Celda* bomba = mapa->obtenerCelda(filaFlama, columnaBomba);
            if (bomba == nullptr) {
                direccionValida[1] = false;
            }
            else if (bomba->esObstaculo())
            {
                bomba->recibirExplosion();
                direccionValida[1] = false;
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
        //OESTE
        if (direccionValida[2])
        {
            int columnaFlama = columnaBomba - distancia;
            Celda* bomba = mapa->obtenerCelda(filaBomba, columnaFlama);
            if (bomba == nullptr) {
                direccionValida[2] = false;
            }
            else if (bomba->esObstaculo())
            {
                bomba->recibirExplosion();
                direccionValida[2] = false;
            }
            else if (reaccionEnCadena(filaBomba,  columnaFlama, retrasoPorAnillo * distancia)) {
                direccionValida[2] = false;
            }
            else
            {


                direccionAlcance[2]++;
            }
        }
        //ESTE
        if (direccionValida[3]){
            int columnaFlama = columnaBomba + distancia;
            Celda* bomba = mapa->obtenerCelda(filaBomba, columnaFlama);
            if (bomba == nullptr) {
                direccionValida[3] = false;
            }
            else if (bomba->esObstaculo())
            {
                bomba->recibirExplosion();
                direccionValida[3] = false;
            }
            else if (reaccionEnCadena(filaBomba,  columnaFlama,retrasoPorAnillo * distancia)) {
                direccionValida[3] = false;
            }

            else
            {

                direccionAlcance[3]++;
            }
        }

        //Dibujando explosion una vez que se valida la explosion en caso contrario no se dibuja nada
        QTimer::singleShot(retraso, this, [this, x, y, desplazamiento, i, direccionAlcance](){
            //NORTE

            if (direccionAlcance[0] > i){
                QGraphicsRectItem* flama = escena->addRect(0, 0,   VentanaJuego::tamanoFlama, VentanaJuego::tamanoFlama,  QPen(Qt::red),  QBrush(Qt::yellow));

                flama->setPos(x, y - desplazamiento);

                QTimer::singleShot(500, this, [flama](){
                    delete flama;
                });
            }
            //SUR
            if (direccionAlcance[1] > i){
                QGraphicsRectItem* flama = escena->addRect( 0, 0,VentanaJuego::tamanoFlama, VentanaJuego::tamanoFlama,QPen(Qt::red),QBrush(Qt::yellow) );

                flama->setPos(x, y + desplazamiento);

                QTimer::singleShot(500, this, [flama](){ delete flama; });
            }
            //OESTE
            if (direccionAlcance[2] > i){
                QGraphicsRectItem* flama = escena->addRect(0, 0, VentanaJuego::tamanoFlama, VentanaJuego::tamanoFlama, QPen(Qt::red),QBrush(Qt::yellow));

                flama->setPos(x - desplazamiento, y);

                QTimer::singleShot(500, this, [flama](){
                    delete flama;
                });
            }
            //ESTE
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

bool VentanaJuego::reaccionEnCadena(int filaFlama, int columnaFlama, int retraso){
    if (mapa == nullptr || mapa->obtenerCelda(filaFlama, columnaFlama) == nullptr) {
        return false;
    }

    int xBombaEncontrada = 0;
    int yBombaEncontrada = 0;
    int alcanceBombaEncontrada = 0;


    if (bombas.localizarBomba( filaFlama, columnaFlama,   xBombaEncontrada,yBombaEncontrada, alcanceBombaEncontrada, mapa->obtenerTamanoCelda(),VentanaJuego::tamanoJugador)){

        QTimer::singleShot(retraso,this,[this, xBombaEncontrada, yBombaEncontrada, alcanceBombaEncontrada, filaFlama, columnaFlama]() {
            crearExplosion(xBombaEncontrada,yBombaEncontrada,mapa->obtenerTamanoCelda(),alcanceBombaEncontrada);
            bombas.eliminarBombaEn( filaFlama,columnaFlama, mapa->obtenerTamanoCelda(),VentanaJuego::tamanoJugador );

            });

        return true;
    }

    return false;
}

