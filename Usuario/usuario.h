#ifndef USUARIO_H
#define USUARIO_H

#include <string>



class Usuario{
private:
    std::string nombre;
    std::string PIN;
    int nivel;
    int trofeos;



public:
    Usuario(std::string nombreN,std::string PINN,int nivelN,int trofeosN);
    std::string obtenerNombre();
    std::string obtenerContrasena();
    int obtenerNivel();
    int obtenerTrofeos();
    int obtenerPuntaje();

};

#endif // USUARIO_H
