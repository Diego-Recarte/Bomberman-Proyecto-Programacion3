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


    QWidget ventana;
    ventana.setWindowTitle("Bomberman");
    ventana.showMaximized();



    QStackedWidget *pantallas = new QStackedWidget(&ventana);




    QWidget *menu = new QWidget();

    menu->setObjectName("menuPrincipal");

    menu->setStyleSheet( "QWidget#menuPrincipal {" "    border-image: url(:/inicio) 0 0 0 0 stretch stretch;" "}" );

    QVBoxLayout *principal = new QVBoxLayout(menu);

    QLabel *placeholder = new QLabel(" ");


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




    VentanaJuego *juego = new VentanaJuego();



    pantallas->addWidget(menu);
    pantallas->addWidget(juego);

    QVBoxLayout *layoutVentana = new QVBoxLayout(&ventana);

    layoutVentana->setContentsMargins(0, 0, 0, 0);
    layoutVentana->addWidget(pantallas);




    QObject::connect(btnJugar.obtenerBoton(),&QPushButton::clicked,[=]() {
        pantallas->setCurrentWidget(juego);
    });

    QObject::connect(btnSalir.obtenerBoton(),&QPushButton::clicked,&ventana,&QWidget::close);




    return app.exec();
}