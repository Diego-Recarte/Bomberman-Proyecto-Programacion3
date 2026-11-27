#include <QApplication>
#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "Boton.h"
#include "Ventanas/ventanajuego.h"
#include <QApplication>

#include "Ventanas/ventanaprincipal.h"
#include "Ventanas/ventanaprincipal.h"
#include "sistemausuarios.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    SistemaUsuarios sistemaUsuarios;
    sistemaUsuarios.cargarContactosDesdeArchivo();

    VentanaPrincipal ventana(sistemaUsuarios);
    ventana.showMaximized();

    sistemaUsuarios.guardarAgendaEnArchivo();


    return app.exec();
}

