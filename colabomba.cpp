#include "colabomba.h"
#include<iostream>

ColaBomba::ColaBomba() {}


ColaBomba::~ColaBomba(){
    vaciar();
}


bool ColaBomba::estaVacia() const{
    return primero == nullptr;
}

int ColaBomba::obtenerCantidad() const{
    return cantidad;
}


void ColaBomba::eliminar(){
    if (estaVacia()){
        return;
    }

    NodoBomba* eliminado = primero;

    primero = primero->siguiente;

    if (primero == nullptr){
        ultimo = nullptr;
    }

    delete eliminado;
    cantidad--;
}

void ColaBomba::vaciar(){
    while (!estaVacia()){
        eliminar();
    }
}


void ColaBomba::agregar(int fila, int columna, int tiempo,  QGraphicsScene* escena){
    if (cantidad<maximoBombas){

        NodoBomba* nueva= new NodoBomba(fila, columna, tiempo, alcance);
        nueva->bomba.dibujar(escena, 40);
        if ((estaVacia())){
            primero=nueva;
            ultimo=nueva;
        }else{
            ultimo->siguiente=nueva;
            ultimo=nueva;
        }


        cantidad++;
    }

}
bool ColaBomba::primeraBombaVencida() const{
    if (estaVacia())
    {
        return false;
    }

    return primero->bomba.tiempoCumplido();
}

bool ColaBomba::obtenerPosicionPrimera(int& x, int& y, int & alcanceExterno) const
{
    if (estaVacia())
    {
        return false;
    }

    alcanceExterno=primero->bomba.obtenerAlcance();



    x = primero->bomba.obtenerX();
    y = primero->bomba.obtenerY();

    return true;
}

