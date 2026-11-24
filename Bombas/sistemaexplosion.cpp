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

void SistemaExplosion::configurar(Mapa* mapa, QGraphicsScene* escena,
                                  ColaBomba* bombas, int tamanoJugador,
                                  GestorEnemigos* enemigos, Jugador* jugador)
{
    this->mapa = mapa;
    this->escena = escena;
    this->bombas = bombas;
    this->tamanoJugador = tamanoJugador;
    this->enemigos = enemigos;
    this->jugador = jugador;
}

void SistemaExplosion::crearExplosion(int x, int y, int tamanoCelda, int alcance)
{
    if (mapa == nullptr || escena == nullptr || tamanoCelda <= 0 ||
        alcance <= 0 || tamanoJugador <= 0) {
        return;
    }

    x += tamanoJugador / 4;
    y += tamanoJugador / 4;
    const int centroX = x + tamanoJugador / 4;
    const int centroY = y + tamanoJugador / 4;
    const int filaBomba = centroY / tamanoCelda;
    const int columnaBomba = centroX / tamanoCelda;
    if (mapa->obtenerCelda(filaBomba, columnaBomba) == nullptr) {
        return;
    }

    QGraphicsRectItem* centro = escena->addRect(
        0, 0, tamanoFlama, tamanoFlama, QPen(Qt::red), QBrush(Qt::yellow));
    centro->setPos(x, y);
    if (enemigos != nullptr) {
        enemigos->recibirExplosionEnCasilla(filaBomba, columnaBomba);
    }
    QTimer::singleShot(500, this, [centro]() { delete centro; });

    const int cambioFila[4] = {-1, 1, 0, 0};
    const int cambioColumna[4] = {0, 0, -1, 1};
    const int retrasoPorAnillo = 100;

    // Cada direccion conserva su propio alcance porque un item puede extenderlo.
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
                if (enemigos != nullptr) {
                    enemigos->recibirExplosionEnCasilla(filaFlama, columnaFlama);
                }
                if (reaccionEnCadena(filaFlama, columnaFlama,
                                     retrasoPorAnillo * distancia)) {
                    continuar = false;
                }
            }

            if (mostrarFlama) {
                QTimer::singleShot(retrasoPorAnillo * (distancia - 1), this,
                                   [this, xFlama, yFlama]() {
                    QGraphicsRectItem* flama = escena->addRect(
                        0, 0, tamanoFlama, tamanoFlama,
                        QPen(Qt::red), QBrush(Qt::yellow));
                    flama->setPos(xFlama, yFlama);
                    QTimer::singleShot(500, this, [flama]() { delete flama; });
                });
            }

            if (!continuar) {
                break;
            }
        }
    }
}

bool SistemaExplosion::reaccionEnCadena(int filaFlama, int columnaFlama, int retraso)
{
    if (mapa == nullptr || bombas == nullptr ||
        mapa->obtenerCelda(filaFlama, columnaFlama) == nullptr) {
        return false;
    }

    int xBomba = 0;
    int yBomba = 0;
    int alcanceBomba = 0;
    if (!bombas->localizarBomba(filaFlama, columnaFlama, xBomba, yBomba,
                                alcanceBomba, mapa->obtenerTamanoCelda(),
                                tamanoJugador)) {
        return false;
    }

    QTimer::singleShot(retraso, this,
                       [this, xBomba, yBomba, alcanceBomba,
                        filaFlama, columnaFlama]() {
        const int tamanoCelda = mapa->obtenerTamanoCelda();
        if (bombas->eliminarBombaEn(filaFlama, columnaFlama,
                                    tamanoCelda, tamanoJugador)) {
            if (jugador != nullptr) {
                jugador->bombaExplotada();
            }
            crearExplosion(xBomba, yBomba, tamanoCelda, alcanceBomba);
        }
    });
    return true;
}

