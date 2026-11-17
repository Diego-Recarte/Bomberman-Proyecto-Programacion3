#ifndef MAPA_H
#define MAPA_H

class Mapa{
public:


Mapa(int filas, int columnas, int tamanoCelda);
~Mapa();

void crearMapa();
bool esObstaculo(int fila, int columna) const;

int obtenerFilas() const;
int obtenerColumnas() const;
int obtenerTamanoCelda() const;
int** obtenerMapa() const;

private:
int filas;
int columnas;
int tamanoCelda;

int** mapa = nullptr;
};

#endif // MAPA_H
