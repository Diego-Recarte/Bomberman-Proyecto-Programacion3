#include "ventanaregistro.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include "sistemausuarios.h"

VentanaRegistro::VentanaRegistro (SistemaUsuarios& sistema,QWidget* padre): QWidget(padre), sistemaUsuarios(sistema){
    setObjectName("pantallaRegistro");

    setStyleSheet(
        "QWidget#pantallaRegistro {"
        "    border-image: url(:/inicio) 0 0 0 0 stretch stretch;"
        "}"

        "QWidget#panelRegistro {"
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
    panel->setObjectName("panelRegistro");
    panel->setFixedWidth(380);

    QVBoxLayout* formulario = new QVBoxLayout(panel);
    formulario->setContentsMargins(25, 25, 25, 25);
    formulario->setSpacing(15);

    QLabel* titulo = new QLabel("Crear cuenta", panel);
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("color: black; font-size: 24px;");

    campoNombre = new QLineEdit(panel);
    campoNombre->setPlaceholderText("Nombre de usuario");

    campoContrasena = new QLineEdit(panel);
    campoContrasena->setPlaceholderText("Contraseña");
    campoContrasena->setEchoMode(QLineEdit::Normal);

    campoConfirmacion = new QLineEdit(panel);
    campoConfirmacion->setPlaceholderText("Confirmar contraseña");
    campoConfirmacion->setEchoMode(QLineEdit::Normal);

    QPushButton* btnCrear = new QPushButton("Crear cuenta", panel);

    QPushButton* btnVolver = new QPushButton("Volver", panel);

    formulario->addWidget(titulo);
    formulario->addWidget(campoNombre);
    formulario->addWidget(campoContrasena);
    formulario->addWidget(campoConfirmacion);
    formulario->addWidget(btnCrear);
    formulario->addWidget(btnVolver);

    principal->addStretch();
    principal->addWidget(panel, 0, Qt::AlignHCenter);
    principal->addStretch();

    connect( btnCrear, &QPushButton::clicked, this, &VentanaRegistro::solicitarRegistro );

    connect(btnVolver,&QPushButton::clicked,this,[this]() {
        limpiarCampos();
        emit volverSolicitado();
    });
}

void VentanaRegistro::solicitarRegistro(){
    const QString nombre = campoNombre->text().trimmed();
    const QString contrasena = campoContrasena->text();
    const QString confirmacion = campoConfirmacion->text();

    if (nombre.isEmpty() ||contrasena.isEmpty() ||confirmacion.isEmpty()){
        QMessageBox::warning(this,"Datos incompletos","Completa todos los campos.");
        return;
    }

    if (contrasena != confirmacion) {
        QMessageBox::warning(this,"Contraseña","Las contraseñas no coinciden.");
        return;
    }

    std::string error;

    const bool creado = sistemaUsuarios.registrar(nombre.toStdString(),contrasena.toStdString(),error);

    if (!creado) {QMessageBox::warning(this,"Registro",QString::fromStdString(error));
        return;
    }

    limpiarCampos();
    sistemaUsuarios.guardarAgendaEnArchivo();
    emit registroExitoso();
}

void VentanaRegistro::limpiarCampos(){
    campoNombre->clear();
    campoContrasena->clear();
    campoConfirmacion->clear();

    campoNombre->setFocus();
}