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
    if (mapa != nullptr || filas <= 0 || columnas <= 0)
    {
        return;
    }

    srand(time(NULL));

    mapa = new Celda*[filas]{};

    for (int fila = 0; fila < filas; fila++){
        mapa[fila] = new Celda[columnas]{};

        for (int columna = 0; columna < columnas; columna++){
            bool contorno = fila == 0 || fila == filas - 1 || columna == 0 || columna == columnas - 1;
            bool pilar = fila % 2 == 0 and columna % 2 == 0;
            bool obstaculo = (fila % 2 == 1 || columna % 2 == 1) and !(fila <= 2 and columna <= 2);
            bool resultado = (rand() % 100 < 30);

            if (contorno || pilar)
            {
                mapa[fila][columna] = Celda(Tipo::pared);
            }
            else if (obstaculo and resultado)
            {
                mapa[fila][columna] = Celda(Tipo::caja);

            }
            if(mapa[fila][columna].obtenerTipo() == caja){
                int num = rand() % 10 + 1;
                switch(num){
                case 1:
                    mapa[fila][columna].asignarItem(TipoItem::Alcance);
                    break;
                case 2:
                    mapa[fila][columna].asignarItem(TipoItem::masVida);
                    break;
                case 3:
                    mapa[fila][columna].asignarItem(TipoItem::Velocidad);
                    break;
                case 4:
                    mapa[fila][columna].asignarItem(TipoItem::BombaExtra);
                    break;
                case 5:
                    mapa[fila][columna].asignarItem(TipoItem::cura);
                    break;
                default:
                    mapa[fila][columna].asignarItem(TipoItem::Ninguno);
                    break;

                }

            }



        }
    }
}

bool Mapa::esObstaculo(int fila, int columna) const
{
    if (mapa == nullptr || fila < 0 || fila >= filas ||
        columna < 0 || columna >= columnas){
        return true;
    }

    if (mapa[fila] == nullptr) {
        return true;
    }

    return mapa[fila][columna].esObstaculo();
}
bool Mapa::esPared(int fila, int columna) const{
    if (mapa == nullptr || fila < 0 || fila >= filas ||
        columna < 0 || columna >= columnas){
        return true;
    }

    if (mapa[fila] == nullptr) {
        return true;
    }
    return mapa[fila][columna].obtenerTipo() == Tipo::pared;
}

Celda* Mapa::obtenerCelda(int fila, int columna)
{
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

void Mapa::dibujar(QGraphicsScene* escena, int tamanoJugador)
{
    if (mapa == nullptr || escena == nullptr || tamanoCelda <= 0 || tamanoJugador <= 0) {
        return;
    }

    for (int fila = 0; fila < filas; ++fila) {
        for (int columna = 0; columna < columnas; ++columna) {
            mapa[fila][columna].dibujar(escena, columna * tamanoCelda,fila * tamanoCelda, tamanoCelda, tamanoJugador);
        }
    }
}
