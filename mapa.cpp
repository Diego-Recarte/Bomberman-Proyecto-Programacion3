#include "mapa.h"


Mapa::Mapa(int filas, int columnas, int tamanoCelda)
{
    this->filas = filas;
    this->columnas = columnas;
    this->tamanoCelda = tamanoCelda;
}

Mapa::~Mapa()
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
    mapa = new int*[filas];

    for (int fila = 0; fila < filas; fila++)
    {
        mapa[fila] = new int[columnas]{};

        for (int columna = 0; columna < columnas; columna++)
        {
            if (fila == 0 || fila == filas - 1 ||
                columna == 0 || columna == columnas - 1)
            {
                mapa[fila][columna] = 1;
            }
        }
    }
}

bool Mapa::esObstaculo(int fila, int columna) const
{
    if (fila < 0 || fila >= filas ||
        columna < 0 || columna >= columnas)
    {
        return true;
    }

    return mapa[fila][columna] != 0;
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


int** Mapa::obtenerMapa() const
{
    return mapa;
}



