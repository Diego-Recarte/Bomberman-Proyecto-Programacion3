#include "pilaitem.h"

PilaItem::PilaItem(){
    cima = nullptr;
    cantidad = 0;
}

PilaItem::~PilaItem(){
    vaciar();
}

bool PilaItem::estaVacia() const{
    return cima == nullptr;
}

int PilaItem::obtenerCantidad() const{
    return cantidad;
}

void PilaItem::apilar(TipoItem item){
    NodoItem* nuevo = new NodoItem(item);
    nuevo->siguiente = cima;
    cima = nuevo;
    cantidad++;
}

TipoItem PilaItem::desapilar(){
    if (estaVacia()){
        return TipoItem::Ninguno;
    }

    NodoItem* eliminado = cima;
    TipoItem item = eliminado->item;

    cima = cima->siguiente;
    delete eliminado;
    cantidad--;

    return item;
}

void PilaItem::vaciar(){
    while (!estaVacia()){
        desapilar();
    }
}