#ifndef VENTANABIENVENIDA_H
#define VENTANABIENVENIDA_H

#include <QWidget>

class VentanaBienvenida : public QWidget{
    Q_OBJECT

public:
    explicit VentanaBienvenida(QWidget* padre = nullptr);

signals:
    void inicioSesionSolicitado();
    void registroSolicitado();
    void salirSolicitado();
};

#endif // VENTANABIENVENIDA_H