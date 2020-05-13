#include <iostream>
#include <vector>
#include <map>
#include <fstream>
using namespace std;


template <class T>
bool evaluacion_de_indices(T inventario, unsigned short int indice){

    ///Ésta función recible cualquier mapa o vector y un valor a evaluar dentro de las claves de este   ///
    ///Si el valor a evaluar se encuentra en el mapa o vector retorna true sino false                   ///

    for (auto id = begin(inventario); id != end(inventario); id++){ //Se itera sobre las claves del mapa, en éste caso son ints
        if(id->first == indice)
            return true;                                            //Se retorna true si el valor a evaluar se encuentra dentro de la clave del mapa
    }
    return false;                                                   //Si se acaba el ciclo de iteración de las claves significa que el valor a evaluar no se encuentra en el mapa
                                                                    //como no se encuentra en el mapa entonces retorna false
}






class Producto_venta{
public:
    string nombre;
    vector<string> elementos;
    unsigned int costoX1;
    void guardar(map<int, vector<Producto_venta>>);
};

void Producto_venta::guardar(map<int,vector<Producto_venta>> inventario){

    ///Ésta función itera sobre la estructura que almacena todos los combos que pueden producirse en la zona de comidas del cine    ///
    ///La estructura que se maneja es: mapa<int,vector<Producto_venta>>                                                             ///
    ///donde Producto_venta es una clase que contiene la siguiente estructura: nombre, vector<string>, costoX1                      ///
    ///Mientras va iterando a su vez va ingresando la información a la base de datos que será un archivo .txt                       ///

    ofstream fichero;
    fichero.open("../ZonaDeComidasVirtual/BasesDeDatos/Combos.txt");    //Se abre el archivo Combos.txt en el cual se almacenará el mapa que contendrá todos los combos existentes
    unsigned short int cantidaddeingredientes;                          //En esta variable se almacenará la longitud del vector que contendrá los elementos necesarios para crear cada combo

    if(!fichero.is_open()){
        cout << "Error abriendo el archivo" << endl;                    //Si el archivo no se logra abrir, se imprime ese mensaje
        exit(1);
    }

    for (auto id=begin(inventario); id!=end(inventario); id++){         //Se itera sobre las claves del mapa, en éste caso son strings
        fichero << id->first;                                           //Se envia la clave al archivo .txt

        for (auto caracteristicas=begin(id->second); caracteristicas!=end(id->second); caracteristicas++){  //Se comienza a iterar sobre cada valor del mapa
                                                                                                            //Es importante resaltar que cada valor del mapa es de la siguiente manera vector<Producto_venta>
                                                                                                            //Donde cada clase es de la siguiente manera: nombre, vector<string>, costoX1
            fichero << " " << caracteristicas->nombre << " { ";
            cantidaddeingredientes = (caracteristicas->elementos).size()-1;

            for(unsigned short int pos=0; pos!=cantidaddeingredientes; pos++){                              //Como el segundo valor de Producto_venta es un vector de strings, se comienza a iterar sobre él
                fichero << (caracteristicas->elementos).at(pos) << " ";
            }

            fichero << "} " << caracteristicas->costoX1 << endl;
        }
    }
    fichero.close();                                                                                        //Se cierra el archivo
}








class Producto_base{
public:
    string nombre;
    unsigned short int tipodecantidad;  //1->unidades   2->gramos   3->mililitros
    unsigned int cantidad;
    unsigned int costoX1;

    void mostrar(map<int,vector<Producto_base>> inventario);
    void guardar(map<int,vector<Producto_base>> inventario);
    map<int,vector<Producto_base>> abrir();

    map<int,vector<Producto_base>> agregar_nuevo(map<int,vector<Producto_base>> inventario);
    map<int,vector<Producto_base>> editar_inventario(map<int,vector<Producto_base>> inventario);
};

void Producto_base::guardar(map<int,vector<Producto_base>> inventario){

    ///Ésta función itera sobre la estructura que almacena todo el inventario disponible hasta el momento                   ///
    ///La estructura que se maneja es: map<int,vector<Producto_base>>                                                       ///
    ///donde Producto_base es una clase que contiene la siguiente estructura: nombre, tipodecantidad, cantidad, costoX1     ///
    ///Mientras va iterando a su vez va ingresando la información a la base de datos que será un archivo .txt               ///

    ofstream fichero;
    fichero.open("../ZonaDeComidasVirtual/BasesDeDatos/ProductosBase.txt"); //Se abre el archivo ProductosBase.txt en el cual se almacenará el mapa que contendrá el inventario de comida del cine

    if(!fichero.is_open()){
        cout << "Error abriendo el archivo" << endl;                        //Si el archivo no se logra abrir, se imprime ese mensaje
        exit(1);
    }

    for (auto id = begin(inventario); id != end(inventario); id++){         //Se itera sobre las claves del mapa, en éste caso son ints
        fichero << id->first;                                               //Se envia la clave al archivo .txt

        for (auto caracteristicas = begin(id->second); caracteristicas != end(id->second); caracteristicas++){  //Se comienza a iterar sobre cada valor del mapa
                                                                                                                //Es importante resaltar que cada valor del mapa es de la siguiente manera vector<Producto_base>
                                                                                                                //Donde cada clase es de la siguiente manera: nombre, tipodecantidad, cantidad, costoX1
            fichero << " " << caracteristicas->nombre;
            fichero << " " << caracteristicas->tipodecantidad;
            fichero << " " << caracteristicas->cantidad;
            fichero << " " << caracteristicas->costoX1;
            fichero << endl;
        }
    }
    fichero.close();                                                        //Se cierra el archivo
}
map<int,vector<Producto_base>> Producto_base::abrir(){

    ///Ésta función itera sobre la base de datos que contiene todo el inventario                                        ///
    ///Durante la iteración, ésta va asignando cada dato al indice(clave del mapa) o a los atributos del objeto         ///
    ///tipo clase Producto_base, en ésta caso el objeto se llama 'elemento'                                             ///
    ///La estructura que se maneja es: map<int,vector<Producto_base>>                                                   ///
    ///donde Producto_base es una clase que contiene la siguiente estructura: nombre, tipodecantidad, cantidad, costoX1 ///


    map<int,vector<Producto_base>> inventario;
    Producto_base elemento;                                                 //Se declara un objeto de la clase Producto_base
    unsigned short int indice;

    ifstream fichero;                                                         //Abre el archivo en modo lectura
    fichero.open("../ZonaDeComidasVirtual/BasesDeDatos/ProductosBase.txt");   //Se abre el archivo ProductosBase.txt en el cual se almacenará el mapa que contendrá el inventario de comida del cine

    if(!fichero.is_open()){                                                 //Se comprueba si el archivo fue abierto exitosamente
        cout << "Error abriendo el archivo" << endl;                        //Si el archivo no se logra abrir, se imprime ese mensaje
        exit(1);
    }

    while(!fichero.eof()){                                                  //Se itera mientras que no se haya llegado al final del archivo
                                                                            //Se va asignando los valores encontrados en el archivo, cada valor va hasta antes de encontrar un salto de linea o un espacio
        fichero >> indice;
        fichero >> elemento.nombre;
        fichero >> elemento.tipodecantidad;
        fichero >> elemento.cantidad;
        fichero >> elemento.costoX1;
        inventario[indice].push_back(elemento);
    }
    fichero.close();                                                        //Se cierra el archivo
    return inventario;                                                      //Se retorna un mapa con el contenido de la información recolectada del archivo
}


map<int,vector<Producto_base>> manejo_de_inventario(map<int,vector<Producto_base>> inventario, Producto_base elemento, unsigned short int indice){

    ///Ésta función recibe el mapa wue contiene los productos basicos para formar combos para el publico, un objeto de la clase Producto_base y ///
    ///un indice que se usará como clave en el mapa y así poder asignarle un nuevo vector como clave.                                           ///
    ///La función retorna el mapa original con las modificaciones hechas.                                                                       ///

    unsigned short int aux_tipodecantidad;
    inventario[indice] = {};                                                                                //Se vacia el valor asociado a la clave para poder evitar posibles errores

    cout << "\nIngrese el nuevo nombre del producto: ";
    cin >> elemento.nombre;                                                                                     //Se le da el atributo nombre al objeto elemento
                                                                                                                //elemento hace parte de la clase Producto_base

    do{
        cout << "Ingrese el numero del tipo de cantidad ((1)->unidades   (2)->gramos   (3)->mililitros): ";
        cin >> aux_tipodecantidad;                                                                              //Se le da el valor que debería ir en tipodecantidad para poder evaluarlo antes de proceder a entregarle el valor al atributo del objeto 'elemento'
        if(aux_tipodecantidad==1 or aux_tipodecantidad==2 or aux_tipodecantidad==3)                             //Se evalua si cumple con un valor en el parametro dado
            elemento.tipodecantidad=aux_tipodecantidad;
    }while(aux_tipodecantidad>3 or aux_tipodecantidad==0);                                                      //Se continua pidiendo el valor si el valor ingresado ha sido erroneo

    cout << "Ingrese la cantidad: ";
    cin >> elemento.cantidad;                                                                                   //Se le da el cantidad nombre al objeto elemento

    cout << "\n-----------------ACLARACION-----------------\n";
    cout << "El costo se ingresa por el valor de 1 unidad\n";
    cout << "o 1 gramo o 1 miligramo, todo depende de lo \n";
    cout << "que se ingreso anteriormente.";
    cout << "\n--------------------------------------------\n";
    cout << "Ingrese el costo: ";
    cin >> elemento.costoX1;                                                                                    //Se le da el cantidad costoX1 al objeto elemento

    inventario[indice].push_back(elemento);                                                                 //Se asocia como clave a 'elemento'

    return inventario;                                                                                      //Se retorna un mapa que contiene toda la información del inventario
}
map<int,vector<Producto_base>> Producto_base::agregar_nuevo(map<int,vector<Producto_base>> inventario){

    ///Ésta función le permite al administrador agregar NUEVO inventario a la base de datos                                 ///
    ///La función le va pidiendo al administrador los que se requiere para llenar el mapa                                   ///
    ///La estructura que se maneja es: map<int,vector<Producto_base>>                                                       ///
    ///donde Producto_base es una clase que contiene la siguiente estructura: nombre, tipodecantidad, cantidad, costoX1     ///
    ///Para el nuevo inventario crea un objeto de la clase Producto_base y se van agregando los atributos que éste requiere ///
    ///cuando se termina de adjuntar todos los atributos, Producto_base se almacena en el mapa como si fuese un vector      ///

    unsigned short int indice = (inventario.size()+1);
    unsigned short int continuar;


    do{
        Producto_base elemento;                                                                                     //Se crea un objeto de la clase Producto_base
        cout << "\n\n.....................................NUEVOS PRODUCTOS.....................................";
        inventario = manejo_de_inventario(inventario, elemento, indice);                                            //Se llama a la función que se encarga de editar el vector que contiene los productos base para la zona de comidas
        cout << "..........................................................................................\n\n";

        do{
            cout << "Si desea seguir ingresando inventario ingrese (1) sino (0): ";
            cin >> continuar;
            if(continuar>1)
                cout << "Numero no valido.\n";
        }while(continuar>1);                                                            //Se evalua si el valor ingresado por el usuario cumple con los parametros
        indice++;

    }while (continuar==1);
    return inventario;                                                                  //Se retorna un mapa con el inventario
}
void Producto_base::mostrar(map<int,vector<Producto_base>> inventario){

    ///Ésta función itera sobre la base de datos que contiene todo el inventario                                        ///
    ///Durante la iteración, ésta va mostrandole al administrador el contenido del inventario en una cierta estructura  ///

    cout << endl;
    for (auto id = begin(inventario); id != end(inventario); id++){         //Se itera sobre las claves del mapa, en éste caso son ints
        cout << "|-(" << id->first << ")";                                  //Se muestra la clave del mapa

        for (auto caracteristicas = begin(id->second); caracteristicas != end(id->second); caracteristicas++){  //Se comienza a iterar sobre cada valor del mapa
                                                                                                                //Es importante resaltar que cada valor del mapa es de la siguiente manera vector<Producto_base>
                                                                                                                //Donde cada clase es de la siguiente manera: nombre, tipodecantidad, cantidad, costoX1
            cout << " " << caracteristicas->nombre;
            cout << " " << caracteristicas->cantidad;

            if(caracteristicas->tipodecantidad == 1)
                cout << " unidad(es).........";
            else if(caracteristicas->tipodecantidad == 2)
                cout << " gramo(s)...........";
            else
                cout << " mililitro(s).......";

            cout << " $" << (caracteristicas->costoX1)*(caracteristicas->cantidad) << endl;         //Como el costo almacenado en el mapa corresponde al de un solo elemento,
                                                                                                    //entonces se calcula el costo de la cantidad de elementos que se tiene en total y se imprime
        }
    }
    cout << endl;
}
map<int,vector<Producto_base>> Producto_base::editar_inventario(map<int,vector<Producto_base>> inventario){

    ///La función recibe un mapa con todos los datos del inventario y dentro de la función se pide la clave del ///
    ///valor a cambiar (clave == ubicacion), cuando se llega a la posición dada se invoca la función            ///
    ///'manejo_de_inventario' para poder hacerle los cambios respectivos a la clave.                            ///
    ///La función retorna un mapa con los cambios hechos al original.                                           ///

    unsigned short int ubicacion;
    cout << "Ingrese el numero del producto que desea editar: ";
    cin >> ubicacion;

    if(evaluacion_de_indices(inventario, ubicacion)==true){                     //Se evalua si el valor entregado por el administrador verdaderamente se encuentra en el mapa
        for (auto id = begin(inventario); id != end(inventario); id++){         //Se itera sobre las claves del mapa, en éste caso son ints
            if((id->first)==ubicacion){
                cout << "\n\n.................................CAMBIOS EN EL INVENTARIO.................................";
                inventario = manejo_de_inventario(inventario, *(begin(id->second)), ubicacion);                                            //Se llama a la función que se encarga de editar el vector que contiene los productos base para la zona de comidas
                cout << "..........................................................................................\n\n";
                break;
            }
        }
    }
    else
        cout << "El numero del producto ingresado no se encuentra.\n";
    return inventario;
}





int main()
{
    //Check de funciones//
        Producto_base elementos;
        map<int,vector<Producto_base>> inventario;
        inventario = elementos.abrir();
        elementos.mostrar(inventario);
        //inventario = elementos.editar_inventario(inventario);
        //elementos.mostrar(inventario);


        inventario = elementos.agregar_nuevo(inventario);
        elementos.guardar(inventario);

        //abrir_inventario();
}


