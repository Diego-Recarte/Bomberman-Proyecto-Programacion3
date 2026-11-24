#ifndef BOTON_H
#define BOTON_H

#include <QPushButton>
#include <QWidget>
#include <QString>

class Boton
{
private:
    QPushButton *boton;

public:
    Boton(QWidget *ventana,QString texto, int ancho = 150,  int alto = 40, QString color = "#3498db");

    QPushButton* obtenerBoton();
};

#endif