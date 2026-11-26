#ifndef LISTAUSUARIOS_H
#define LISTAUSUARIOS_H

#include "NodoUsuario.h"




class ListaUsuarios{
public:
    ListaUsuarios();
    ~ListaUsuarios();
    bool estaVacia() const;
    int obtenerCantidad() const;
    bool eliminar(std::string clave);
    void vaciar();
    bool agregar(std::string nombre, std::string contrasena, int niveles, int trofeos);
    bool localiza();
    NodoUsuario* iniciarSesion( std::string nombre, std::string contrasena);

    NodoUsuario* buscarPorNombre(std::string nombre);
    NodoUsuario* obtenerPorIndice(int i);
      void ordenarPorPuntaje();
private:


    NodoUsuario* primero = nullptr;
     int cantidad = 0;
};







#endif // LISTAUSUARIOS_H
