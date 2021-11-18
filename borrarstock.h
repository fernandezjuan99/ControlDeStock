#pragma once
#include <QtGui>
#include "main_window.h"


class ventana_principal;
struct stock;

class deleteStock : public QWidget {

    Q_OBJECT

private:
    QPushButton * button;   //Listo
    QPushButton * button2;  //Salir
    QLineEdit *CODIGO;      //Campo de ingreso Código
    QLineEdit *CANTIDAD;    //Campo de ingreso Cantidad

    QLabel *LBLCODIGO;      //Label Código
    QLabel *LBLCANTIDAD;    //Label Cantidad

    QMessageBox *error;
    ventana_principal *vp;

public:

    deleteStock(QWidget * parent = 0);
    void setVP(ventana_principal *);

public slots:
    void BorrarStock();    // Descuenta Stock a un producto
    void Salir();          // Cierra la ventana
};

