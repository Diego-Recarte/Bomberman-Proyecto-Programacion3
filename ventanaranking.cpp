#include "ventanaranking.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>

#include "sistemausuarios.h"
#include "listausuarios.h"

VentanaRanking::VentanaRanking(SistemaUsuarios& sistema,QWidget* padre): QWidget(padre),sistemaUsuarios(sistema){
    setObjectName("pantallaRanking");

    setStyleSheet(
        "QWidget#pantallaRanking {"
        "    background-color: #1b2631;"
        "}"

        "QLabel {"
        "    color: white;"
        "}"

        "QTableWidget {"
        "    background-color: #2c3e50;"
        "    color: white;"
        "    gridline-color: #4a6274;"
        "    border: 2px solid #4a6274;"
        "    border-radius: 8px;"
        "}"

        "QHeaderView::section {"
        "    background-color: #34495e;"
        "    color: white;"
        "    border: none;"
        "    padding: 8px;"
        "    font-weight: bold;"
        "}"
        );

    QVBoxLayout* principal = new QVBoxLayout(this);
    principal->setContentsMargins(30, 20, 30, 20);
    principal->setSpacing(20);

    QLabel* titulo = new QLabel("Ranking de jugadores", this);
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("font-size: 32px; font-weight: bold;");

    etiquetaPrimero = new QLabel(this);
    etiquetaPrimero->setAlignment(Qt::AlignCenter);
    etiquetaPrimero->setStyleSheet(
        "font-size: 28px;"
        "font-weight: bold;"
        "color: #f1c40f;"
        "background-color: rgba(241, 196, 15, 0.15);"
        "border: 3px solid #f1c40f;"
        "border-radius: 15px;"
        "padding: 25px;"
        );

    tablaRanking = new QTableWidget(this);
    tablaRanking->setColumnCount(5);
    tablaRanking->setHorizontalHeaderLabels({"Posición", "Nombre", "Nivel", "Trofeos", "Puntaje"});

    tablaRanking->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tablaRanking->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tablaRanking->setSelectionBehavior(QAbstractItemView::SelectRows);
    tablaRanking->verticalHeader()->setVisible(false);

    QPushButton* btnVolver = new QPushButton("Volver", this);
    btnVolver->setFixedWidth(180);

    connect( btnVolver, &QPushButton::clicked, this, &VentanaRanking::volverSolicitado );

    principal->addWidget(titulo);
    principal->addWidget(etiquetaPrimero);
    principal->addWidget(tablaRanking, 1);
    principal->addWidget(btnVolver, 0, Qt::AlignHCenter);

    actualizarRanking();
}

void VentanaRanking::actualizarRanking()
{
    sistemaUsuarios.obtenerListas().ordenarPorPuntaje();

    const int cantidad = sistemaUsuarios.obtenerListas().obtenerCantidad();

    if (cantidad == 0) {
        etiquetaPrimero->setText("Todavía no hay jugadores registrados");
        tablaRanking->setRowCount(0);
        return;
    }

     NodoUsuario* primero = sistemaUsuarios.obtenerListas().obtenerPorIndice(0);

    etiquetaPrimero->setText( QString("1er lugar\n%1\nPuntaje: %2").arg(QString::fromStdString(primero->usuario.obtenerNombre())).arg(primero->usuario.obtenerPuntaje()));

    const int filas = cantidad - 1;

    tablaRanking->setRowCount(filas);

    for (int indice = 1; indice < cantidad; ++indice) {
        NodoUsuario* usuario =sistemaUsuarios.obtenerListas().obtenerPorIndice(indice);

        const int fila = indice - 1;

        tablaRanking->setItem(fila,0,new QTableWidgetItem(QString::number(indice + 1)));

        tablaRanking->setItem( fila, 1, new QTableWidgetItem( QString::fromStdString(usuario->usuario.obtenerNombre() ) ));

        tablaRanking->setItem(fila, 2,new QTableWidgetItem(QString::number(usuario->usuario.obtenerNivel())));

        tablaRanking->setItem( fila, 3,new QTableWidgetItem(QString::number(usuario->usuario.obtenerTrofeos()) ));

        tablaRanking->setItem(fila, 4,new QTableWidgetItem(QString::number(usuario->usuario.obtenerPuntaje()) ));
    }
}