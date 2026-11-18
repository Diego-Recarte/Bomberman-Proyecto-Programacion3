#ifndef NODOBOMBA_H
#define NODOBOMBA_H


#include "bomba.h"
class NodoBomba
{
public:
    NodoBomba(int fila, int columna, int tiempo,int alcance);

    Bomba bomba;
    NodoBomba* siguiente = nullptr;



};

#endif // NODOBOMBA_H
