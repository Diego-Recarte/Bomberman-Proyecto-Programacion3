
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "Boton.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Ventana principal
    QWidget ventana;
    ventana.setWindowTitle("Menu principal");
    ventana.resize(700, 600);

    // Layout principal (vertical)
    QVBoxLayout *principal = new QVBoxLayout(&ventana);

    // PLACEHOLDER (parte superior)
    QLabel *placeholder = new QLabel(
        "Area de contenido", &ventana
        );

    placeholder->setAlignment(Qt::AlignCenter);
    placeholder->setMinimumHeight(180);

    placeholder->setStyleSheet(
        "background-color: #eeeeee;"
        "border: 2px solid #aaaaaa;"
        "font-size: 20px;"
        );

    // GRID (parte inferior)
    QGridLayout *grid = new QGridLayout();

    // Crear botones
    Boton btnJugar(&ventana, "Jugar", 250, 70, "#27ae60");
    Boton btnInstruciones(&ventana, "Instruciones", 250, 70, "#2980b9");
    Boton btnRanking(&ventana, "Ranking", 250, 70, "#8e44ad");
    Boton btnSalir(&ventana, "Salir", 250, 70, "#c0392b");

    // Distribuir botones 2x2
    grid->addWidget(btnJugar.obtenerBoton(), 0, 0);
    grid->addWidget(btnInstruciones.obtenerBoton(), 0, 1);
    grid->addWidget(btnRanking.obtenerBoton(), 1, 0);
    grid->addWidget(btnSalir.obtenerBoton(), 1, 1);

    // Conectar boton salir
    QObject::connect(
        btnSalir.obtenerBoton(),
        &QPushButton::clicked,
        &ventana,
        &QWidget::close
        );

    // Agregar secciones al layout principal
    principal->addWidget(placeholder, 1);
    principal->addLayout(grid);

    // Espaciado entre botones
    grid->setSpacing(12);

    ventana.show();

    return app.exec();
}
