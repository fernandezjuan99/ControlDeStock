#include "producto.h"
#include "nuevo.h"
#include "main_window.h"
#include "stock.h"
#include "borrarstock.h"
#include "borrarproducto.h"


ventana_principal::ventana_principal(QWidget *parent) : QWidget(parent){

        // Configura la tamaño de la ventana
        setGeometry(500 , 250 , 675 , 475);
        setFixedSize( 675 , 475);
        setWindowTitle("Control de Stock");

        nuevo = NULL;
        producto = NULL;
        deleteproducto = NULL;
        addstock = NULL;
        deletestock = NULL;

        // Botón Nuevo
        button1 = new QPushButton("Nuevo",this);
        button1->setGeometry(30, 50, 60 , 25 );
        connect(button1 ,SIGNAL(clicked()),this, SLOT(mostrarNuevo()));

        // Botón Abrir
        button2 = new QPushButton("Abrir",this);
        button2->setGeometry(100, 50, 60 , 25 );
        connect(button2 ,SIGNAL(clicked()),this, SLOT(Abrir()));

        // Botón Guardar
        button3 = new QPushButton("Guardar",this);
        button3->setGeometry(170, 50, 60 , 25 );
        connect(button3, SIGNAL(clicked()),this, SLOT(Guardar()));

        //Botón Producto +
        button4 = new QPushButton("+",this);
        button4->setGeometry(240, 50, 25, 25 );
        connect(button4 ,SIGNAL(clicked()),this, SLOT(mostrarProducto()));

        // Botón Producto -
        button5 = new QPushButton("-",this);
        button5->setGeometry(267, 50, 25 , 25 );
        connect(button5 ,SIGNAL(clicked()),this, SLOT(mostrardeleteProducto()));

        // Botón Stock +
        button6 = new QPushButton("+",this);
        button6->setGeometry(302, 50, 25 , 25 );
        connect(button6 ,SIGNAL(clicked()),this, SLOT(mostrarAddStock()));

        // Botón Stock -
        button7 = new QPushButton("-",this);
        button7->setGeometry(329, 50, 25 , 25 );
        connect(button7 ,SIGNAL(clicked()),this, SLOT(mostrardeleteStock()));

        // Botón Buscar
        button8 = new QPushButton("Buscar",this);
        button8->setGeometry(466, 50, 60 , 25 );
        connect(button8 ,SIGNAL(clicked()),this, SLOT(Buscar()));

        // Botón de Refrescar
        button9 = new QPushButton("R",this);
        button9->setGeometry(536, 50, 25 , 25 );
        connect(button9 ,SIGNAL(clicked()),this, SLOT(refrescar()));

        // Cuadro de Búsqueda
        text = new QLineEdit(this);
        text->setGeometry(364, 51, 100 , 23);

        // Label Producto
        LBLPRODUCTO = new QLabel("Producto",this);
        LBLPRODUCTO->setGeometry(244, 33, 100 , 23);

        // Label Stock
        LBLSTOCK = new QLabel("Stock",this);
        LBLSTOCK->setGeometry(314, 33, 100 , 23);

        // Tabla
        Tabla = new QTableWidget(this);
        Tabla->setGeometry(30, 120, 600 , 300);
        Tabla->setColumnCount(4);
        Tabla->setRowCount(10);
        Tabla->setColumnWidth(0,150);
        Tabla->setColumnWidth(1,235);
        Tabla->setColumnWidth(2,125);
        Tabla->setColumnWidth(3,73);
}


void ventana_principal::mostrarNuevo()           //Muestra la ventana Nuevo
{
    if(!nuevo)
    {
        nuevo = new Nuevo();
        nuevo->setVP(this);
    }

    nuevo->show();
}

void ventana_principal::mostrarProducto()       // Muestra la ventana Producto +
{
    if(!producto)
    {
        producto = new Producto();
        producto->setVP(this);
    }

    producto->show();
}

void ventana_principal::mostrardeleteProducto() // Muestra la ventana Producto -
{
    if(!deleteproducto)
    {
        deleteproducto = new deleteProducto();
        deleteproducto->setVP(this);
    }

    deleteproducto->show();
}

void ventana_principal::mostrarAddStock()       // Muestra la ventana Stock +
{
    if(!addstock)
    {
        addstock = new AddStock();
        addstock->setVP(this);
    }

    addstock->show();
}

void ventana_principal::mostrardeleteStock()    // Muestra la ventana Stock -
{
    if(!deletestock)
    {
        deletestock = new deleteStock();
        deletestock->setVP(this);
    }

    deletestock->show();
}


void ventana_principal::actualizarTabla(){    // Vuelve a leer el archivo "temp"

    FILE *FP;
    int cant_filas = 0;  /*!< Almacena la cantidad de registros para asignar a la tabla esa cantidad de filas */
    int i = 0;           /*!< Se incrementa a medida que leo cada registro para moverme por cada fila de la tabla */
    struct STOCK X;

    if((FP = fopen("temp","rb")) == NULL){              //  Abro "temp" en modo lectura y cuento la cantidad
		printf("ERROR");                                //  de Registros y lo guardo en cant_filas
		return;
    }
    fseek(FP , 0 , 2);
    cant_filas = ftell(FP)/sizeof(X);

                                                        // Configuracion de la Tabla

    QStringList horzHeader;
    horzHeader << "Codigo" << "Producto" << "Cantidad" << "Estado";
    Tabla->setHorizontalHeaderLabels(horzHeader);
    Tabla->setColumnCount(4);
    Tabla->setRowCount(cant_filas);
    Tabla->setColumnWidth(0,150);
    Tabla->setColumnWidth(1,235);
    Tabla->setColumnWidth(2,125);
    Tabla->setColumnWidth(3,73);

    // Coloco los registros en la tabla

    fseek(FP , 0 , 0);
    fread(&X,sizeof(X),1,FP);
    while(!feof(FP)){

        Tabla->setItem(i, 0, new QTableWidgetItem(X.CODIGO));           /** Leo cada registro y lo coloco en la fila i. */
        Tabla->setItem(i, 1, new QTableWidgetItem(X.PRODUCTO));
        Tabla->setItem(i, 2, new QTableWidgetItem(QString::number(X.CANTIDAD)));
        Tabla->setItem(i, 3, new QTableWidgetItem);

        /// Colores de Estado.
        /** Dependiendo la cantidad de stock asigno un determinado color. */


        if(X.CANTIDAD >= 20){           /**Cantidad de Stock mayor a 20 -> Color Verde */

        Tabla->item(i, 3)->setBackground(Qt::green);

        }
        if(X.CANTIDAD < 20 && X.CANTIDAD >= 10){ /**Cantidad de Stock entre 19 y 10 -> Color Amarillo */

             Tabla->item(i, 3)->setBackground(Qt::yellow);

        }

        if(X.CANTIDAD>0 && X.CANTIDAD < 10){ /**Cantidad de Stock entre 10 y 1 */

             Tabla->item(i, 3)->setBackground(Qt::red);

        }

        if(!X.CANTIDAD){ /**Cantidad de Stock vacio -> Color Negro */

             Tabla->item(i, 3)->setBackground(Qt::black);

        }

        i++;
        fread(&X,sizeof(X),1,FP);
    }

    fclose(FP);

}


void ventana_principal::Buscar(){

     struct STOCK X;
     int i=0;    /** Se incrementa a medida que leo cada registro para moverme por cada fila de la tabla */
     int cont=0; /** Cuenta las veces que se repite el Código de un Registro y lo guarda en cont para setear esa cant. de filas de la Tabla */


     FILE *FP;

    if((FP = fopen("temp","rb")) == NULL){
            return;
    }

    // Recibe los datos de los labels
    QString temp = text->text();
    QByteArray ba = temp.toLatin1();

    // Cuenta la cantidad de veces que se repite el codigo

    fread(&X,sizeof(X),1,FP);

    while(!feof(FP)){

        if(!strcmp(X.CODIGO,ba.data())){ // Si Codigo es igual a lo que recibo del label incremento cont

            cont++;

        }

        fread(&X,sizeof(X),1,FP);

    }


    fseek(FP,0,0);

    Tabla->setRowCount(cont);

    fread(&X,sizeof(X),1,FP);
    while(!feof(FP)){                       // Recorro los registros y cuando es igual a lo que recibo del label lo coloco
                                            // en la tabla
        if(!strcmp(X.CODIGO,ba.data())){

                Tabla->setItem(i, 0, new QTableWidgetItem(X.CODIGO));
                Tabla->setItem(i, 1, new QTableWidgetItem(X.PRODUCTO));
                Tabla->setItem(i, 2, new QTableWidgetItem(QString::number(X.CANTIDAD)));
                Tabla->setItem(i, 3, new QTableWidgetItem);

                if(X.CANTIDAD >= 20){                                    // Comentado en la función
                                                                         //ventana_principal::actualizarTabla()
                    Tabla->item(i, 3)->setBackground(Qt::green);

                    }

                if(X.CANTIDAD < 20 && X.CANTIDAD >= 10){

                    Tabla->item(i, 3)->setBackground(Qt::yellow);

                    }

                if(X.CANTIDAD>0 && X.CANTIDAD < 10){

                    Tabla->item(i, 3)->setBackground(Qt::red);

                    }

                if(!X.CANTIDAD){

                    Tabla->item(i, 3)->setBackground(Qt::black);

                    }

                i++;

        }
        fread(&X,sizeof(X),1,FP);
    }

}

void ventana_principal::Abrir(){    // Abro un archivo existente
    struct STOCK X;
    QString fileName = QFileDialog::getOpenFileName(this,"Abrir archivo","C://"); /*!<Recibo la direccion del archivo */
    QByteArray ba = fileName.toLatin1(); /*!< Convierte filename en un char */
    //printf("\na%s", ba.data());

    if(!strcmp("",ba.data())){  // Cuando toco el boton "Cancelar" o "x" no recibo ningun string entonces salgo de la funcion
        return;
    }

    FILE *FP,*FC;



    if((FP = fopen(ba.data(),"rb")) == NULL){
		printf("ERROR");
        }


    if((FC = fopen("temp","wb")) == NULL){
		printf("ERROR");
        }

    // Copia el archivo a temp
    // Trabajo desde temp para no modificar el archivo original en caso de que me arrepienta de modificarlo

    fread(&X,sizeof(X),1,FP);
        while(!feof(FP)){
            printf("\n %s %s %d",X.CODIGO,X.PRODUCTO,X.CANTIDAD);
            fwrite(&X,sizeof(X),1,FC);
            fread(&X,sizeof(X),1,FP);
    }

    fclose(FP);
    fclose(FC);
    actualizarTabla();
}

void ventana_principal::Guardar(){ // Guardo el proyecto
    struct STOCK X;
    QString fileName = QFileDialog::getSaveFileName(this,"Guardar archivo","C://"); /*!<Recibo la direccion del archivo */
    QByteArray ba = fileName.toLatin1();                                            /*!< Convierte filename en un char* */

    if(!strcmp("",ba.data())){  // Cuando toco el boton "Cancelar" o "x" no recibo ningun string entonces salgo de la funcion
        return;
    }


    FILE *FP,*FC;

    if((FP = fopen("temp","rb")) == NULL){
		printf("ERROR");
        }

    if((FC = fopen(ba.data(),"wb")) == NULL){
		printf("ERROR");
        }

    //Transcribo temp al archivo que voy a guardar

    fread(&X,sizeof(X),1,FP);

    while(!feof(FP)){
        printf("\n %s %s %d",X.CODIGO,X.PRODUCTO,X.CANTIDAD);
        fwrite(&X,sizeof(X),1,FC);
        fread(&X,sizeof(X),1,FP);
    }

    fclose(FP);
    fclose(FC);
}

void ventana_principal::refrescar(){

        //Cuando toco el botón "R" vuelvo a leer "temp"

        actualizarTabla();
}


