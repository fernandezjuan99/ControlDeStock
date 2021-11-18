#pragma once
#include <QtGui>
#include "main_window.h"


class ventana_principal;
struct stock;

class Producto : public QWidget {

    Q_OBJECT

private:

    QPushButton * button;  // Ingresar
    QPushButton * button2;
    QLineEdit *CODIGO;      //Campo de Ingreso de Código
    QLineEdit *PRODUCTO;    //Campo de Ingreso de Producto
    QLineEdit *CANTIDAD;    //Campo de Ingreso de Cantidad

    QLabel *LBLCODIGO;      //Label Código
    QLabel *LBLPRODUCTO;    //Label Producto
    QLabel *LBLCANTIDAD;    //Label Cantidad
    QMessageBox *error;
    ventana_principal *vp;

public:

    Producto(QWidget * parent = 0);
    void setVP(ventana_principal *);

public slots:

    void Salir();              // Cierra la Ventana
    void AgregarProducto();    // Agrega un Registro al archivo "temp"
    void Chequeo();            // Se fija si hay informacion en los campos de ingreso de datos
};

