#include "main_window.h"
#include "borrarstock.h"

deleteStock::deleteStock(QWidget *parent) : QWidget(parent){
        setGeometry(750 , 100 , 225 , 200);
        setFixedSize( 225 , 200);
        setWindowTitle("Quitar Stock");

        // Botón Ingresar
        button = new QPushButton("Ingresar",this);
        button->setGeometry(50, 150, 65 , 25 );
        connect(button ,SIGNAL(clicked()),this, SLOT(BorrarStock()));

        // Botón Cerrar
        button2 = new QPushButton("Cerrar",this);
        button2->setGeometry(120, 150, 65 , 25);
        connect(button2 ,SIGNAL(clicked()),this, SLOT(Salir()));

        // Label de los Campos de Datos
        LBLCODIGO = new QLabel("Codigo:",this);
        LBLCODIGO->setGeometry(20, 20, 100 , 23);
        LBLCANTIDAD = new QLabel("Cantidad:",this);
        LBLCANTIDAD->setGeometry(20, 60, 100 , 23);

        //Campos de Ingreso de Datos
        CODIGO = new QLineEdit(this);
        CODIGO->setGeometry(100, 20, 100 , 23);
        CANTIDAD = new QLineEdit(this);
        CANTIDAD->setGeometry(100, 60, 100 , 23);

}

void deleteStock::setVP(ventana_principal * v){ // Guarda la dirección de la ventana principal
        vp = v;
}

void deleteStock::BorrarStock(){                // Descuenta la cant. de Stock a un producto

    struct STOCK X,Y;
    FILE *FP;

    if((FP = fopen("temp","r+b")) == NULL){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","No hay abierto ningun archivo");
        messageBox.setFixedSize(500,200);
        return;
        }

    QString temp = CODIGO->text();  //Obtengo el Código del produto y lo convierto en Char
    QByteArray ba = temp.toLatin1();
    strcpy(X.CODIGO,ba.data());     //Lo guardo en la struct STOCK X

    temp = CANTIDAD->text();        //Obtengo la cant. de Stock a agregar y lo convierto en int
    X.CANTIDAD = temp.toInt();      //Lo guardo en la struct STOCK X



    //Busco el registro dependiendo el Código y modifico su Stock

    fread(&Y,sizeof(Y),1,FP);

        while(!feof(FP)){

                    if(!strcmp(X.CODIGO,Y.CODIGO)){     // Recorro "temp" hasta encontrar mi X.CODIGO

                                fseek(FP,long (-1)*sizeof(X),1);                // Muevo al ventana de FP 1 lugar hacia atras desde donde estoy.

                                strcpy(X.PRODUCTO,Y.PRODUCTO);                  // A produto X le copio la descripción de producto Y.

                                X.CANTIDAD = Y.CANTIDAD - X.CANTIDAD;           // A la cantidad de Stock que decrementar le resto la cantidad del Stock de X

                                fwrite(&X,sizeof(X),1,FP);                      // Modifico el registro
                                fclose(FP);

                                CODIGO->clear();
                                CANTIDAD->clear();
                                hide();                                         // Cierro la ventana de Stock -

                                vp->actualizarTabla();                          // Recorro "temp" y lo muestro en la Tabla

                                return;                                         // Salgo de la función
        }
        fread(&Y,sizeof(Y),1,FP);
    }
    fclose(FP);



    // Si sali del while fue porque no se encontro el Código.

    QMessageBox messageBox;
    messageBox.critical(0,"Error","No se encontro el Codigo");
    messageBox.setFixedSize(500,200);

}


void deleteStock::Salir(){ // Cierro la ventana Stock -
    hide();
    CODIGO->clear();
    CANTIDAD->clear();
}

