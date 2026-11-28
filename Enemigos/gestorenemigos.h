#ifndef GESTORENEMIGOS_H
#define GESTORENEMIGOS_H


class ColaBomba;
class Enemigo;
class EnemigoPersecutor;
class fantasma;
class Jugador;
class Mapa;
class QGraphicsScene;

class GestorEnemigos {
public:
    ~GestorEnemigos();

    void crearEnemigos(Mapa* mapa, QGraphicsScene* escena, int filaJugador, int columnaJugador, int cantidad, int tamJugador);
    void crearEnemigos(Mapa* mapa, QGraphicsScene* escena,int filaJugador, int columnaJugador, int aleatorio,int inteligente,
                       int tamJugador, Jugador* jugador);
    void crearEnemigos(Mapa* mapa, QGraphicsScene* escena,int filaJugador, int columnaJugador, int aleatorio,int inteligente,
                       int fantasma, int tamJugador, Jugador* jugador);
    void actualizar(int milisegundos, Jugador* jugador, const ColaBomba* bombas);
    void recibirExplosionEnCasilla(int fila, int columna, int identificadorExplosion);
    void finalizarExplosion(int identificadorExplosion);
    int obtenerCantidad() const;

private:
    Enemigo** enemigos = nullptr;
    int cantidadEnemigos = 0;
    int capacidad = 0;

    struct NodoImpactoExplosion {
        const Enemigo* enemigo;
        int identificadorExplosion;
        NodoImpactoExplosion* siguiente = nullptr;
    };
    NodoImpactoExplosion* primerosImpactos = nullptr;

    void eliminarEnemigo(int indice);
    bool yaRecibioExplosion(const Enemigo* enemigo, int identificadorExplosion) const;
    void registrarImpacto(const Enemigo* enemigo, int identificadorExplosion);
    void eliminarImpactosDelEnemigo(const Enemigo* enemigo);
};

#endif // GESTORENEMIGOS_H
