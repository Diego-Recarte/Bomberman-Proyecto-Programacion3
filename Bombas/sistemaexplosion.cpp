#include "sistemaexplosion.h"
#include "colabomba.h"
#include "../Jugador/jugador.h"
#include "../Enemigos/gestorenemigos.h"
#include "../MapaYCasillas/mapa.h"
#include "../MapaYCasillas/celda.h"
#include "../Item/tipoitem.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>
#include <QTimer>

SistemaExplosion::NodoCasillaEnLlamas::NodoCasillaEnLlamas( int fila, int columna, int inicioMs, int finMs,NodoCasillaEnLlamas* siguiente): fila(fila), columna(columna), inicioMs(inicioMs), finMs(finMs),siguiente(siguiente){
}

SistemaExplosion::~SistemaExplosion()
{
    while (primeraExplosion != nullptr) {
        ExplosionActiva* eliminada = primeraExplosion;
        primeraExplosion = primeraExplosion->siguiente;
        eliminarExplosion(eliminada);
    }
    ultimaExplosion = nullptr;
}

void SistemaExplosion::configurar(Mapa* mapa, QGraphicsScene* escena,ColaBomba* bombas, int tamanoJugador,GestorEnemigos* enemigos, Jugador* jugador){
    this->mapa = mapa;
    this->escena = escena;
    this->bombas = bombas;
    this->tamanoJugador = tamanoJugador;
    this->enemigos = enemigos;
    this->jugador = jugador;
}

void SistemaExplosion::crearExplosion(int x, int y, int tamanoCelda, int alcance){
    if (mapa == nullptr || escena == nullptr || tamanoCelda <= 0 ||alcance <= 0 || tamanoJugador <= 0) {
        return;
    }

    x += tamanoJugador / 4;
    y += tamanoJugador / 4;
    int duracion = 350;
    const int centroX = x + tamanoJugador / 4;
    const int centroY = y + tamanoJugador / 4;
    const int filaBomba = centroY / tamanoCelda;
    const int columnaBomba = centroX / tamanoCelda;
    if (mapa->obtenerCelda(filaBomba, columnaBomba) == nullptr) {
        return;
    }

    ExplosionActiva* explosion = new ExplosionActiva;
    explosion->identificador = siguienteIdentificadorExplosion++;
    agregarCasilla(explosion, filaBomba, columnaBomba, 0, duracion);
    explosion->duracionMs = duracion;

    QGraphicsRectItem* centro = escena->addRect(0, 0, tamanoFlama, tamanoFlama, QPen(Qt::red), QBrush(Qt::yellow));
    centro->setPos(x, y);

    QTimer::singleShot(duracion, this, [centro]() { delete centro; });

    const int cambioFila[4] = {-1, 1, 0, 0};
    const int cambioColumna[4] = {0, 0, -1, 1};
    const int retrasoPorAnillo = 100;

    for (int direccion = 0; direccion < 4; ++direccion) {
        int alcanceDireccion = alcance;
        for (int distancia = 1; distancia <= alcanceDireccion; ++distancia) {
            const int filaFlama = filaBomba + cambioFila[direccion] * distancia;
            const int columnaFlama = columnaBomba + cambioColumna[direccion] * distancia;
            Celda* celda = mapa->obtenerCelda(filaFlama, columnaFlama);

            if (celda == nullptr) {
                break;
            }

            const int xFlama = x + cambioColumna[direccion] * tamanoCelda * distancia;
            const int yFlama = y + cambioFila[direccion] * tamanoCelda * distancia;
            bool continuar = true;
            bool mostrarFlama = true;

            if (celda->esObstaculo()) {
                celda->recibirExplosion();
                const bool destruida = celda->estaDestruida();
                const TipoItem item = celda->obtenerItem();
                if (!destruida) {
                    continuar = false;
                    mostrarFlama = false;
                } else {
                    if (item == TipoItem::Alcance) {
                        alcanceDireccion += tamanoItemAlcance;
                    } else if (item != TipoItem::Ninguno) {
                        celda->setItemDisponible();
                    }
                    if (item != TipoItem::Alcance) {
                        continuar = false;
                    }
                }
            } else {
                if (reaccionEnCadena(filaFlama, columnaFlama, retrasoPorAnillo * distancia)) {
                    continuar = false;
                }
            }

            if (mostrarFlama) {
                const int inicioMs = retrasoPorAnillo * (distancia - 1);
                const int finMs = inicioMs + duracion;
                agregarCasilla(explosion, filaFlama, columnaFlama,inicioMs, finMs);
                if (finMs > explosion->duracionMs) {
                    explosion->duracionMs = finMs;
                }
                QTimer::singleShot(inicioMs, this, [this, xFlama, yFlama, duracion]() {
                    QGraphicsRectItem* flama = escena->addRect(0, 0, tamanoFlama, tamanoFlama,QPen(Qt::red), QBrush(Qt::yellow));
                    flama->setPos(xFlama, yFlama);
                    QTimer::singleShot(duracion, this, [flama]() { delete flama; });
                });
            }

            if (!continuar) {
                break;
            }
        }
    }

    if (ultimaExplosion == nullptr) {
        primeraExplosion = explosion;
    } else {
        ultimaExplosion->siguiente = explosion;
    }
    ultimaExplosion = explosion;
}

void SistemaExplosion::actualizar(int milisegundos){
    if (milisegundos <= 0) {
        return;
    }

    ExplosionActiva* anterior = nullptr;
    ExplosionActiva* explosion = primeraExplosion;
    while (explosion != nullptr) {
        explosion->tiempoMs += milisegundos;

        NodoCasillaEnLlamas* casilla = explosion->primeraCasilla;
        while (casilla != nullptr) {
            if (explosion->tiempoMs < casilla->inicioMs ||explosion->tiempoMs >= casilla->finMs) {
                casilla = casilla->siguiente;
                continue;
            }

            if (!explosion->jugadorDanado &&jugadorEnCasilla(casilla->fila, casilla->columna)) {
                jugador->recibirDanioPorExplosion(1);
                explosion->jugadorDanado = true;
            }

            if (enemigos != nullptr) {
                enemigos->recibirExplosionEnCasilla(casilla->fila, casilla->columna,explosion->identificador);
            }
            casilla = casilla->siguiente;
        }

        if (explosion->tiempoMs >= explosion->duracionMs) {
            ExplosionActiva* eliminada = explosion;
            explosion = explosion->siguiente;
            if (anterior == nullptr) {
                primeraExplosion = explosion;
            } else {
                anterior->siguiente = explosion;
            }
            if (ultimaExplosion == eliminada) {
                ultimaExplosion = anterior;
            }
            if (enemigos != nullptr) {
                enemigos->finalizarExplosion(eliminada->identificador);
            }
            eliminarExplosion(eliminada);
        } else {
            anterior = explosion;
            explosion = explosion->siguiente;
        }
    }
}

void SistemaExplosion::agregarCasilla(ExplosionActiva* explosion, int fila, int columna, int inicioMs, int finMs)
{
    if (explosion == nullptr) {
        return;
    }
    NodoCasillaEnLlamas* nueva = new NodoCasillaEnLlamas(fila, columna, inicioMs, finMs, explosion->primeraCasilla);
    explosion->primeraCasilla = nueva;
}

void SistemaExplosion::eliminarExplosion(ExplosionActiva* explosion)
{
    if (explosion == nullptr) {
        return;
    }
    while (explosion->primeraCasilla != nullptr) {
        NodoCasillaEnLlamas* eliminada = explosion->primeraCasilla;
        explosion->primeraCasilla = eliminada->siguiente;
        delete eliminada;
    }
    delete explosion;
}

bool SistemaExplosion::jugadorEnCasilla(int fila, int columna) const
{
    if (jugador == nullptr || mapa == nullptr || tamanoJugador <= 0 ||
        mapa->obtenerTamanoCelda() <= 0) {
        return false;
    }

    QGraphicsRectItem* figura = jugador->obtenerFigura();
    if (figura == nullptr) {
        return false;
    }

    const int tamanoCelda = mapa->obtenerTamanoCelda();
    const int centroX = static_cast<int>(figura->pos().x()) + tamanoJugador / 2;
    const int centroY = static_cast<int>(figura->pos().y()) + tamanoJugador / 2;
    return centroY / tamanoCelda == fila && centroX / tamanoCelda == columna;
}

bool SistemaExplosion::reaccionEnCadena(  int filaFlama, int columnaFlama, int retraso)
{
    if (mapa == nullptr || bombas == nullptr ||mapa->obtenerCelda(filaFlama, columnaFlama) == nullptr) {
        return false;
    }

    int xBomba = 0;
    int yBomba = 0;
    int alcanceBomba = 0;
    if (!bombas->localizarBomba(filaFlama, columnaFlama, xBomba, yBomba,alcanceBomba, mapa->obtenerTamanoCelda(),tamanoJugador)) {
        return false;
    }

    QTimer::singleShot(retraso, this,[this, xBomba, yBomba, alcanceBomba,filaFlama, columnaFlama]() {
        const int tamanoCelda = mapa->obtenerTamanoCelda();
        if (bombas->eliminarBombaEn(filaFlama, columnaFlama, tamanoCelda, tamanoJugador)) {
            if (jugador != nullptr) {
                jugador->bombaExplotada();
            }
            crearExplosion(xBomba, yBomba, tamanoCelda, alcanceBomba);
        }
    });
    return true;
}

