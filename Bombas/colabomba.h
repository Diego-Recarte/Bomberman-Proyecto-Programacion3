#ifndef COLABOMBA_H
#define COLABOMBA_H
#include <QGraphicsScene>
#include "nodobomba.h"

class ColaBomba{
public:
    ColaBomba();
    ~ColaBomba();

    bool estaVacia() const;//funcion const
    int obtenerCantidad() const;

    bool obtenerPosicionPrimera(int& x, int& y,  int& alcanceExterno) const;

    bool primeraBombaVencida() const;
    void eliminar();
    void vaciar();
    bool agregar(int fila, int columna, int tiempo, QGraphicsScene* escena,
                 int tamanoCelda, int tamanoJugador);

    bool existeBombaEn(int fila, int columna, int tamanoCelda, int tamanoJugador) const;

    bool localizarBomba(int fila, int columna, int& x, int& y, int& alcance,int tamanoCelda, int tamanoJugador);
    bool eliminarBombaEn(int fila, int columna, int tamanoCelda,int tamanoJugador);

private:
    NodoBomba* primero = nullptr;
    NodoBomba* ultimo = nullptr;
    int cantidad = 0;
    int maximoBombas=3;
    int alcance=3;
};

#endif // COLABOMBA_H
