#include "nuevo.h"
#include "main_window.h"
#include "producto.h"



 static int i = 1; /*
                    * Cuando pulso el botón "Ingresar" se tiene que abrir un flujo al archivo "temp".
                    * Si este no existe, cuando lo leo en modo r+b sale error,
                    * Si existe y lo leo en w+b me lo va a borrar cada vez que toco el boton "Ingresar".
                    * Entonces cuando este en 1 se pone en modo w+b y cuando este en 0 se pone en r+b
                    */

Nuevo::Nuevo(QWidget *parent) : QWidget(parent){
        setGeometry(750 , 100 , 225 , 200);
        setFixedSize( 225 , 200);
        setWindowTitle("Nueva Tabla");


        // Botón Ingresar
        button1 = new QPushButton("Ingresar",this);
        button1->setGeometry(50, 150, 65 , 25 );
        button1->setEnabled(false);
        connect(button1 ,SIGNAL(clicked()),this, SLOT(NuevaTabla()));

        // Botón Finalizar
        button2 = new QPushButton("Finalizar",this);
        button2->setGeometry(120, 150, 65 , 25);
        connect(button2 ,SIGNAL(clicked()),this, SLOT(Fin()));


        // Labels de los campos de datos
        LBLCODIGO = new QLabel("Codigo:",this);
        LBLCODIGO->setGeometry(20, 20, 100 , 23);
        LBLPRODUCTO = new QLabel("Producto:",this);
        LBLPRODUCTO->setGeometry(20, 60, 100 , 23);
        LBLCANTIDAD= new QLabel("Cantidad:",this);
        LBLCANTIDAD->setGeometry(20, 100, 100 , 23);


        // Campos de Ingreso de Datos
        CODIGO = new QLineEdit(this);
        CODIGO->setGeometry(100, 20, 100 , 23);
        PRODUCTO = new QLineEdit(this);
        PRODUCTO->setGeometry(100, 60, 100 , 23);
        CANTIDAD= new QLineEdit(this);
        CANTIDAD->setGeometry(100, 100, 100 , 23);

        connect(CODIGO,SIGNAL(textChanged(const QString)),this,SLOT(Chequeo()));
        connect(PRODUCTO,SIGNAL(textChanged(const QString)),this,SLOT(Chequeo()));
        connect(CANTIDAD,SIGNAL(textChanged(const QString)),this,SLOT(Chequeo()));
}

void Nuevo::setVP(ventana_principal * v){  // Guarda la dirección de la ventana principal
        vp = v;
}


void Nuevo::NuevaTabla(){ // Agrega un registro

	struct STOCK X;
    FILE *FP;

    //printf("\ni value %d",i);

    if(i){

        if((FP = fopen("temp","w+b")) == NULL){
		  printf("ERROR");
		  exit(1);
        }

        i=0;

        }

        else

        {

        if((FP = fopen("temp","r+b")) == NULL){

		  printf("ERROR");
		  exit(1);
             }

        }

    //Recibe los datos de los labels
    QString temp = CODIGO->text();
    QByteArray ba = temp.toLatin1();
    strcpy(X.CODIGO,ba.data());

    temp = PRODUCTO->text();
    ba = temp.toLatin1();
    strcpy(X.PRODUCTO,ba.data());

    temp = CANTIDAD->text();
    X.CANTIDAD = temp.toInt();

    // Me muevo hasta el final de "temp" y agrego el registro
    fseek(FP,long (0)*sizeof(X),2);
    fwrite(&X,sizeof(X),1,FP);

    fclose(FP);

    // Recorro "temp" y lo muestro en la tabla
    vp->actualizarTabla();

    CODIGO->clear();
    PRODUCTO->clear();
    CANTIDAD->clear();
}

void Nuevo::Chequeo(){ // Verifica si hay texto en los campos de ingreso de datos y desbloquea el boton Ingresar

    if(CODIGO->text().length() > 0 && PRODUCTO->text().length() > 0 && CANTIDAD->text().length() > 0)
    {
        button1->setEnabled(true);
    }

    if(CODIGO->text().length() == 0 && PRODUCTO->text().length() == 0 && CANTIDAD->text().length() == 0)
    {
        button1->setEnabled(false);
    }

}

void Nuevo::Fin(){ // Iguala i a 1, cierra la ventana "Nuevo", recorro "temp" y lo muestro en la tabla
    i = 1;
    hide();
    vp->actualizarTabla();
}



