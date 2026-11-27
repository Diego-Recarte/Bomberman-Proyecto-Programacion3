#include "listausuarios.h"

ListaUsuarios::ListaUsuarios() {}


ListaUsuarios::~ListaUsuarios(){
    vaciar();
}

bool ListaUsuarios::estaVacia() const
{
    return primero == nullptr;
}

int ListaUsuarios::obtenerCantidad() const
{
    return cantidad;
}

bool ListaUsuarios::eliminar(std::string clave){

    if (primero ==nullptr){
        return false;
    }
    if (primero ->usuario.obtenerNombre()==clave){

        NodoUsuario* aux = primero;
        primero = primero ->siguiente;
        delete aux;
        aux=nullptr;
        cantidad --;
        return true;

    }
    NodoUsuario* anterior =primero;
    NodoUsuario* actual =primero->siguiente;

    while (actual !=nullptr && actual->usuario.obtenerNombre() != clave){
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr){
        return false;
    }else{
        anterior ->siguiente= actual ->siguiente;
        delete actual;
        cantidad--;
        return true;


    }

}

void ListaUsuarios::vaciar(){
    while (!estaVacia()) {
        if (estaVacia()) {
            return;
        }

        NodoUsuario* siguiente = primero->siguiente;


        delete primero;
        --cantidad;
        primero =siguiente;
    }
}

bool ListaUsuarios::agregar(std::string nombre, std::string contrasena, int niveles, int trofeos){

    NodoUsuario* nueva = new NodoUsuario(nombre, contrasena, niveles, trofeos);
    if (estaVacia()) {
        primero = nueva;

    } else {

        NodoUsuario* posicion= primero;

        while (posicion->siguiente!=nullptr){
            posicion=posicion->siguiente;
        }
        posicion->siguiente=nueva;

    }
    ++cantidad;
    return true;
}


NodoUsuario* ListaUsuarios::obtenerPorIndice(int i){
    NodoUsuario * actual= primero;
    for (int j=0; j<i; j++){
        actual = actual->siguiente;
        if (actual==nullptr){
            return nullptr;
        }
    }

    return actual;
}


void ListaUsuarios::ordenarPorPuntaje(){
    for (int i=0; i<cantidad-1; i++){
        int maximo=i;

        for (int j=1+i; j<cantidad; j++){

            if (obtenerPorIndice(j)->usuario.obtenerPuntaje()>obtenerPorIndice(maximo)->usuario.obtenerPuntaje()){
                maximo=j;
            }

        }

        if (i != maximo){

            Usuario temp = obtenerPorIndice(i)->usuario;
            obtenerPorIndice(i)->usuario = obtenerPorIndice(maximo)->usuario;
            obtenerPorIndice(maximo)->usuario= temp;
        }
    }
}

NodoUsuario* ListaUsuarios::buscarPorNombre(std::string nombre){
    NodoUsuario* actual = primero;

    while (actual != nullptr) {
        if (actual->usuario.obtenerNombre() == nombre) {
            return actual;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}

NodoUsuario* ListaUsuarios::iniciarSesion( std::string nombre, std::string contrasena){
    NodoUsuario* encontrado = buscarPorNombre(nombre);

    if (encontrado == nullptr) {
        return nullptr;
    }

    if (encontrado->usuario.obtenerContrasena() != contrasena) {
        return nullptr;
    }

    return encontrado;
}