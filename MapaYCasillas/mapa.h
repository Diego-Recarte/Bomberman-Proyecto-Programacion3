#ifndef MAPA_H
#define MAPA_H

#include "celda.h"
class Mapa{
public:


Mapa(int filas, int columnas, int tamanoCelda);
~Mapa();

void crearMapa();
void dibujar(QGraphicsScene* escena, int tamanoJugador);
bool esObstaculo(int fila, int columna) const;
Celda* obtenerCelda(int fila, int columna);

int obtenerFilas() const;
int obtenerColumnas() const;
int obtenerTamanoCelda() const;


private:
int filas;
int columnas;
int tamanoCelda;

Celda** mapa = nullptr;
};

#endif // MAPA_H
