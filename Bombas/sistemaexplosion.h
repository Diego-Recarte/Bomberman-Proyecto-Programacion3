#ifndef SISTEMAEXPLOSION_H
#define SISTEMAEXPLOSION_H

#include <QObject>

class ColaBomba;
class Jugador;
class Mapa;
class QGraphicsScene;
class GestorEnemigos;

class SistemaExplosion : public QObject {
public:
    void configurar(Mapa* mapa, QGraphicsScene* escena, ColaBomba* bombas,
                    int tamanoJugador, GestorEnemigos* enemigos, Jugador* jugador);
    void crearExplosion(int x, int y, int tamanoCelda, int alcance);
    bool reaccionEnCadena(int filaFlama, int columnaFlama, int retraso);

private:
    Mapa* mapa = nullptr;
    QGraphicsScene* escena = nullptr;
    ColaBomba* bombas = nullptr;
    GestorEnemigos* enemigos = nullptr;
    Jugador* jugador = nullptr;
    int tamanoJugador = 0;
    int tamanoFlama = 20;
    int tamanoItemAlcance = 2;
};

#endif // SISTEMAEXPLOSION_H
