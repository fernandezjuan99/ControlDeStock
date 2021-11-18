/*
 *
 * Proyecto Control de Stock
 *
 * Informatica II
 *
 * Alumno: Fernández Juan Ignacio
 *
 * Descripción: El programa consiste en un registro de entrada y salida de
 * productos.
 *
 * En la ventana principal se encuentran los sig. botones:
 *
 * Nuevo: Crea un nuevo archivo.
 * Abrir: Abre un archivo existente.
 * Guardar: Guarda el proyecto en curso.
 * Producto +: Agrega un producto a la tabla.
 * Producto -: Quita un producto de la tabla.
 * Stock +: Incrementa la cantidad de Stock de cierto producto.
 * Stock -: Disminuye la cantidad de Stock de cierto producto.
 * Buscar: Filtra la tabla dependiendo el Código ingresado.
 * A: Refresca la tabla.
 *
 */

#include <QApplication>
#include "main_window.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    ventana_principal *vp = new ventana_principal();

    vp->show();

    app.exec();

    remove("temp"); //Borra el archivo temp.
}
