#include "sistemaexplosion.h"
#include "colabomba.h"
#include "../Enemigos/gestorenemigos.h"
#include "../MapaYCasillas/mapa.h"
#include "../MapaYCasillas/celda.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>
#include <QTimer>

void SistemaExplosion::configurar(Mapa* mapa, QGraphicsScene* escena, ColaBomba* bombas, int tamanoJugador,
                                  GestorEnemigos* enemigos)
{
    this->mapa = mapa;
    this->escena = escena;
    this->bombas = bombas;
    this->tamanoJugador = tamanoJugador;
    this->enemigos = enemigos;
}
void SistemaExplosion::crearExplosion(int x, int y,  int tamanoCelda, int alcance){
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

    QGraphicsRectItem* flamaCentral = escena->addRect(  0, 0, tamanoFlama, tamanoFlama,  QPen(Qt::red), QBrush(Qt::yellow));
    if (flamaCentral == nullptr) {
        return;
    }
    flamaCentral->setPos(x, y);
    if (enemigos != nullptr) {
        enemigos->recibirExplosionEnCasilla(filaBomba, columnaBomba);
    }
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
            else
            {
                if (enemigos != nullptr) {
                    enemigos->recibirExplosionEnCasilla(filaFlama, columnaBomba);
                }
                if (reaccionEnCadena(filaFlama, columnaBomba, retrasoPorAnillo * distancia)) {
                    direccionValida[0] = false;
                } else {



                    direccionAlcance[0]++;
                }
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
            else
            {
                if (enemigos != nullptr) {
                    enemigos->recibirExplosionEnCasilla(filaFlama, columnaBomba);
                }
                if (reaccionEnCadena(filaFlama, columnaBomba, retrasoPorAnillo * distancia)) {
                    direccionValida[1] = false;
                } else {

                    direccionAlcance[1]++;
                }
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
            else
            {
                if (enemigos != nullptr) {
                    enemigos->recibirExplosionEnCasilla(filaBomba, columnaFlama);
                }
                if (reaccionEnCadena(filaBomba, columnaFlama, retrasoPorAnillo * distancia)) {
                    direccionValida[2] = false;
                } else {


                    direccionAlcance[2]++;
                }
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
            else
            {
                if (enemigos != nullptr) {
                    enemigos->recibirExplosionEnCasilla(filaBomba, columnaFlama);
                }
                if (reaccionEnCadena(filaBomba, columnaFlama, retrasoPorAnillo * distancia)) {
                    direccionValida[3] = false;
                } else {

                    direccionAlcance[3]++;
                }
            }
        }

        //Dibujando explosion una vez que se valida la explosion en caso contrario no se dibuja nada
        QTimer::singleShot(retraso, this, [this, x, y, desplazamiento, i, direccionAlcance](){
            //NORTE

            if (direccionAlcance[0] > i){
                QGraphicsRectItem* flama = escena->addRect(0, 0,   tamanoFlama, tamanoFlama,  QPen(Qt::red),  QBrush(Qt::yellow));

                flama->setPos(x, y - desplazamiento);

                QTimer::singleShot(500, this, [flama](){
                    delete flama;
                });
            }
            //SUR
            if (direccionAlcance[1] > i){
                QGraphicsRectItem* flama = escena->addRect( 0, 0,tamanoFlama, tamanoFlama,QPen(Qt::red),QBrush(Qt::yellow) );

                flama->setPos(x, y + desplazamiento);

                QTimer::singleShot(500, this, [flama](){ delete flama; });
            }
            //OESTE
            if (direccionAlcance[2] > i){
                QGraphicsRectItem* flama = escena->addRect(0, 0, tamanoFlama, tamanoFlama, QPen(Qt::red),QBrush(Qt::yellow));

                flama->setPos(x - desplazamiento, y);

                QTimer::singleShot(500, this, [flama](){
                    delete flama;
                });
            }
            //ESTE
            if (direccionAlcance[3] > i){
                QGraphicsRectItem* flama = escena->addRect(0, 0, tamanoFlama, tamanoFlama, QPen(Qt::red),QBrush(Qt::yellow));

                flama->setPos(x + desplazamiento, y);

                QTimer::singleShot(500, this, [flama]() {
                    delete flama;
                });
            }
        });
    }
}

bool SistemaExplosion::reaccionEnCadena(int filaFlama, int columnaFlama, int retraso){
    if (mapa == nullptr || mapa->obtenerCelda(filaFlama, columnaFlama) == nullptr) {
        return false;
    }

    int xBombaEncontrada = 0;
    int yBombaEncontrada = 0;
    int alcanceBombaEncontrada = 0;


    if (bombas->localizarBomba( filaFlama, columnaFlama,   xBombaEncontrada,yBombaEncontrada, alcanceBombaEncontrada, mapa->obtenerTamanoCelda(),tamanoJugador)){

        QTimer::singleShot(retraso,this,[this, xBombaEncontrada, yBombaEncontrada, alcanceBombaEncontrada, filaFlama, columnaFlama]() {
            crearExplosion(xBombaEncontrada,yBombaEncontrada,mapa->obtenerTamanoCelda(),alcanceBombaEncontrada);
            bombas->eliminarBombaEn( filaFlama,columnaFlama, mapa->obtenerTamanoCelda(),tamanoJugador );

            });

        return true;
    }

    return false;
}

