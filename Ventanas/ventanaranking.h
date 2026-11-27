#ifndef VENTANARANKING_H
#define VENTANARANKING_H

#include <QWidget>

class QLabel;
class QTableWidget;
class SistemaUsuarios;

class VentanaRanking : public QWidget{
    Q_OBJECT

public:
    explicit VentanaRanking(SistemaUsuarios& sistema, QWidget* padre = nullptr);

    void actualizarRanking();

signals:
    void volverSolicitado();

private:
    SistemaUsuarios& sistemaUsuarios;

    QLabel* etiquetaPrimero = nullptr;
    QTableWidget* tablaRanking = nullptr;
};

#endif