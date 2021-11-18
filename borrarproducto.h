#pragma once
#include <QtGui>
#include "main_window.h"


class ventana_principal;
struct stock;

class deleteProducto : public QWidget {

    Q_OBJECT

private:
    QPushButton * button;  // Eliminar
    QPushButton * button2; // Cerrar
    QLineEdit *CODIGO;     //Cuadro de Ingreso de Codigo
    QLabel *LBLCODIGO;     //Label Código

    QMessageBox *error;    //Warning
    ventana_principal *vp;

public:

    deleteProducto(QWidget * parent = 0);
    void setVP(ventana_principal *);

public slots:
    void Salir();               // Cierra la ventana
    void eliminarProducto();    // Elimina un registro depurando "temp"
};


