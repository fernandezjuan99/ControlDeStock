#pragma once
#include <QtGui>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


class Nuevo;
class Producto;
class AddStock;
class deleteProducto;
class deleteStock;

struct STOCK{
    char CODIGO[20];
    char PRODUCTO[20];
    int CANTIDAD;
};

class ventana_principal : public QWidget{

    Q_OBJECT

private:
    QPushButton * button1;  // Nueva Tabla
    QPushButton * button2;  // Abrir
    QPushButton * button3;  // Guardar
    QPushButton * button4;  // + Producto
    QPushButton * button5;  // - Producto
    QPushButton * button6;  // + Stock
    QPushButton * button7;  // - Stock
    QPushButton * button8;  // Buscar
    QPushButton * button9;  // Refrescar

    QLabel *LBLPRODUCTO;    //Label Producto
    QLabel *LBLSTOCK;       //Label Stock

    QLineEdit *text;        //Cuadro de Busqueda
    QTableWidget *Tabla;    //Tabla

    Nuevo *nuevo;

    Producto *producto;
    deleteProducto *deleteproducto;

    AddStock *addstock;
    deleteStock *deletestock;

public:
    ventana_principal(QWidget * parent = 0);
    void actualizarTabla();         // Lee el archivo "temp" y lo muestra en la Tabla

public slots:

    void mostrarNuevo();            //Muestra la ventana Nuevo

    void Abrir();                   //Abre un Archivo existente
    void Guardar();                 //Guarda un Archivo existente

    void mostrarProducto();         // Muestra la ventana Producto +
    void mostrardeleteProducto();   // Muestra la ventana Producto -

    void mostrarAddStock();         // Muestra la ventana Stock +
    void mostrardeleteStock();      // Muestra la ventana Stock -


    void Buscar();                  // Filtra la Tabla
    void refrescar();               // Refresca la Tabla

};

