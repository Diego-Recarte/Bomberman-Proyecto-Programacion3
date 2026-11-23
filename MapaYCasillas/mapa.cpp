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

    if (mapa != nullptr || filas <= 0 || columnas <= 0)
    {
        return;
    }
    srand(time(NULL));



    mapa = new Celda*[filas]{};

    for (int fila = 0; fila < filas; fila++)
    {
        mapa[fila] = new Celda[columnas]{};

        for (int columna = 0; columna < columnas; columna++)
        {
            bool contorno = fila == 0 || fila == filas - 1 || columna == 0 || columna == columnas - 1;
            //Se dibujan las casillas indestructibles que no son parte del contorno del mapa
            bool pilar = fila % 2 == 0 and columna % 2 == 0;
            //Se posicionan las cajas en puntos en los que no interfieran con otras casillas o el spawn del jugador
            bool obstaculo = (fila % 2 == 1 || columna % 2 == 1) and !(fila <= 2 and columna <= 2) ;
            bool resultado = (rand() % 100 < 30);//Un 30% de proabilidad de generar el obstaculo
            if (contorno || pilar)
            {
                mapa[fila][columna] =  Celda(Tipo::pared);
            }else if(obstaculo and resultado){
                mapa[fila][columna] =  Celda(Tipo::caja);
            }

        }
    }
}

bool Mapa::esObstaculo(int fila, int columna) const
{
    if (mapa == nullptr || fila < 0  || fila >= filas ||
        columna < 0 || columna >= columnas)
    {
        return true;
    }

    if (mapa[fila] == nullptr) {
        return true;
    }

    return mapa[fila][columna].esObstaculo();
}

Celda* Mapa::obtenerCelda(int fila, int columna){
    if (mapa == nullptr || fila < 0 || fila >= filas ||
        columna < 0 || columna >= columnas) {
        return nullptr;
    }

    if (mapa[fila] == nullptr) {
        return nullptr;
    }

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






