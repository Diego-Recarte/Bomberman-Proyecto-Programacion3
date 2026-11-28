#include "ventanaprincipal.h"

#include <QStackedWidget>
#include <QVBoxLayout>

#include "ventanamenu.h"
#include "ventanabienvenida.h"
#include "ventanajuego.h"
#include "ventanainiciosesion.h"
#include "ventanaregistro.h"
#include "ventanaranking.h"
#include <QMessageBox>

#include <iostream>


VentanaPrincipal::VentanaPrincipal( SistemaUsuarios& sistema, QWidget* padre): QWidget(padre), sistema(sistema){

    setWindowTitle("Bomberman");

    pantallas = new QStackedWidget(this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(pantallas);



    bienvenida = new VentanaBienvenida();
    pantallas->addWidget(bienvenida);

    connect(bienvenida,&VentanaBienvenida::salirSolicitado,this,&QWidget::close);


    inicioSesion = new VentanaInicioSesion(sistema);
    pantallas->addWidget(inicioSesion);
    connect( bienvenida, &VentanaBienvenida::inicioSesionSolicitado, this, &VentanaPrincipal::mostrarInicioSesion );
    connect(inicioSesion,&VentanaInicioSesion::volverSolicitado,this,&VentanaPrincipal::mostrarBienvenida);

    registro = new VentanaRegistro(sistema);
    pantallas->addWidget(registro);

    connect(bienvenida,&VentanaBienvenida::registroSolicitado,this,&VentanaPrincipal::mostrarRegistro);

    connect(registro,&VentanaRegistro::volverSolicitado,this,&VentanaPrincipal::mostrarBienvenida);


    menu = new VentanaMenu(sistema);
    pantallas->addWidget(menu);

    connect( menu, &VentanaMenu::sesionCerrada, this, &VentanaPrincipal::mostrarBienvenida );
    connect(menu,&VentanaMenu::jugarSolicitado,this,&VentanaPrincipal::mostrarJuego);

    connect(menu,&VentanaMenu::salirSolicitado,this,&QWidget::close);

    connect(inicioSesion,&VentanaInicioSesion::accesoExitoso,this,&VentanaPrincipal::mostrarMenu);

    connect(registro,&VentanaRegistro::registroExitoso,this,&VentanaPrincipal::mostrarMenu);
    connect(menu,&VentanaMenu::cuentaBorrada,this,&VentanaPrincipal::mostrarBienvenida);


    ranking = new VentanaRanking(sistema);
    pantallas->addWidget(ranking);

    connect( menu, &VentanaMenu::rankingSolicitado, this, &VentanaPrincipal::mostrarRanking );

    connect( ranking, &VentanaRanking::volverSolicitado, this, &VentanaPrincipal::mostrarMenu );
    mostrarBienvenida();
}

void VentanaPrincipal::mostrarMenu(){

    pantallas->setCurrentWidget(menu);
}

void VentanaPrincipal::mostrarJuego()
{
    if (juego == nullptr) {
        juego = new VentanaJuego();
        pantallas->addWidget(juego);
    }

    pantallas->setCurrentWidget(juego);
}

void VentanaPrincipal::mostrarBienvenida(){

    pantallas->setCurrentWidget(bienvenida);
}
void VentanaPrincipal::mostrarInicioSesion(){
    std::cout<<"mostrar"<<std::endl;
    pantallas->setCurrentWidget(inicioSesion);
    inicioSesion->limpiarCampos();
}
void VentanaPrincipal::mostrarRegistro()
{
    pantallas->setCurrentWidget(registro);
    registro->limpiarCampos();
}

void VentanaPrincipal::mostrarRanking(){
    ranking->actualizarRanking();
    pantallas->setCurrentWidget(ranking);
}