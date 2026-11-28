#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>

class ControladorJuego;
class QGraphicsTextItem;
class QGraphicsPixmapItem;

class PanelVida;

class VentanaJuego : public QGraphicsView
{
public:
    VentanaJuego();
    ~VentanaJuego() override;

protected:
    void keyPressEvent(QKeyEvent* evento) override;
    void keyReleaseEvent(QKeyEvent* evento) override;

<<<<<<< HEAD

private slots:
    void actualizarTiempo();

=======
>>>>>>> c1a3d3efdcd9b98e84d51bed675734a3c2c455bc
private:

    PanelVida* panelVida = nullptr;


    QGraphicsScene* escena = nullptr;
    ControladorJuego* controlador = nullptr;
    QTimer* temporizadorMovimiento = nullptr;

    enum class EstadoPartida { EnCurso, Derrota, Victoria };
    EstadoPartida estadoPartida = EstadoPartida::EnCurso;


    QGraphicsTextItem* textoVida = nullptr;
    QGraphicsTextItem* textoResultado = nullptr;
    QGraphicsPixmapItem* corazonPrueba = nullptr;

    void crearInterfaz();
    void actualizarPartida();
    void actualizarInterfazVida();
    void finalizarPartida(bool victoria);
<<<<<<< HEAD


    QTimer* temporizadorNivel = nullptr;
    int tiempoRestante = 0;
    int tiempoInicial=60;

    QGraphicsTextItem* textoTiempo = nullptr;
    QGraphicsPixmapItem* itemReloj = nullptr;

    qreal posicionBaseRelojX = 0.0;
    qreal posicionBaseRelojY = 0.0;

    void iniciarCronometro(int segundos);
    void detenerCronometro();
=======
>>>>>>> c1a3d3efdcd9b98e84d51bed675734a3c2c455bc
};

#endif // VENTANAJUEGO_H
