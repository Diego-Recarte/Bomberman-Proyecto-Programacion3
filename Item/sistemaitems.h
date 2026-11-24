#ifndef SISTEMAITEMS_H
#define SISTEMAITEMS_H

class Jugador;
class Mapa;

class SistemaItems
{
public:
    void configurar(Mapa* mapa, Jugador* jugador, int tamanoJugador);
    void actualizar();

private:
    Mapa* mapa = nullptr;
    Jugador* jugador = nullptr;
    int tamanoJugador = 0;
};

#endif // SISTEMAITEMS_H
