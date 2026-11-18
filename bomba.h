#ifndef BOMBA_H
#define BOMBA_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QElapsedTimer>

class Bomba{
public:
    Bomba(int filaInicial, int columnaInicial, int duracionInicialMs, int alcanceInicial);
    void dibujar(QGraphicsScene* escena, int tamanoCelda);
    ~Bomba();

    int obtenerX() const;
    int obtenerY() const;




    Bomba(const Bomba&) = delete;
    Bomba& operator=(const Bomba&) = delete;
    bool tiempoCumplido() const;

    void cambiarAlcance( int i);
    int obtenerAlcance() const;

private:
    int fila;
    int columna;
    int tiempo;
    int alcance;
    QElapsedTimer reloj;
    QGraphicsRectItem* forma = nullptr;
};

#endif // BOMBA_H
