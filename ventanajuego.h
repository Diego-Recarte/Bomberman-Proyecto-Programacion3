#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>

class ControladorJuego;
class QGraphicsTextItem;

class VentanaJuego : public QGraphicsView
{
public:
    VentanaJuego();
    ~VentanaJuego() override;

protected:
    void keyPressEvent(QKeyEvent* evento) override;
    void keyReleaseEvent(QKeyEvent* evento) override;

private:
    QGraphicsScene* escena = nullptr;
    ControladorJuego* controlador = nullptr;
    QTimer* temporizadorMovimiento = nullptr;

    enum class EstadoPartida { EnCurso, Derrota, Victoria };
    EstadoPartida estadoPartida = EstadoPartida::EnCurso;

    QGraphicsRectItem* barraVidaFondo = nullptr;
    QGraphicsRectItem* barraVida = nullptr;
    QGraphicsTextItem* textoVida = nullptr;
    QGraphicsTextItem* textoResultado = nullptr;

    void crearInterfaz();
    void actualizarPartida();
    void actualizarInterfazVida();
    void finalizarPartida(bool victoria);
};

#endif // VENTANAJUEGO_H
