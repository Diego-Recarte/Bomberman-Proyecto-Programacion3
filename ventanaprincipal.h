
#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QWidget>

#include "sistemausuarios.h"

class QStackedWidget;
class VentanaMenu;
class VentanaJuego;
class VentanaBienvenida;
class VentanaInicioSesion;
class VentanaRegistro;
class SistemaUsuarios;
class VentanaRanking;


class VentanaPrincipal : public QWidget
{
public:
    explicit VentanaPrincipal(SistemaUsuarios& sistema,QWidget* padre = nullptr);

private:
    VentanaRanking* ranking = nullptr;
    QStackedWidget* pantallas = nullptr;

    VentanaMenu* menu = nullptr;
    VentanaJuego* juego = nullptr;



    VentanaBienvenida* bienvenida = nullptr;
    VentanaInicioSesion* inicioSesion = nullptr;

    VentanaRegistro* registro = nullptr;

    void mostrarRegistro();

    void mostrarBienvenida();
    void mostrarInicioSesion();
    void mostrarMenu();
    void mostrarJuego();
    SistemaUsuarios& sistema;

private slots:
    void mostrarRanking();
};

#endif // VENTANAPRINCIPAL_H


