#include "producto.h"
#include "main_window.h"


Producto::Producto(QWidget *parent) : QWidget(parent){
        setGeometry(750 , 100 , 225 , 200);
        setFixedSize( 225 , 200);
        setWindowTitle("Agregar Producto");

        // Botón Ingresar
        button = new QPushButton("Ingresar",this);
        button->setGeometry(50, 150, 65 , 25 );
        button->setEnabled(false);
        connect(button ,SIGNAL(clicked()),this, SLOT(AgregarProducto()));

        // Botón Cerrar
        button2 = new QPushButton("Cerrar",this);
        button2->setGeometry(120, 150, 65 , 25);
        connect(button2 ,SIGNAL(clicked()),this, SLOT(Salir()));

        // Labels Campos de Datos
        LBLCODIGO = new QLabel("Codigo:",this);
        LBLCODIGO->setGeometry(20, 20, 100 , 23);
        LBLPRODUCTO = new QLabel("Producto:",this);
        LBLPRODUCTO->setGeometry(20, 60, 100 , 23);
        LBLCANTIDAD= new QLabel("Cantidad:",this);
        LBLCANTIDAD->setGeometry(20, 100, 100 , 23);


        // Campos Ingreso de Datos
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

void Producto::setVP(ventana_principal * v){ // Guarda la dirección de la ventana principal
        vp = v;
}

void Producto::Chequeo(){ // Verifica si hay texto en los campos de ingreso de datos y desbloquea el boton Ingresar

    if(CODIGO->text().length() > 0 && PRODUCTO->text().length() > 0 && CANTIDAD->text().length() > 0)
    {
        button->setEnabled(true);
    }

    if(CODIGO->text().length() == 0 && PRODUCTO->text().length() == 0 && CANTIDAD->text().length() == 0)
    {
        button->setEnabled(false);
    }

}

void Producto::AgregarProducto(){ // Agrega producto a "temp"

    struct STOCK X;
    FILE *FP;

    if((FP = fopen("temp","r+b")) == NULL){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","No hay abierto ningun archivo");
        messageBox.setFixedSize(500,200);
        return;
        }

    //Recibo los datos ingresados
    QString temp = CODIGO->text();
    QByteArray ba = temp.toLatin1();
    strcpy(X.CODIGO,ba.data());

    temp = PRODUCTO->text();
    ba = temp.toLatin1();
    strcpy(X.PRODUCTO,ba.data());

    temp = CANTIDAD->text();
    X.CANTIDAD = temp.toInt();

    // Agrego el nuevo registro al final de "temp"
    fseek(FP,long (0)*sizeof(X),2);
    fwrite(&X,sizeof(X),1,FP);

    fclose(FP);

    CODIGO->clear();
    PRODUCTO->clear();
    CANTIDAD->clear();

    vp->actualizarTabla();  // Recorro "temp" y lo muestro en la Tabla
}


void Producto::Salir(){ //Cierra la ventana

    CODIGO->clear();
    PRODUCTO->clear();
    CANTIDAD->clear();

    hide();
}
