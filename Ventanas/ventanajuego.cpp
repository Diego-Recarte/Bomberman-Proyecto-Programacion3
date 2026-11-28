#include "ventanajuego.h"
#include "controladorjuego.h"
#include <QBrush>
#include <QFont>
#include <QGraphicsTextItem>
#include <QPen>
#include <QPixmap>
#include "panelvida.h"
#include <QGraphicsPixmapItem>


VentanaJuego::VentanaJuego(){
    setWindowTitle("Bomberman - Mi primera ventana");
    escena = new QGraphicsScene(this);
    setScene(escena);
    escena->setSceneRect(0, 0, 1500, 770);

    const QPixmap fondo(":/ladrillosfondo.jpg");
    if (!fondo.isNull()){
        const QPixmap imagenAjustada = fondo.scaled(1500,770,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

        escena->setBackgroundBrush(QBrush(imagenAjustada));
    }else{
        escena->setBackgroundBrush(QBrush(Qt::yellow));
    }




    controlador = new ControladorJuego(escena);

    crearInterfaz();



    temporizadorNivel = new QTimer(this);
    iniciarCronometro(tiempoInicial);

    connect(temporizadorNivel,&QTimer::timeout,this,&VentanaJuego::actualizarTiempo);



    temporizadorMovimiento = new QTimer(this);
    connect(temporizadorMovimiento, &QTimer::timeout,this, &VentanaJuego::actualizarPartida);
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

    delete panelVida;
    panelVida = nullptr;
    if (temporizadorNivel != nullptr) {
        temporizadorNivel->stop();
    }
}

void VentanaJuego::keyPressEvent(QKeyEvent* evento)
{
    if (evento == nullptr) {
        return;
    }
    if (estadoPartida != EstadoPartida::EnCurso|| controlador == nullptr) {
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


    QPixmap imagenReloj(":/reloj");

    itemReloj = new QGraphicsPixmapItem(imagenReloj);

    if (!imagenReloj.isNull()) {
        itemReloj->setPixmap(imagenReloj.scaled( 200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation ) );
    }

    itemReloj->setPos(960, 320);
    itemReloj->setZValue(102);
    escena->addItem(itemReloj);

    posicionBaseRelojX = itemReloj->x();
    posicionBaseRelojY = itemReloj->y();

    textoTiempo = escena->addText("");
    textoTiempo->setDefaultTextColor(Qt::white);
    textoTiempo->setFont(QFont("Arial", 60, QFont::Bold));
    textoTiempo->setPos(1150, 370);
    textoTiempo->setZValue(102);

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

    panelVida = new PanelVida(escena, 1000, 50);

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

void VentanaJuego::actualizarInterfazVida(){
    if (controlador == nullptr)
    {
        return;
    }

    const int vida = controlador->obtenerVidaActual();
    const int vidaMaxima = controlador->obtenerVidaMaxima();


    if (panelVida != nullptr){
        panelVida->actualizar(vida, vidaMaxima);
    }
}

void VentanaJuego::finalizarPartida(bool victoria){
    if (estadoPartida != EstadoPartida::EnCurso) {
        return;
    }

    estadoPartida = victoria? EstadoPartida::Victoria: EstadoPartida::Derrota;

    if (temporizadorMovimiento != nullptr) {
        temporizadorMovimiento->stop();
    }

    detenerCronometro();

    if (textoResultado != nullptr) {
        textoResultado->setPlainText(victoria ? "¡Victoria!" : "¡Derrota!");
        textoResultado->setVisible(true);
    }
}


void VentanaJuego::iniciarCronometro(int segundos){
    tiempoRestante = segundos;

    actualizarTiempo();

    if (temporizadorNivel != nullptr) {
        temporizadorNivel->start(1000);
    }
}

void VentanaJuego::detenerCronometro(){
    if (temporizadorNivel != nullptr) {
        temporizadorNivel->stop();
    }

    if (itemReloj != nullptr) {
        itemReloj->setPos(posicionBaseRelojX,posicionBaseRelojY);
    }
}

void VentanaJuego::actualizarTiempo(){
    if (estadoPartida != EstadoPartida::EnCurso) {
        return;
    }

    if (tiempoRestante > 0) {
        --tiempoRestante;
    }

    if (textoTiempo != nullptr) {
        textoTiempo->setPlainText(QString::fromStdString(std::to_string(tiempoRestante)));
    }

    if (itemReloj != nullptr) {
        if (tiempoRestante < 30) {
            double vibracion = (tiempoRestante % 2 == 1) ? 2.0 : -2.0;
            itemReloj->setPos(posicionBaseRelojX + vibracion,posicionBaseRelojY-vibracion);
        } else {
            itemReloj->setPos(posicionBaseRelojX,posicionBaseRelojY);
        }
    }

    if (tiempoRestante == 0) {
        detenerCronometro();
        finalizarPartida(false);
    }
}