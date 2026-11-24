#ifndef GESTORENEMIGOS_H
#define GESTORENEMIGOS_H

class ColaBomba;
class Enemigo;
class Jugador;
class Mapa;
class QGraphicsScene;

class GestorEnemigos {
public:
    ~GestorEnemigos();

    void crearEnemigos(Mapa* mapa, QGraphicsScene* escena, int filaJugador, int columnaJugador, int cantidad);
    void actualizar(int milisegundos, Jugador* jugador, const ColaBomba* bombas);
    void recibirExplosionEnCasilla(int fila, int columna);
    int obtenerCantidad() const;

private:
    Enemigo** enemigos = nullptr;
    int cantidadEnemigos = 0;
    int capacidad = 0;

    void eliminarEnemigo(int indice);
};

#endif // GESTORENEMIGOS_H
