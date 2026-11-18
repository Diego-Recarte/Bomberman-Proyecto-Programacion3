#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

#include "Boton.h"
#include "ventanajuego.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    QWidget ventana;
    ventana.setWindowTitle("Menu principal");
    ventana.resize(700, 600);



    QVBoxLayout *principal = new QVBoxLayout(&ventana);


    QLabel *placeholder = new QLabel("Area de contenido", &ventana   );

    placeholder->setAlignment(Qt::AlignCenter);
    placeholder->setMinimumHeight(180);

    placeholder->setStyleSheet( "background-color: #eeeeee;" "border: 2px solid #aaaaaa;" "font-size: 20px;");


    QGridLayout *grid = new QGridLayout();


    Boton btnJugar(&ventana, "Jugar", 250, 70, "#27ae60");
    Boton btnInstruciones(&ventana, "Instrucciones", 250, 70, "#2980b9");
    Boton btnRanking(&ventana, "Ranking", 250, 70, "#8e44ad");
    Boton btnSalir(&ventana, "Salir", 250, 70, "#c0392b");


    grid->addWidget(btnJugar.obtenerBoton(), 0, 0);
    grid->addWidget(btnInstruciones.obtenerBoton(), 0, 1);
    grid->addWidget(btnRanking.obtenerBoton(), 1, 0);
    grid->addWidget(btnSalir.obtenerBoton(), 1, 1);


    VentanaJuego *juego = nullptr;

    QObject::connect(
        btnJugar.obtenerBoton(),
        &QPushButton::clicked,
        &ventana,
        [&]() {
            if (!juego) {
                juego = new VentanaJuego();
            }

            juego->show();
            juego->raise();
            juego->activateWindow();
        }
        );

    QObject::connect(  btnSalir.obtenerBoton(),   &QPushButton::clicked,  &ventana,   &QWidget::close );


    principal->addWidget(placeholder, 1);
    principal->addLayout(grid);

    grid->setSpacing(12);

    ventana.show();

    return app.exec();
}
