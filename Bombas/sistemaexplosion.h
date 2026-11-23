#ifndef SISTEMAEXPLOSION_H
#define SISTEMAEXPLOSION_H

#include <QObject>

class ColaBomba;
class Mapa;
class QGraphicsScene;

class SistemaExplosion : public QObject {
public:
    void configurar(Mapa* mapa, QGraphicsScene* escena, ColaBomba* bombas,
                    int tamanoJugador);

    void crearExplosion(int x, int y, int tamanoCelda, int alcance);
    bool reaccionEnCadena(int filaFlama, int columnaFlama, int retraso);

private:
    Mapa* mapa = nullptr;
    QGraphicsScene* escena = nullptr;
    ColaBomba* bombas = nullptr;
    int tamanoJugador = 0;
    int tamanoFlama = 20;
};

#endif // SISTEMAEXPLOSION_H
