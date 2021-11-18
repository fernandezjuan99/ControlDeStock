#pragma once
#include <QtGui>
#include "main_window.h"
#include "producto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct STOCK;

class ventana_principal;

class Nuevo : public QWidget {

    Q_OBJECT

private:
    QPushButton * button1;  // Ingresar
    QPushButton * button2;  // Finalizar

    QLineEdit *CODIGO;      //Cuadro de ingreso de Código
    QLineEdit *PRODUCTO;    //Cuadro de ingreso de Producto
    QLineEdit *CANTIDAD;    //Cuadro de ingreso de Cantidad

    QLabel *LBLCODIGO;      //Label Código
    QLabel *LBLPRODUCTO;    //Label Producto
    QLabel *LBLCANTIDAD;    //Label Cantidad

    ventana_principal *vp;

public:
    Nuevo(QWidget * parent = 0);
    void setVP(ventana_principal *);

public slots:
    void NuevaTabla();
    void Chequeo();
    void Fin();
};


