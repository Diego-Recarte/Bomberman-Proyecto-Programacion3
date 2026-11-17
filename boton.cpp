#include "Boton.h"

Boton::Boton(QWidget *ventana, QString texto,
             int ancho, int alto, QString color)
{
    boton = new QPushButton(texto, ventana);

    boton->setFixedSize(ancho, alto);

    boton->setStyleSheet(
        "QPushButton {"
        "background-color: " + color + ";"
                  "color: white;"
                  "border-radius: 8px;"
                  "font-size: 25px;"
                  "}"

                  "QPushButton:hover {"
                  "background-color: #555555;"
                  "}"
        );
}

QPushButton* Boton::obtenerBoton()
{
    return boton;
}