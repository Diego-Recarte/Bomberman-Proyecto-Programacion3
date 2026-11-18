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
    void agregar(int fila, int columna, int tiempo,  QGraphicsScene* escena);

private:
    NodoBomba* primero = nullptr;
    NodoBomba* ultimo = nullptr;
    int cantidad = 0;
    int maximoBombas=3;
    int alcance=3;
};

#endif // COLABOMBA_H
