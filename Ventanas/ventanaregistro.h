#ifndef VENTANAREGISTRO_H
#define VENTANAREGISTRO_H

#include <QWidget>
#include <QString>

class SistemaUsuarios;

class QLineEdit;

class VentanaRegistro : public QWidget{
    Q_OBJECT

public:
    explicit VentanaRegistro(SistemaUsuarios& sistema, QWidget* padre = nullptr);

    void limpiarCampos();

signals:
    void volverSolicitado();

    void registroSolicitado(const QString& nombre,const QString& contrasena);
    void registroExitoso();

private:
    QLineEdit* campoNombre = nullptr;
    QLineEdit* campoContrasena = nullptr;
    QLineEdit* campoConfirmacion = nullptr;

    void solicitarRegistro();
    SistemaUsuarios& sistemaUsuarios;
};

#endif // VENTANAREGISTRO_H