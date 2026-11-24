#ifndef PILAITEM_H
#define PILAITEM_H


#include "tipoitem.h"

struct NodoItem{
    TipoItem item;
    NodoItem* siguiente;

    NodoItem(TipoItem itemInicial) {
        item = itemInicial;
        siguiente = nullptr;
    }
};

class PilaItem
{
private:
    NodoItem* cima;
    int cantidad;

public:
    PilaItem();
    ~PilaItem();

    bool estaVacia() const;
    int obtenerCantidad() const;

    void apilar(TipoItem item);
    TipoItem desapilar();
    void vaciar();
};

#endif