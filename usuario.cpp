#include "usuario.h"

Usuario::Usuario(std::string nombreN,std::string PINN,int nivelN,int trofeosN): nombre(nombreN), PIN(PINN), nivel(nivelN), trofeos(trofeosN){

}



std::string Usuario::obtenerNombre(){
    return nombre;
}
std::string Usuario::obtenerContrasena(){
    return PIN;
}
int Usuario::obtenerNivel(){
    return nivel;
}
int Usuario::obtenerTrofeos(){
    return trofeos;
}
int Usuario::obtenerPuntaje(){
    return trofeos * nivel;
}

