#ifndef COLABOMBA_H
#define COLABOMBA_H

#include <QGraphicsScene>
#include "nodobomba.h"

class ColaBomba {
public:
    ColaBomba();
    ~ColaBomba();

    bool estaVacia() const;
    int obtenerCantidad() const;
    bool obtenerPosicionPrimera(int& x, int& y, int& alcanceExterno) const;
    bool primeraBombaVencida() const;
    void eliminar();
    void vaciar();

    bool agregar(int fila, int columna, int tiempo, int alcance,QGraphicsScene* escena, int tamanoCelda, int tamanoJugador);
    bool existeBombaEn(int fila, int columna, int tamanoCelda, int tamanoJugador) const;
    bool localizarBomba(int fila, int columna, int& x, int& y, int& alcance, int tamanoCelda, int tamanoJugador);
    bool eliminarBombaEn(int fila, int columna, int tamanoCelda, int tamanoJugador);
    bool bloqueaMovimiento(double x,double y,double ancho,double alto,double dx,double dy, int tamanoJugador) const;

private:
    NodoBomba* primero = nullptr;
    NodoBomba* ultimo = nullptr;
    int cantidad = 0;
};

#endif // COLABOMBA_H