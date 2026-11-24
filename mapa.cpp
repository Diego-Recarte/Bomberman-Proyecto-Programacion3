#include "mapa.h"


Mapa::Mapa(int filas, int columnas, int tamanoCelda)
{
    this->filas = filas;
    this->columnas = columnas;
    this->tamanoCelda = tamanoCelda;
}

Mapa::~Mapa()//destructor
{
    if (mapa != nullptr)
    {
        for (int fila = 0; fila < filas; fila++)
        {
            delete[] mapa[fila];
        }

        delete[] mapa;
    }
}

void Mapa::crearMapa()
{

    if (mapa != nullptr)
    {
        return;
    }

    mapa = new Celda*[filas];

    for (int fila = 0; fila < filas; fila++)
    {
        mapa[fila] = new Celda[columnas]{};

        for (int columna = 0; columna < columnas; columna++)
        {
            if (fila == 0 || fila == filas - 1 ||
                columna == 0 || columna == columnas - 1)
            {
                mapa[fila][columna] =  Celda(Tipo::pared);
            }
        }
    }


    mapa[6][7]= Celda(Tipo::caja);
    mapa[6][7].asignarItem(TipoItem::Portal);
    mapa[7][7]= Celda(Tipo::pared);





}

bool Mapa::esObstaculo(int fila, int columna) const
{
    if (fila < 0  || fila >= filas ||
        columna < 0 || columna >= columnas)
    {
        return true;
    }

    return mapa[fila][columna].esObstaculo();
}

Celda* Mapa::obtenerCelda(int fila, int columna){
    return &mapa[fila][columna];
}

int Mapa::obtenerFilas() const
{
    return filas;
}

int Mapa::obtenerColumnas() const
{
    return columnas;
}

int Mapa::obtenerTamanoCelda() const
{
    return tamanoCelda;
}






