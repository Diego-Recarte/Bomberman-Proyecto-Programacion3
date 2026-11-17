#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "ventanajuego.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication aplicacion(argc, argv);

    VentanaJuego ventana;
   ventana.resize(600, 440);
    ventana.showMaximized();

    return aplicacion.exec();
}
