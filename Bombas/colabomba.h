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
    void agregar(int fila, int columna, int tiempo,int alcance,  QGraphicsScene* escena);

    bool existeBombaEn(int fila, int columna) const;

    bool localizarBomba(int fila, int columna, int& x, int& y, int& alcance,int tamanoCelda, int tamanoJugador);
    bool eliminarBombaEn(int fila, int columna, int tamanoCelda,int tamanoJugador);

private:
    NodoBomba* primero = nullptr;
    NodoBomba* ultimo = nullptr;
    int cantidad = 0;

};

#endif // COLABOMBA_H
