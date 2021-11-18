#include "main_window.h"
#include "borrarproducto.h"

deleteProducto::deleteProducto(QWidget *parent) : QWidget(parent){

        setGeometry(750 , 100 , 225 , 200);
        setFixedSize( 225 , 200);
        setWindowTitle("Eliminar Producto");

        // Botón Eliminar
        button = new QPushButton("Eliminar",this);
        button->setGeometry(50, 150, 65 , 25 );
        button->setEnabled(true);
        connect(button ,SIGNAL(clicked()),this, SLOT(eliminarProducto()));
        // Botón Cerrar
        button2 = new QPushButton("Cerrar",this);
        button2->setGeometry(120, 150, 65 , 25);
        connect(button2 ,SIGNAL(clicked()),this, SLOT(Salir()));

        // Label de Campo Código
        LBLCODIGO = new QLabel("Codigo:",this);
        LBLCODIGO->setGeometry(20, 20, 100 , 23);

        // Campo de Ingreso de Datos
        CODIGO = new QLineEdit(this);
        CODIGO->setGeometry(100, 20, 100 , 23);

}

void deleteProducto::setVP(ventana_principal * v){  // Guarda la dirección de la ventana principal
        vp = v;
}


void deleteProducto::eliminarProducto(){
            struct STOCK X;
            FILE *FP,*FC;
            int i = 0;

                QString temp = CODIGO->text();      //Obtengo el Código del produto y lo convierto en Char
                QByteArray ba = temp.toLatin1();

                if((FP = fopen("temp","rb")) == NULL){
                        QMessageBox messageBox;
                        messageBox.critical(0,"Error","No hay abierto ningun archivo");
                        messageBox.setFixedSize(500,200);
                        return;
                }

                if((FC = fopen("temp2","wb")) == NULL){
                    printf("ERROR");
                    exit(1);
                    return;
                }


                // Depuro el archivo "temp" y creando un archivo "temp2"

                fread(&X,sizeof(X),1,FP);

                while(!feof(FP)){

                        if((!strcmp(X.CODIGO,ba.data())) && i==0 ){    // Si el Código que ingrese es igual al que lei de "temp"
                                                                       // e i es igual a 0 no lo paso a "temp2".
                            i = 1;                                     // Igualo i a 1 para solo borrarlo una vez.
                        }
                        else
                        {
                            fwrite(&X,sizeof(X),1,FC);
                        }
                            fread(&X,sizeof(X),1,FP);
                        }

                    if(i == 0){                                        // Si i es igual a 0, nunca se encontro el Código
                                                                       // que ingrese para eliminar.
                        // Mensaje de Error
                        QMessageBox messageBox;
                        messageBox.critical(0,"Error","No se encontro el código");
                        messageBox.setFixedSize(500,200);
                    }

                    fclose(FP);
                    fclose(FC);


                    if( remove( "temp" ) != 0 ){             //Borro "temp"
                        printf( "\nError!" );
                    }
                    else
                    {
                        printf( "Funciono!" );
                    }

                    if( rename("temp2","temp") != 0 ){       // Cambio el nombre de "temp2" a "temp"
                        printf( "\nError!" );
                    }
                    else
                    {
                        printf( "Funciono!" );
                    }

                    CODIGO->clear();

                    //Recorro "temp" y lo muestro en la tabla
                    vp->actualizarTabla();
}

void deleteProducto::Salir(){     // Cierro la ventana Producto -
        hide();
}

