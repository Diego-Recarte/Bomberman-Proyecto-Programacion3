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



bool ColaBomba::localizarBomba(int fila, int columna, int& x, int& y, int& alcance,int tamanoCelda,int tamanoJugador){
    NodoBomba* actual =primero;

    while(actual!=nullptr){
        int centroX = actual->bomba.obtenerX() + tamanoJugador / 4;
        int centroY = actual->bomba.obtenerY() + tamanoJugador / 4;

        int filaBomba = centroY / tamanoCelda;
        int columnaBomba = centroX / tamanoCelda;

        if (filaBomba==fila  && columnaBomba==columna){
            x=actual->bomba.obtenerX();
            y=actual->bomba.obtenerY();
            alcance=actual->bomba.obtenerAlcance();
            return true;
        }

        actual =actual->siguiente;

    }
    return false;
}
bool ColaBomba::eliminarBombaEn(int fila, int columna,int tamanoCelda, int tamanoJugador){
    NodoBomba* anterior = nullptr;
    NodoBomba* actual = primero;

    while (actual != nullptr){
        int centroX = actual->bomba.obtenerX() + tamanoJugador / 4;
        int centroY = actual->bomba.obtenerY() + tamanoJugador / 4;

        int filaBomba = centroY / tamanoCelda;
        int columnaBomba = centroX / tamanoCelda;

        if (filaBomba == fila && columnaBomba == columna){
            if (anterior == nullptr){
                primero = actual->siguiente;
            }
            else{
                anterior->siguiente = actual->siguiente;
            }

            if (actual == ultimo){
                ultimo = anterior;
            }

            delete actual;
            cantidad--;

            return true;
        }

        anterior = actual;
        actual = actual->siguiente;
    }

    return false;
}


