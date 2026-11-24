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
    ~SistemaExplosion() override;

    void configurar(Mapa* mapa, QGraphicsScene* escena, ColaBomba* bombas,
                    int tamanoJugador, GestorEnemigos* enemigos, Jugador* jugador);
    void crearExplosion(int x, int y, int tamanoCelda, int alcance);
    void actualizar(int milisegundos);
    bool reaccionEnCadena(int filaFlama, int columnaFlama, int retraso);

private:
    struct NodoCasillaEnLlamas {
        NodoCasillaEnLlamas(int fila, int columna, int inicioMs, int finMs,
                            NodoCasillaEnLlamas* siguiente);

        int fila;
        int columna;
        int inicioMs;
        int finMs;
        NodoCasillaEnLlamas* siguiente = nullptr;
    };

    struct ExplosionActiva {
        int identificador = 0;
        int tiempoMs = 0;
        int duracionMs = 0;
        bool jugadorDanado = false;
        NodoCasillaEnLlamas* primeraCasilla = nullptr;
        ExplosionActiva* siguiente = nullptr;
    };

    Mapa* mapa = nullptr;
    QGraphicsScene* escena = nullptr;
    ColaBomba* bombas = nullptr;
    GestorEnemigos* enemigos = nullptr;
    Jugador* jugador = nullptr;
    int tamanoJugador = 0;
    int tamanoFlama = 20;
    int tamanoItemAlcance = 2;
    int siguienteIdentificadorExplosion = 1;
    ExplosionActiva* primeraExplosion = nullptr;
    ExplosionActiva* ultimaExplosion = nullptr;

    void agregarCasilla(ExplosionActiva* explosion, int fila, int columna,
                        int inicioMs, int finMs);
    void eliminarExplosion(ExplosionActiva* explosion);
    bool jugadorEnCasilla(int fila, int columna) const;
};

#endif // SISTEMAEXPLOSION_H
