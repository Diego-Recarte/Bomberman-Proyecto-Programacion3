#include "ventanainiciosesion.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "sistemausuarios.h"

VentanaInicioSesion::VentanaInicioSesion(SistemaUsuarios& sistema,QWidget* padre): QWidget(padre), sistemaUsuarios(sistema){
    setObjectName("pantallaInicioSesion");

    setStyleSheet(
        "QWidget#pantallaInicioSesion {"
        "    border-image: url(:/inicio) 0 0 0 0 stretch stretch;"
        "}"

        "QWidget#panelAcceso {"
        "    background-color: rgba(255, 255, 255, 230);"
        "    border-radius: 12px;"
        "}"

        "QLineEdit {"
        "    background-color: white;"
        "    color: black;"
        "    border: 1px solid gray;"
        "    border-radius: 6px;"
        "    padding: 8px;"
        "    font-size: 18px;"
        "}"

        "QPushButton {"
        "    background-color: #2980b9;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 8px;"
        "    padding: 10px;"
        "    font-size: 18px;"
        "}"

        "QPushButton:hover {"
        "    background-color: #3498db;"
        "}"
        );

    QVBoxLayout* principal = new QVBoxLayout(this);

    QWidget* panel = new QWidget(this);
    panel->setObjectName("panelAcceso");
    panel->setFixedWidth(380);

    QVBoxLayout* formulario = new QVBoxLayout(panel);
    formulario->setContentsMargins(25, 25, 25, 25);
    formulario->setSpacing(15);

    QLabel* titulo = new QLabel("Iniciar sesión", panel);
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("color: black; font-size: 24px;");

    campoNombre = new QLineEdit(panel);
    campoNombre->setPlaceholderText("Nombre de usuario");

    campoContrasena = new QLineEdit(panel);
    campoContrasena->setPlaceholderText("Contraseña");
    campoContrasena->setEchoMode(QLineEdit::Password);

    QPushButton* btnEntrar = new QPushButton("Entrar", panel);
    QPushButton* btnVolver = new QPushButton("Volver", panel);

    formulario->addWidget(titulo);
    formulario->addWidget(campoNombre);
    formulario->addWidget(campoContrasena);
    formulario->addWidget(btnEntrar);
    formulario->addWidget(btnVolver);

    principal->addStretch();
    principal->addWidget(panel, 0, Qt::AlignHCenter);
    principal->addStretch();

    connect( btnEntrar,&QPushButton::clicked,this,&VentanaInicioSesion::solicitarAcceso);

    connect( btnVolver,&QPushButton::clicked,this,[this]() { limpiarCampos();emit volverSolicitado();});
}

void VentanaInicioSesion::solicitarAcceso()
{
    const QString nombre = campoNombre->text().trimmed();
    const QString contrasena = campoContrasena->text();

    if (nombre.isEmpty() || contrasena.isEmpty()) {
        QMessageBox::warning(this,"Datos incompletos","Escribe tu nombre y tu contraseña.");
        return;
    }

    std::string error;

    const bool valido = sistemaUsuarios.iniciarSesion(nombre.toStdString(),contrasena.toStdString(),error);

    if (!valido) {
        QMessageBox::warning(this,"Inicio de sesión",QString::fromStdString(error));
        return;
    }

    limpiarCampos();
    emit accesoExitoso();
}

void VentanaInicioSesion::limpiarCampos()
{
    campoNombre->clear();
    campoContrasena->clear();
    campoNombre->setFocus();
}