#include "ventanabienvenida.h"

#include <QVBoxLayout>
#include <QPushButton>

VentanaBienvenida::VentanaBienvenida(QWidget* padre): QWidget(padre)
{
    setObjectName("pantallaBienvenida");

    setStyleSheet(
        "QWidget#pantallaBienvenida {"
        "    border-image: url(:/inicio) 0 0 0 0 stretch stretch;"
        "}"

        "QPushButton {"
        "    background-color: #2980b9;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 10px;"
        "    font-size: 20px;"
        "}"

        "QPushButton:hover {"
        "    background-color: #3498db;"
        "}"

        "QPushButton:pressed {"
        "    background-color: #1f618d;"
        "}"
        );

    QVBoxLayout* principal = new QVBoxLayout(this);
    principal->setSpacing(20);

    QPushButton* btnInicioSesion = new QPushButton("Iniciar sesión", this);

    QPushButton* btnCrearCuenta = new QPushButton("Crear cuenta", this);

    QPushButton* btnSalir = new QPushButton("Salir", this );

    btnInicioSesion->setFixedSize(300, 70);
    btnCrearCuenta->setFixedSize(300, 70);
    btnSalir->setFixedSize(300, 70);

    principal->addStretch();

    principal->addWidget(btnInicioSesion, 0, Qt::AlignHCenter);

    principal->addWidget(btnCrearCuenta, 0, Qt::AlignHCenter);

    principal->addWidget(btnSalir, 0, Qt::AlignHCenter);

    principal->addStretch();

    connect(btnInicioSesion,&QPushButton::clicked,this,&VentanaBienvenida::inicioSesionSolicitado);

    connect(btnCrearCuenta,&QPushButton::clicked,this,&VentanaBienvenida::registroSolicitado);

    connect(btnSalir,&QPushButton::clicked,this,&VentanaBienvenida::salirSolicitado);
}