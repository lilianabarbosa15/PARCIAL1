#include <iostream>
#include <vector>
#include <map>
#include <fstream>
using namespace std;


//Los combos se pueden borrar pero los elementos para armarlos no
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

    void guardar(map<int,vector<Producto_base>> inventario);
    map<int,vector<Producto_base>> abrir_inventario();
    map<int,vector<Producto_base>> agregar_inventario(map<int,vector<Producto_base>> inventario);
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

    for (auto id = begin(inventario); id != end(inventario); id++){         //Se itera sobre las claves del mapa, en éste caso son strings
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


map<int,vector<Producto_base>> Producto_base::agregar_inventario(map<int,vector<Producto_base>> inventario){

    unsigned short int indice = (inventario.size()+1);
    unsigned short int continuar;
    unsigned short int aux_tipodecantidad;

    do{
        Producto_base elemento;
        cout << "\n\n.....................................NUEVOS PRODUCTOS.....................................";
        cout << "\nIngrese el nombre del nuevo producto: ";
        cin >> elemento.nombre;

        do{
            cout << "Ingrese el numero del tipo de cantidad ((1)->unidades   (2)->gramos   (3)->mililitros): ";
            cin >> aux_tipodecantidad;
            if(aux_tipodecantidad==1 or aux_tipodecantidad==2 or aux_tipodecantidad==3)
                elemento.tipodecantidad=aux_tipodecantidad;
        }while(aux_tipodecantidad>3 or aux_tipodecantidad==0);

        cout << "Ingrese la cantidad: ";
        cin >> elemento.cantidad;

        cout << "\n-----------------ACLARACION-----------------\n";
        cout << "El costo se ingresa por el valor de 1 unidad\n";
        cout << "o 1 gramo o 1 miligramo, todo depende de lo \n";
        cout << "que se ingreso anteriormente.";
        cout << "\n--------------------------------------------\n";
        cout << "Ingrese el costo: ";
        cin >> elemento.costoX1;

        inventario[indice].push_back(elemento);
        cout << "..........................................................................................\n\n";

        do{
            cout << "Si desea seguir ingresando inventario ingrese (1) sino (0): ";
            cin >> continuar;
            if(continuar>1)
                cout << "Numero no valido.\n";
        }while(continuar>1);
        indice++;

    }while (continuar==1);
    return inventario;
}
map<int,vector<Producto_base>> Producto_base::abrir_inventario(){

    map<int,vector<Producto_base>> inventario;
    Producto_base elemento;
    unsigned short int indice;

    ifstream fichero;                                                         //Abre el archivo en modo lectura
    fichero.open("../ZonaDeComidasVirtual/BasesDeDatos/ProductosBase.txt");   //Se abre el archivo ProductosBase.txt en el cual se almacenará el mapa que contendrá el inventario de comida del cine

    if(!fichero.is_open()){                                                 //Se comprueba si el archivo fue abierto exitosamente
        cout << "Error abriendo el archivo" << endl;                        //Si el archivo no se logra abrir, se imprime ese mensaje
        exit(1);
    }

    while(!fichero.eof()){
        fichero >> indice;
        fichero >> elemento.nombre;
        fichero >> elemento.tipodecantidad;
        fichero >> elemento.cantidad;
        fichero >> elemento.costoX1;
        inventario[indice].push_back(elemento);
    }
    fichero.close();                                                        //Se cierra el archivo
    return inventario;
}



















int main()
{
    /*//Check de funciones//
        Producto_base elementos;
        map<int,vector<Producto_base>> inventario;
        inventario = elementos.agregar_inventario(inventario);
        elementos.guardar(inventario);
        abrir_inventario();
    //- - - - - - - - - - - - - - - - - - - - -*/

}


