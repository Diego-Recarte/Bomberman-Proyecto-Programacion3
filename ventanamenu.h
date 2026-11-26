#ifndef VENTANAMENU_H
#define VENTANAMENU_H

#include <QWidget>

class Boton;
class SistemaUsuarios;

class VentanaMenu : public QWidget{
    Q_OBJECT

public:
    explicit VentanaMenu(SistemaUsuarios& sistema, QWidget* padre = nullptr );
    ~VentanaMenu() override;

signals:
    void jugarSolicitado();
    void instruccionesSolicitadas();
    void rankingSolicitado();
    void salirSolicitado();
    void sesionCerrada();
    void cuentaBorrada();

private:
    Boton* btnJugar = nullptr;
    Boton* btnInstrucciones = nullptr;
    Boton* btnRanking = nullptr;
    Boton* btnSalir = nullptr;

    SistemaUsuarios& sistemaUsuarios;

    Boton* btnCerrarSesion = nullptr;
    Boton* btnBorrarCuenta = nullptr;

    void borrarCuenta();

    void cerrarSesion();

};

#endif // VENTANAMENU_H