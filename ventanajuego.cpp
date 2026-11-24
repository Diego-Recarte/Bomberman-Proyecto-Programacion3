#include "ventanajuego.h"
#include "controladorjuego.h"
#include <QBrush>
#include <QFont>
#include <QGraphicsTextItem>
#include <QPen>

VentanaJuego::VentanaJuego()
{
    setWindowTitle("Bomberman - Mi primera ventana");
    escena = new QGraphicsScene(this);
    setScene(escena);
    escena->setSceneRect(0, 0, 1500, 770);
    escena->setBackgroundBrush(QBrush(Qt::darkGreen));

    controlador = new ControladorJuego(escena);
    crearInterfaz();

    temporizadorMovimiento = new QTimer(this);
    connect(temporizadorMovimiento, &QTimer::timeout,
            this, &VentanaJuego::actualizarPartida);
    temporizadorMovimiento->start(16);

    setFocusPolicy(Qt::StrongFocus);
    showFullScreen();
    setFocus();
}

VentanaJuego::~VentanaJuego()
{
    if (temporizadorMovimiento != nullptr) {
        temporizadorMovimiento->stop();
    }
    delete controlador;
    controlador = nullptr;
}

void VentanaJuego::keyPressEvent(QKeyEvent* evento)
{
    if (evento == nullptr) {
        return;
    }
    if (estadoPartida != EstadoPartida::EnCurso || controlador == nullptr) {
        evento->accept();
        return;
    }
    if (controlador->procesarTeclaPresionada(evento)) {
        evento->accept();
        return;
    }
    QGraphicsView::keyPressEvent(evento);
}

void VentanaJuego::keyReleaseEvent(QKeyEvent* evento)
{
    if (evento == nullptr) {
        return;
    }
    if (controlador != nullptr && controlador->procesarTeclaLiberada(evento)) {
        evento->accept();
        return;
    }
    QGraphicsView::keyReleaseEvent(evento);
}

void VentanaJuego::crearInterfaz()
{
    if (escena == nullptr) {
        return;
    }
    barraVidaFondo = escena->addRect(0, 0, 184, 24,
                                     QPen(Qt::black), QBrush(Qt::darkGray));
    barraVida = escena->addRect(0, 0, 180, 20,
                                QPen(Qt::NoPen), QBrush(Qt::red));
    barraVidaFondo->setPos(18, 18);
    barraVidaFondo->setZValue(100);
    barraVida->setPos(20, 20);
    barraVida->setZValue(101);

    textoVida = escena->addText("");
    textoVida->setDefaultTextColor(Qt::white);
    textoVida->setFont(QFont("Arial", 12, QFont::Bold));
    textoVida->setPos(20, 45);
    textoVida->setZValue(102);

    textoResultado = escena->addText("");
    textoResultado->setDefaultTextColor(Qt::white);
    textoResultado->setFont(QFont("Arial", 28, QFont::Bold));
    textoResultado->setPos(560, 340);
    textoResultado->setZValue(200);
    textoResultado->setVisible(false);
    actualizarInterfazVida();
}

void VentanaJuego::actualizarPartida()
{
    if (estadoPartida != EstadoPartida::EnCurso) {
        return;
    }
    if (controlador != nullptr) {
        controlador->actualizar(16);
    }
    actualizarInterfazVida();
    if (controlador == nullptr || controlador->obtenerVidaActual() <= 0) {
        finalizarPartida(false);
    } else if (controlador->obtenerCantidadEnemigos() == 0) {
        finalizarPartida(true);
    }
}

void VentanaJuego::actualizarInterfazVida()
{
    if (controlador == nullptr) {
        return;
    }
    const int vida = controlador->obtenerVidaActual();
    const int vidaMaxima = controlador->obtenerVidaMaxima();
    if (barraVida != nullptr && vidaMaxima > 0) {
        barraVida->setRect(0, 0, 180.0 * vida / vidaMaxima, 20);
    }
    if (textoVida != nullptr) {
        textoVida->setPlainText(QString("Vida: %1 / %2").arg(vida).arg(vidaMaxima));
    }
}

void VentanaJuego::finalizarPartida(bool victoria)
{
    if (estadoPartida != EstadoPartida::EnCurso) {
        return;
    }
    estadoPartida = victoria ? EstadoPartida::Victoria : EstadoPartida::Derrota;
    if (temporizadorMovimiento != nullptr) {
        temporizadorMovimiento->stop();
    }
    if (textoResultado != nullptr) {
        textoResultado->setPlainText(victoria ? "¡Victoria!" : "¡Derrota!");
        textoResultado->setVisible(true);
    }
}
