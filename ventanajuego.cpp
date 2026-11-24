#include "ventanajuego.h"

#include <QBrush>
#include <QPen>
#include <iostream>

VentanaJuego::VentanaJuego()
{
    setWindowTitle("Bomberman - Mi primera ventana");

    escena = new QGraphicsScene(this);
    setScene(escena);
    escena->setSceneRect(0, 0, 1500, 770);

    mapa = new Mapa(11, 13, 70);
    mapa->crearMapa();

    construirMapa();

    jugador = new Jugador(100, 100, tamanoJugador, 5);
    escena->addItem(jugador->obtenerFigura());

    temporizadorMovimiento = new QTimer(this);

    connect(
        temporizadorMovimiento,
        &QTimer::timeout,
        this,
        &VentanaJuego::actualizarMovimiento
        );

    connect(
        temporizadorMovimiento,
        &QTimer::timeout,
        this,
        &VentanaJuego::revisarItemsJugador
        );

    connect(
        temporizadorMovimiento,
        &QTimer::timeout,
        this,
        &VentanaJuego::actualizarBombas
        );

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

    delete jugador;
    delete mapa;
}

void VentanaJuego::keyPressEvent(QKeyEvent* evento)
{
    if (evento == nullptr) {
        return;
    }

    if (jugador == nullptr) {
        QGraphicsView::keyPressEvent(evento);
        return;
    }

    switch (evento->key()) {
    case Qt::Key_W:
        jugador->establecerDireccion(Direccion::Arriba);
        break;

    case Qt::Key_S:
        jugador->establecerDireccion(Direccion::Abajo);
        break;

    case Qt::Key_A:
        jugador->establecerDireccion(Direccion::Izquierda);
        break;

    case Qt::Key_D:
        jugador->establecerDireccion(Direccion::Derecha);
        break;

    case Qt::Key_Space:
        if (!evento->isAutoRepeat()) {
            colocarBomba();
        }
        break;

    default:
        QGraphicsView::keyPressEvent(evento);
        return;
    }

    evento->accept();
}

void VentanaJuego::keyReleaseEvent(QKeyEvent* evento)
{
    if (evento == nullptr) {
        return;
    }

    if (jugador == nullptr) {
        QGraphicsView::keyReleaseEvent(evento);
        return;
    }

    if (evento->isAutoRepeat()) {
        evento->accept();
        return;
    }

    Direccion direccion = jugador->obtenerDireccion();

    bool detener =
        (evento->key() == Qt::Key_W &&
         direccion == Direccion::Arriba) ||
        (evento->key() == Qt::Key_S &&
         direccion == Direccion::Abajo) ||
        (evento->key() == Qt::Key_A &&
         direccion == Direccion::Izquierda) ||
        (evento->key() == Qt::Key_D &&
         direccion == Direccion::Derecha);

    if (detener) {
        jugador->establecerDireccion(Direccion::Null);
        evento->accept();
        return;
    }

    QGraphicsView::keyReleaseEvent(evento);
}

void VentanaJuego::actualizarMovimiento()
{
    if (jugador == nullptr || mapa == nullptr) {
        return;
    }

    jugador->actualizarMovimiento(
        mapa,
        mapa->obtenerTamanoCelda()
        );
}

void VentanaJuego::construirMapa()
{
    if (mapa == nullptr || escena == nullptr) {
        return;
    }

    int tamanoCelda = mapa->obtenerTamanoCelda();

    for (int fila = 0; fila < mapa->obtenerFilas(); fila++) {
        for (int columna = 0;
             columna < mapa->obtenerColumnas();
             columna++) {

            Celda* celda = mapa->obtenerCelda(fila, columna);

            if (celda != nullptr) {
                celda->dibujar(
                    escena,
                    columna * tamanoCelda,
                    fila * tamanoCelda,
                    tamanoCelda,
                    tamanoJugador
                    );
            }
        }
    }
}

void VentanaJuego::colocarBomba()
{
    if (jugador == nullptr ||
        escena == nullptr ||
        mapa == nullptr) {
        return;
    }

    if (!jugador->puedeColocarBomba()) {
        return;
    }

    QGraphicsRectItem* figura = jugador->obtenerFigura();

    if (figura == nullptr) {
        return;
    }

    int x = figura->pos().x();
    int y = figura->pos().y();

    // Conserva el orden usado por tu codigo original:
    // primero la coordenada vertical y despues la horizontal.
    jugador->obtenerBombas().agregar(
        y,
        x,
        3000,
        jugador->obtenerAlcance(),
        escena
        );

    jugador->bombaColocada();
}

void VentanaJuego::actualizarBombas()
{
    if (mapa == nullptr || jugador == nullptr) {
        return;
    }

    ColaBomba& cola = jugador->obtenerBombas();

    while (cola.primeraBombaVencida()) {
        int x = 0;
        int y = 0;
        int alcance = 0;

        if (!cola.obtenerPosicionPrimera(x, y, alcance)) {
            break;
        }

        // Retirar primero evita que la propia explosion
        // vuelva a encontrar esta bomba en la cola.
        cola.eliminar();
        jugador->bombaExplotada();

        crearExplosion(
            x,
            y,
            mapa->obtenerTamanoCelda(),
            alcance
            );
    }
}

void VentanaJuego::crearExplosion(
    int x,
    int y,
    int tamanoCelda,
    int alcance)
{
    if (mapa == nullptr ||
        escena == nullptr ||
        jugador == nullptr ||
        tamanoCelda <= 0 ||
        alcance <= 0) {
        return;
    }

    x += tamanoJugador / 4;
    y += tamanoJugador / 4;

    int centroX = x + tamanoJugador / 4;
    int centroY = y + tamanoJugador / 4;

    int filaBomba = centroY / tamanoCelda;
    int columnaBomba = centroX / tamanoCelda;

    if (mapa->obtenerCelda(filaBomba, columnaBomba) == nullptr) {
        return;
    }

    QGraphicsRectItem* flamaCentral = escena->addRect(
        0,
        0,
        tamanoFlama,
        tamanoFlama,
        QPen(Qt::red),
        QBrush(Qt::yellow)
        );

    flamaCentral->setPos(x, y);

    QTimer::singleShot(500, this, [flamaCentral]() {
        delete flamaCentral;
    });

    // 0: arriba, 1: abajo, 2: izquierda, 3: derecha.
    const int cambioFila[4] = {-1, 1, 0, 0};
    const int cambioColumna[4] = {0, 0, -1, 1};

    bool direccionValida[4] = {true, true, true, true};
    int direccionAlcance[4] = {0, 0, 0, 0};
    int limiteDireccion[4] = {
        alcance, alcance, alcance, alcance
    };

    const int retrasoPorAnillo = 100;

    for (int i = 0;
         i < limiteDireccion[0] ||
         i < limiteDireccion[1] ||
         i < limiteDireccion[2] ||
         i < limiteDireccion[3];
         i++) {

        int distancia = i + 1;

        for (int direccion = 0; direccion < 4; direccion++) {
            if (!direccionValida[direccion] ||
                i >= limiteDireccion[direccion]) {
                continue;
            }

            int filaFlama =
                filaBomba + cambioFila[direccion] * distancia;

            int columnaFlama =
                columnaBomba + cambioColumna[direccion] * distancia;

            Celda* celda =
                mapa->obtenerCelda(filaFlama, columnaFlama);

            if (celda == nullptr) {
                direccionValida[direccion] = false;
                continue;
            }

            if (celda->esObstaculo()) {
                celda->recibirExplosion();

                bool cajaDestruida = celda->estaDestruida();

                if (cajaDestruida) {
                    direccionAlcance[direccion]++;
                }

                TipoItem item = celda->obtenerItem();

                bool activoAlcance =
                    cajaDestruida &&
                    item == TipoItem::Alcance;

                bool activoItem =
                    cajaDestruida &&
                    (item == TipoItem::Portal ||
                     item == TipoItem::BombaExtra ||
                     item == TipoItem::Velocidad ||
                     item == TipoItem::cura ||
                     item == TipoItem::masVida);

                if (activoAlcance) {
                    limiteDireccion[direccion] += tamanoItemAlcance;
                }

                if (activoItem) {
                    celda->setItemDisponible();
                }

                if (!activoAlcance) {
                    direccionValida[direccion] = false;
                }
            }
            else if (reaccionEnCadena(
                         filaFlama,
                         columnaFlama,
                         retrasoPorAnillo * distancia)) {

                direccionValida[direccion] = false;
            }
            else {
                direccionAlcance[direccion]++;
            }
        }
    }

    for (int direccion = 0; direccion < 4; direccion++) {
        for (int i = 0; i < direccionAlcance[direccion]; i++) {
            int desplazamiento = tamanoCelda * (i + 1);
            int retraso = retrasoPorAnillo * i;

            int xFlama =
                x + cambioColumna[direccion] * desplazamiento;

            int yFlama =
                y + cambioFila[direccion] * desplazamiento;

            QTimer::singleShot(
                retraso,
                this,
                [this, xFlama, yFlama]() {
                    QGraphicsRectItem* flama = escena->addRect(
                        0,
                        0,
                        tamanoFlama,
                        tamanoFlama,
                        QPen(Qt::red),
                        QBrush(Qt::yellow)
                        );

                    flama->setPos(xFlama, yFlama);

                    QTimer::singleShot(500, this, [flama]() {
                        delete flama;
                    });
                }
                );
        }
    }
}

void VentanaJuego::revisarItemsJugador()
{
    if (jugador == nullptr || mapa == nullptr) {
        return;
    }

    QGraphicsRectItem* figura = jugador->obtenerFigura();

    if (figura == nullptr) {
        return;
    }

    int x = figura->pos().x();
    int y = figura->pos().y();
    int tamanoCelda = mapa->obtenerTamanoCelda();

    int fila = (y + tamanoJugador / 4) / tamanoCelda;
    int columna = (x + tamanoJugador / 4) / tamanoCelda;

    Celda* celda = mapa->obtenerCelda(fila, columna);

    if (celda == nullptr || !celda->isItemDisponible()) {
        return;
    }

    if (celda->obtenerItem() == TipoItem::Portal) {
        std::cout << "gano" << std::endl;
        return;
    }

    jugador->recogerItem(celda->obtenerItem());
    celda->consumirItem();
}

bool VentanaJuego::reaccionEnCadena(
    int filaFlama,
    int columnaFlama,
    int retraso)
{
    if (mapa == nullptr || jugador == nullptr) {
        return false;
    }

    int xBomba = 0;
    int yBomba = 0;
    int alcanceBomba = 0;
    int tamanoCelda = mapa->obtenerTamanoCelda();

    ColaBomba& cola = jugador->obtenerBombas();

    bool encontrada = cola.localizarBomba(
        filaFlama,
        columnaFlama,
        xBomba,
        yBomba,
        alcanceBomba,
        tamanoCelda,
        tamanoJugador
        );

    if (!encontrada) {
        return false;
    }

    // Reservamos la detonacion retirando la bomba de la cola.
    // Asi otra flama no programa la misma bomba otra vez.
    cola.eliminarBombaEn(
        filaFlama,
        columnaFlama,
        tamanoCelda,
        tamanoJugador
        );

    QTimer::singleShot(
        retraso,
        this,
        [this, xBomba, yBomba, alcanceBomba, tamanoCelda]() {
            jugador->bombaExplotada();

            crearExplosion(
                xBomba,
                yBomba,
                tamanoCelda,
                alcanceBomba
                );
        }
        );

    return true;
}