#ifndef VENTANAINICIOSESION_H
#define VENTANAINICIOSESION_H

#include <QWidget>
#include <QString>

class SistemaUsuarios;

class QLineEdit;

class VentanaInicioSesion : public QWidget{
    Q_OBJECT

public:
    explicit VentanaInicioSesion(SistemaUsuarios& sistema,QWidget* padre = nullptr);

    void limpiarCampos();

signals:
    void volverSolicitado();
    void accesoExitoso();


private:
    QLineEdit* campoNombre = nullptr;
    QLineEdit* campoContrasena = nullptr;
    SistemaUsuarios& sistemaUsuarios;

    void solicitarAcceso();
};

#endif // VENTANAINICIOSESION_H