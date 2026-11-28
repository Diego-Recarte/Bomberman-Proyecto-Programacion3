#ifndef NODOUSUARIO_H
#define NODOUSUARIO_H


#include "usuario.h"
class NodoUsuario
{
public:

    NodoUsuario(std::string nombreN,std::string PINN,int nivelN,int trofeosN);

    Usuario usuario;
    NodoUsuario * siguiente= nullptr;




};





#endif // NODOUSUARIO_H
