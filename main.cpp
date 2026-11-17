#include <QApplication>
#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "Boton.h"
#include "ventanajuego.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Ventana principal
    QWidget ventana;
    ventana.setWindowTitle("Bomberman");
    ventana.resize(700, 600);

    // Contenedor de pantallas
    QStackedWidget *pantallas = new QStackedWidget(&ventana);

    // =================================
    // PANTALLA 1: MENU PRINCIPAL
    // =================================

    QWidget *menu = new QWidget();

    QVBoxLayout *principal = new QVBoxLayout(menu);

    QLabel *placeholder = new QLabel("MENU PRINCIPAL");

    placeholder->setAlignment(Qt::AlignCenter);

    QGridLayout *grid = new QGridLayout();

    Boton btnJugar(menu, "Jugar", 250, 70, "#27ae60");
    Boton btnInstrucciones(menu, "Instrucciones", 250, 70, "#2980b9");
    Boton btnRanking(menu, "Ranking", 250, 70, "#8e44ad");
    Boton btnSalir(menu, "Salir", 250, 70, "#c0392b");

    grid->addWidget(btnJugar.obtenerBoton(), 0, 0);
    grid->addWidget(btnInstrucciones.obtenerBoton(), 0, 1);
    grid->addWidget(btnRanking.obtenerBoton(), 1, 0);
    grid->addWidget(btnSalir.obtenerBoton(), 1, 1);

    principal->addWidget(placeholder, 1);
    principal->addLayout(grid);

    // =================================
    // PANTALLA 2: JUEGO
    // =================================

    VentanaJuego *juego = new VentanaJuego();

    // =================================
    // AGREGAR PANTALLAS
    // =================================

    pantallas->addWidget(menu);
    pantallas->addWidget(juego);

    // Layout de la ventana principal
    QVBoxLayout *layoutVentana = new QVBoxLayout(&ventana);

    layoutVentana->setContentsMargins(0, 0, 0, 0);
    layoutVentana->addWidget(pantallas);

    // =================================
    // CAMBIO DE PANTALLAS
    // =================================

    QObject::connect(
        btnJugar.obtenerBoton(),
        &QPushButton::clicked,
        [=]() {
            pantallas->setCurrentWidget(juego);
        }
        );

    QObject::connect(
        btnSalir.obtenerBoton(),
        &QPushButton::clicked,
        &ventana,
        &QWidget::close
        );

    ventana.show();

    return app.exec();
}