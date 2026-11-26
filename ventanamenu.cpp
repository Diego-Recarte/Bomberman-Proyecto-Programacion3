#include "ventanamenu.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "Boton.h"
#include "sistemausuarios.h"
#include <QMessageBox>
VentanaMenu::VentanaMenu(SistemaUsuarios& sistema,QWidget* padre): QWidget(padre),sistemaUsuarios(sistema)
{

    setObjectName("menu");

    setStyleSheet("QWidget#menuPrincipal {""    border-image: url(:/menu) 0 0 0 0 stretch stretch;""}");

    QVBoxLayout* principal = new QVBoxLayout(this);

    QLabel* placeholder = new QLabel(" ", this);
    placeholder->setAlignment(Qt::AlignCenter);

    QGridLayout* grid = new QGridLayout();

    btnJugar = new Boton( this, "Jugar", 250, 70, "#27ae60");

    btnInstrucciones = new Boton(this, "Instrucciones", 250, 70, "#2980b9");

    btnRanking = new Boton(this, "Ranking", 250, 70, "#8e44ad");

    btnSalir = new Boton(this, "Salir", 250, 70, "#c0392b");

    btnCerrarSesion = new Boton( this, "Cerrar sesión", 250, 70, "#e67e22");

    btnBorrarCuenta = new Boton(this,"Borrar cuenta",250,70,"#922b21");

    grid->addWidget(btnJugar->obtenerBoton(), 0, 0);
    grid->addWidget(btnInstrucciones->obtenerBoton(), 0, 1);
    grid->addWidget(btnRanking->obtenerBoton(), 1, 0);
    grid->addWidget(btnSalir->obtenerBoton(), 1, 1);
    grid->addWidget(btnCerrarSesion->obtenerBoton(), 2, 0);
    grid->addWidget(btnBorrarCuenta->obtenerBoton(), 2, 1);

    principal->addWidget(placeholder, 1);
    principal->addLayout(grid);

    connect(btnBorrarCuenta->obtenerBoton(),&QPushButton::clicked,this,&VentanaMenu::borrarCuenta);

    connect(btnJugar->obtenerBoton(),&QPushButton::clicked,this,&VentanaMenu::jugarSolicitado);

    connect(btnInstrucciones->obtenerBoton(),&QPushButton::clicked,this,&VentanaMenu::instruccionesSolicitadas);

    connect(btnRanking->obtenerBoton(),&QPushButton::clicked,this,&VentanaMenu::rankingSolicitado);

    connect(btnSalir->obtenerBoton(),&QPushButton::clicked,this,&VentanaMenu::salirSolicitado);
    connect(btnCerrarSesion->obtenerBoton(),&QPushButton::clicked,this,&VentanaMenu::cerrarSesion);
}

void VentanaMenu::borrarCuenta(){
    const auto respuesta = QMessageBox::question(this,"Borrar cuenta","¿Quieres borrar tu cuenta?\n""Se eliminarán sus datos de la lista de usuarios.",QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (respuesta != QMessageBox::Yes) {
        return;
    }

    if (!sistemaUsuarios.borrarCuentaActiva()) {
        QMessageBox::warning( this, "Borrar cuenta", "No se pudo borrar la cuenta activa." );
        return;
    }

    QMessageBox::information( this, "Cuenta borrada", "La cuenta se eliminó correctamente." );
    sistemaUsuarios.guardarAgendaEnArchivo();

    emit cuentaBorrada();
}

VentanaMenu::~VentanaMenu()
{
    delete btnJugar;
    delete btnInstrucciones;
    delete btnRanking;
    delete btnSalir;
    delete btnCerrarSesion;
    delete btnBorrarCuenta;
}
void VentanaMenu::cerrarSesion(){
    sistemaUsuarios.cerrarSesion();
    sistemaUsuarios.guardarAgendaEnArchivo();

    emit sesionCerrada();
}