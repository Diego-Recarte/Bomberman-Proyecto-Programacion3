#ifndef PANELVIDA_H
#define PANELVIDA_H

#include <QPixmap>

class QGraphicsScene;
class QGraphicsPixmapItem;

class PanelVida{
public:
    PanelVida(QGraphicsScene* escena, int x, int y);
    ~PanelVida();

    void actualizar(int vidaActual, int vidaMaxima);

    PanelVida(const PanelVida&) = delete; //evitar duplicaciones
    PanelVida& operator=(const PanelVida&) = delete;

private:
    struct NodoCorazon{
        QGraphicsPixmapItem* imagen = nullptr;
        NodoCorazon* siguiente = nullptr;
    };

    QGraphicsScene* escena = nullptr;

    NodoCorazon* primero = nullptr;
    int cantidadCorazones = 0;

    QPixmap imagenCorazon;
    QPixmap imagenCorazonRoto;

    int x = 0;
    int y = 0;

    void agregarCorazon();
};

#endif // PANELVIDA_H