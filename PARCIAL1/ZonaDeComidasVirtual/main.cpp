#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <stdio.h>
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

unsigned short int evaluacion_dato_ingresado(string tipo){
    string aux;
    bool estado;
    do{
        estado=true;
        cout << "Ingrese " + tipo + ": ";
        cin >> aux;
        for(unsigned short int n=0; n<aux.size();n++){
            if(!isdigit(aux.at(n)))
                estado = false;
        }
        if(estado==true){
            return stoi(aux);
        }
    }while (estado==false);
    return 0;
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
    map<int,vector<Producto_base>> agregar(map<int,vector<Producto_base>> inventario);
    map<int,vector<Producto_base>> editar(map<int,vector<Producto_base>> inventario);
};

void Producto_base::mostrar(map<int,vector<Producto_base>> inventario){

    ///Ésta función itera sobre la estructura que contiene todo el inventario                                       ///
    ///Durante la iteración, ésta va mostrandole al administrador el contenido del inventario en una cierta manera  ///

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
void Producto_base::guardar(map<int,vector<Producto_base>> inventario){

    ///Ésta función itera sobre la estructura que almacena todo el inventario disponible hasta el momento                   ///
    ///La estructura que se maneja es: map<int,vector<Producto_base>>                                                       ///
    ///donde Producto_base es una clase que contiene la siguiente estructura: nombre, tipodecantidad, cantidad, costoX1     ///
    ///Mientras va iterando a su vez va ingresando la información a la base de datos que será un archivo .txt               ///

    unsigned short int cant_productos = inventario.size();
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
            fichero << " { " << caracteristicas->nombre;
            fichero << " } " << caracteristicas->tipodecantidad;
            fichero << " " << caracteristicas->cantidad;
            fichero << " " << caracteristicas->costoX1;
            if((id->first)<cant_productos)
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
    string auxiliarqueevalua;
    string nombredelelemento = "";
    Producto_base elemento;                                                 //Se declara un objeto de la clase Producto_base
    unsigned short int indice;

    ifstream fichero;                                                         //Abre el archivo en modo lectura
    fichero.open("../ZonaDeComidasVirtual/BasesDeDatos/ProductosBase.txt");   //Se abre el archivo ProductosBase.txt del cual se sacará el mapa que contendrá el inventario de comida del cine

    if(!fichero.is_open()){                                                 //Se comprueba si el archivo fue abierto exitosamente
        cout << "Error abriendo el archivo" << endl;                        //Si el archivo no se logra abrir, se imprime ese mensaje
        exit(1);
    }

    while(!fichero.eof()){                                                  //Se itera mientras que no se haya llegado al final del archivo
                                                                            //Se va asignando los valores encontrados en el archivo, cada valor va hasta antes de encontrar un salto de linea o un espacio
        fichero >> indice;
        fichero >> auxiliarqueevalua;
        if(auxiliarqueevalua == "{"){
            do{
                fichero >> auxiliarqueevalua;
                if(auxiliarqueevalua=="}")
                    break;
                nombredelelemento += auxiliarqueevalua;
                nombredelelemento+=" ";
            }while(auxiliarqueevalua != "}");
        }
        auxiliarqueevalua = nombredelelemento;
        nombredelelemento = "";
        for(unsigned short int pos=0; pos<auxiliarqueevalua.size()-1; pos++)
            nombredelelemento+=auxiliarqueevalua[pos];

        elemento.nombre = nombredelelemento;
        nombredelelemento = "";
        fichero >> elemento.tipodecantidad;
        fichero >> elemento.cantidad;
        fichero >> elemento.costoX1;
        inventario[indice].push_back(elemento);
    }
    fichero.close();                                                        //Se cierra el archivo
    return inventario;                                                      //Se retorna un mapa con el contenido de la información recolectada del archivo
}

map<int,vector<Producto_base>> manejo_de_inventario(map<int,vector<Producto_base>> inventario, Producto_base elemento, unsigned short int indice){

    ///Ésta función recibe el mapa que contiene los productos basicos para formar combos para el publico, un objeto de la clase Producto_base y ///
    ///un indice que se usará como clave en el mapa y así poder asignarle un nuevo vector como clave.                                           ///
    ///La función retorna el mapa original del inventario con las modificaciones hechas.                                                        ///

    unsigned short int aux_tipodecantidad;
    inventario[indice] = {};                                                                                //Se vacia el valor asociado a la clave para poder evitar posibles errores


    cout << "\nIngrese el nuevo nombre del producto: ";
    getline(cin, elemento.nombre);                                                                  //Se le da el atributo nombre al objeto elemento
                                                                                                    //elemento hace parte de la clase Producto_base

    do{
        aux_tipodecantidad = evaluacion_dato_ingresado("el numero del tipo de cantidad ((1)->unidades   (2)->gramos   (3)->mililitros)");   //Se le da el valor que debería ir en tipodecantidad para poder evaluarlo antes de proceder a entregarle el valor al atributo del objeto 'elemento'
        if(aux_tipodecantidad==1 or aux_tipodecantidad==2 or aux_tipodecantidad==3)                                                         //Se evalua si cumple con un valor en el parametro dado
            elemento.tipodecantidad=aux_tipodecantidad;
    }while(aux_tipodecantidad>3 or aux_tipodecantidad==0);                                                                                  //Se continua pidiendo el valor si el valor ingresado ha sido erroneo


    elemento.cantidad = evaluacion_dato_ingresado("la cantidad");                                           //Se le da el valor de la cantidad al objeto elemento


    cout << "\n-----------------ACLARACION-----------------\n";
    cout << "El costo se ingresa por el valor de 1 unidad\n";
    cout << "o 1 gramo o 1 miligramo, todo depende de lo \n";
    cout << "que se ingreso anteriormente.";
    cout << "\n--------------------------------------------\n";
    elemento.costoX1 = evaluacion_dato_ingresado("el costo");                                               //Se le da el valor correspondiente al costoX1 al objeto elemento



    inventario[indice].push_back(elemento);                                                                 //Se asocia como clave a 'elemento'

    return inventario;                                                                                      //Se retorna un mapa que contiene toda la información del inventario
}
map<int,vector<Producto_base>> Producto_base::agregar(map<int,vector<Producto_base>> inventario){

    ///Ésta función le permite al administrador agregar NUEVO inventario a la base de datos                                 ///
    ///La función le va pidiendo al administrador lo que se requiere para llenar el mapa                                    ///
    ///La estructura que se maneja es: map<int,vector<Producto_base>>                                                       ///
    ///donde Producto_base es una clase que contiene la siguiente estructura: nombre, tipodecantidad, cantidad, costoX1     ///
    ///Para el nuevo inventario crea un objeto de la clase Producto_base y se van agregando los atributos que éste requiere ///
    ///cuando se termina de adjuntar todos los atributos, Producto_base se almacena en el mapa como si fuese un vector      ///

    Producto_base elemento={};                                                                                     //Se crea un objeto de la clase Producto_base
    cout << "\n\n.....................................NUEVOS PRODUCTOS.....................................";
    inventario = manejo_de_inventario(inventario, elemento, (inventario.size()+1));                                            //Se llama a la función que se encarga de editar el vector que contiene los productos base para la zona de comidas
    cout << "..........................................................................................\n\n";

    return inventario;                                                                  //Se retorna un mapa con el inventario
}
map<int,vector<Producto_base>> Producto_base::editar(map<int,vector<Producto_base>> inventario){

    ///La función recibe un mapa con todos los datos del inventario y dentro de la función se pide la clave del ///
    ///valor a cambiar (clave == ubicacion), cuando se llega a la posición dada se invoca la función            ///
    ///'manejo_de_inventario' para poder hacerle los cambios respectivos al valor de la clave.                  ///
    ///La función retorna un mapa con los cambios hechos al original.                                           ///

    unsigned short int ubicacion;
    ubicacion = evaluacion_dato_ingresado("el numero del producto que desea editar");

    if(evaluacion_de_indices(inventario, ubicacion)==true){                     //Se evalua si el valor entregado por el administrador verdaderamente se encuentra en el mapa
        for (auto id = begin(inventario); id != end(inventario); id++){         //Se itera sobre las claves del mapa, en éste caso son ints
            if((id->first)==ubicacion){
                cin.ignore();
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







class Producto_venta{
private:
    struct ingrediente{
        string nombre;
        unsigned int cantidad;
    };
public:
    string nombre;
    unsigned int costoX1;
    vector<ingrediente> implementos;

    void guardar(map<int, vector<Producto_venta>> combos);
    void mostrar(map<int,vector<Producto_venta>> combos);
    map<int,vector<Producto_venta>> abrir();
    map<int,vector<Producto_venta>> agregar(map<int,vector<Producto_base>> inventario, map<int,vector<Producto_venta>> combos);
    map<int,vector<Producto_venta>> editar(map<int,vector<Producto_base>> inventario, map<int,vector<Producto_venta>> combos);
};

void Producto_venta::guardar(map<int,vector<Producto_venta>> combos){

    ///Ésta función itera sobre la estructura que almacena todos los combos que pueden producirse en la zona de comidas del cine    ///
    ///La estructura que se maneja es: mapa<int,vector<Producto_venta>>                                                             ///
    ///donde Producto_venta es una clase que contiene la siguiente estructura: nombre, costoX1, vector<ingrediente>                 ///
    ///Mientras va iterando a su vez va ingresando la información a la base de datos que será un archivo .txt                       ///

    ofstream fichero;
    fichero.open("../ZonaDeComidasVirtual/BasesDeDatos/Combos.txt");    //Se abre el archivo Combos.txt en el cual se almacenará el mapa que contendrá todos los combos existentes
    unsigned short int longitud_vector = combos.size();

    if(!fichero.is_open()){
        cout << "Error abriendo el archivo" << endl;                    //Si el archivo no se logra abrir, se imprime ese mensaje
        exit(1);
    }


    for (auto id=begin(combos); id!=end(combos); id++){                 //Se itera sobre las claves del mapa, en éste caso son strings
        fichero << id->first;                                           //Se envia la clave al archivo .txt

        for (auto caracteristicas=begin(id->second); caracteristicas!=end(id->second); caracteristicas++){  //Se comienza a iterar sobre cada valor del mapa
                                                                                                            //Es importante resaltar que cada valor del mapa es de la siguiente manera vector<Producto_venta>
                                                                                                            //Donde cada clase es de la siguiente manera: nombre, vector<string>, costoX1
            fichero << " { " << caracteristicas->nombre;
            fichero << " } " << caracteristicas->costoX1;
            fichero << " [ ";

            for(auto ingrediente=begin(caracteristicas->implementos); ingrediente!=end(caracteristicas->implementos); ingrediente++){   //Como el tercer valor de Producto_venta es un vector de strings, se comienza a iterar sobre él
                fichero << (ingrediente->nombre) << " , ";
                fichero << (ingrediente->cantidad) << " ";
            }

            fichero << "]";
            if((id->first)<longitud_vector)
                fichero << endl;
        }
    }
    fichero.close();                                                                                        //Se cierra el archivo
}
void Producto_venta::mostrar(map<int,vector<Producto_venta>> combos){

    ///Ésta función itera sobre la estructura que contiene todos los combos                                   ///
    ///Durante la iteración, ésta va mostrandole al usuario el contenido del inventario en una cierta manera  ///

    cout << endl;
    for (auto id = begin(combos); id != end(combos); id++){         //Se itera sobre las claves del mapa, en éste caso son ints
        cout << "|-(" << id->first << ")";                          //Se muestra la clave del mapa

        for (auto caracteristicas = begin(id->second); caracteristicas != end(id->second); caracteristicas++){  //Se comienza a iterar sobre cada valor del mapa
                                                                                                                //Es importante resaltar que cada valor del mapa es de la siguiente manera vector<Producto_venta>
                                                                                                                //Donde cada clase es de la siguiente manera: nombre, costoX1, vector<ingrediente> implementos
            cout << " " << caracteristicas->nombre;
            cout << ".................. $" << caracteristicas->costoX1;
            cout << endl;
        }
    }
    cout << endl;
}
map<int,vector<Producto_venta>> Producto_venta::abrir(){

    ///Ésta función itera sobre la base de datos que contiene todos los combos                                                  ///
    ///Durante la iteración, ésta va asignando cada dato al indice(clave del mapa) o a los atributos del objeto                 ///
    ///tipo clase Producto_venta, en ésta caso el objeto se llama 'elemento'                                                    ///
    ///La estructura que se maneja es: map<int,vector<Producto_venta>>                                                          ///
    ///donde Producto_venta es una clase que contiene la siguiente estructura: nombre, costoX1, vector<ingredientes> implementos///


    map<int,vector<Producto_venta>> combos;

    string auxiliar, nombre_elemento;
    unsigned short int auxiliar_cantidad;
    Producto_venta elemento;                                                 //Se declara un objeto de la clase Producto_venta

    unsigned short int indice;

    ifstream fichero;                                                         //Abre el archivo en modo lectura
    fichero.open("../ZonaDeComidasVirtual/BasesDeDatos/Combos.txt");          //Se abre el archivo Combos.txt del cual se sacará el mapa que contendrá el inventario de comida del cine

    if(!fichero.is_open()){                                                 //Se comprueba si el archivo fue abierto exitosamente
        cout << "Error abriendo el archivo" << endl;                        //Si el archivo no se logra abrir, se imprime ese mensaje
        exit(1);
    }

    while(!fichero.eof()){                                                  //Se itera mientras que no se haya llegado al final del archivo
                                                                            //Se va asignando los valores encontrados en el archivo, cada valor va hasta antes de encontrar un salto de linea o un espacio
        fichero >> indice;
        cout << "indice: " << indice << endl;

        fichero >> auxiliar;                            //Se le entrega una { lo cual significa que hay que iniciar una iteración para calcular el nombre del combo
        nombre_elemento = "";                           //Esa variable es un acumulador, por lo cual, lo mejor siempre es vaciarla para así evitar futuros errores
        fichero >> auxiliar;                            //Se toma el primer valor del nombre del combo

        while(auxiliar != "}"){
            nombre_elemento += auxiliar;
            nombre_elemento+=" ";
            fichero >> auxiliar;                        //Se va moviendo dentro del archivo, en busqueda de una } lo que indicaría el fin del nombre del combo y el inicio del valor del costo del combo
        }


        auxiliar = nombre_elemento;
        nombre_elemento = "";                           //El acumulador vuelve a vaciarse porque ahí irá el verdadero nombre del combo (el valor que tiene la variable 'auxiliar' pero sin el espacio al final)
        for(unsigned short int pos=0; pos<auxiliar.size()-1; pos++)
            nombre_elemento+=auxiliar[pos];             //Éste ciclo se realiza con el fin de quitarle el ' ' final al nombre del combo

        elemento.nombre = nombre_elemento;              //Cuando se tiene el verdadero nombre (sin el espacio final), se le pasa el valor a el objeto elemento de la clase Producto_venta

        fichero >> elemento.costoX1;            //Despues del nombre siempre irá el costo, entonces se pasa el valor directamente al objeto
                                                //El valor se pasa como un atributo del objeto
        fichero >> auxiliar;                            //Se le entrega una [ lo cual significa que hay que iniciar una iteración para calcular el nombre de un elemento del combo
        do{
            nombre_elemento = "";                       //Esa variable es un acumulador, por lo cual, lo mejor siempre es vaciarla para así evitar futuros errores
            fichero >> auxiliar;

            while (auxiliar!="," && auxiliar!="]"){
                nombre_elemento += auxiliar;
                nombre_elemento+=" ";
                fichero >> auxiliar;
            }

            if(auxiliar!="]"){      //Aquí se verifica que no se haya acabado el proceso de calculo de nombres y cantidades de productos se necesitan para el combo
                auxiliar = nombre_elemento;
                nombre_elemento = "";
                for(unsigned short int pos=0; pos<auxiliar.size()-1; pos++)
                    nombre_elemento+=auxiliar[pos];                 //Se le quita el espacio final al nombre de algún elemento que se necesita
                fichero >> auxiliar_cantidad;                       //Se le pasa el valor de la cantidad que se necesita de ese producto a la variables 'auxiliar_cantidad'

                (elemento.implementos).push_back({nombre_elemento,auxiliar_cantidad});  //(elemento.implementos) es un vector<ingrediente>
            }
        }while(auxiliar!="]");                  //El proceso se repite hasta acabar el procesamiento de los nombres y la cantidad de los elementos asociados
        combos[indice].push_back(elemento);     //Cuando ya se tienen todos los atributos asociados, se crea una clave y su respectivo valor (lo que se calculó anteriormente)
    }

    fichero.close();                                                        //Se cierra el archivo
    return combos;                                                          //Se retorna un mapa con el contenido de la información recolectada del archivo
}


map<int,vector<Producto_venta>> manejo_de_combos(map<int,vector<Producto_base>> inventario, Producto_venta elemento, unsigned short int indice, map<int,vector<Producto_venta>> combo){ //FALTA AGREGAR LO DE LA CANTIDAD

    ///Ésta función recibe el mapa que contiene los productos basicos para formar combos para el publico, un objeto de la clase Producto_base, ///
    ///un indice que se usará como clave en el mapa (y así poder asignarle un nuevo vector como clave), además de que también recibe el mapa   ///
    ///que contiene toda la información de los combos.                                                                                         ///
    ///La función retorna el mapa original de los combos con las modificaciones hechas.                                                        ///

    Producto_base materiaprima;
    materiaprima.mostrar(inventario);               //Al llamar esa función en éste punto, le permite al usuario (en este caso el administrador) poder ver los diferentes elementos que se tienen disponibles

    unsigned short int indice_vector = 0, producto_necesario, valor_cantidad;
    unsigned short int continuar=1;                                                     //Se inicializa en 1 para tener certeza de que al menos se ingresará un elemento del combo

    combo[indice] = {};                                                                             //Se vacia el valor asociado a la clave para poder evitar posibles errores

    cout << "\nIngrese el nuevo nombre del combo: ";
    getline(cin, elemento.nombre);                                                                  //Se le da el atributo nombre al objeto elemento
                                                                                                    //elemento hace parte de la clase Producto_venta
    elemento.costoX1 = evaluacion_dato_ingresado("el costo del combo");             //Se le da el valor correspondiente al costoX1 al objeto elemento

    do{
    producto_necesario = evaluacion_dato_ingresado("el numero del producto que se necesita para crear el combo");
    if(evaluacion_de_indices(inventario, producto_necesario) == true){
        for (auto id = begin(inventario); id != end(inventario); id++){         //Se itera sobre las claves del mapa, en éste caso son ints
            if((id->first)==producto_necesario){                                //Se evalua si el el indice en el que se encuentra del mapa es igual al valor ingresado por el administrador

                auto caracteristicas = begin(id->second);
                valor_cantidad = evaluacion_dato_ingresado("la cantidad del producto necesario para el combo");
                (elemento.implementos).push_back({caracteristicas->nombre,valor_cantidad});      //(elemento.implementos) corresponde al vector<ingrediente>
                                                                                                            //por lo cual es necesario ingresar los atributos de ingrediente
                                                                                                            //por medio del .push_back
                break;
            }
        }

        do{
            continuar = evaluacion_dato_ingresado("(0) si no se necesitan mas productos y (1) si aun faltan");
        }while(continuar>1);                                //Mientras que la variable continuar no sea 0 o 1 se seguirá preguntando los ingredientes necesarios para el combo
        indice_vector++;
    }
    else
        cout << "El producto no se encontro.\n";
    }while(continuar==1);

    combo[indice].push_back(elemento);                                                         //Se asocia como clave a 'elemento'
    return combo;                                                                              //Se retorna un mapa que contiene toda la información del inventario
}
map<int,vector<Producto_venta>> Producto_venta::agregar(map<int,vector<Producto_base>> inventario, map<int,vector<Producto_venta>> combos){

    ///Ésta función le permite al administrador agregar NUEVOS combos a la base de datos                                        ///
    ///La función le va pidiendo al administrador lo que se requiere para llenar el mapa                                        ///
    ///La estructura que se maneja es: map<int,vector<Producto_base>>                                                           ///
    ///donde Producto_base es una clase que contiene la siguiente estructura: nombre, costoX1, vector<ingrediente>implementos   ///
    ///Para el nuevo inventario crea un objeto de la clase Producto_venta y se van agregando los atributos que éste requiere    ///
    ///cuando se termina de adjuntar todos los atributos, Producto_venta se almacena en el mapa como si fuese un vector         ///

    Producto_venta elemento={};                                                                                     //Se crea un objeto de la clase Producto_base

    cout << "\n\n.......................................NUEVOS COMBOS......................................";
    combos = manejo_de_combos(inventario, elemento, (combos.size()+1), combos);                                     //Se llama a la función que se encarga de editar el vector que contiene los productos base para la zona de comidas
    cout << "..........................................................................................\n\n";

    return combos;
}
map<int,vector<Producto_venta>> Producto_venta::editar(map<int,vector<Producto_base>> inventario, map<int,vector<Producto_venta>> combos){

    ///La función recibe un mapa con todos los datos del inventario y otro mapa con todos los datos de los combos       ///
    ///dentro de la función se pide la clave del valor a cambiar (clave == ubicacion), cuando se llega a la posición    ///
    ///dada se invoca la función 'manejo_de_combos' para poder hacerle los cambios respectivos al valor de la clave.    ///
    ///La función retorna un mapa con los cambios hechos al original.                                                   ///

    unsigned short int ubicacion;
    ubicacion = evaluacion_dato_ingresado("el numero del combo que desea editar");

    if(evaluacion_de_indices(combos, ubicacion)==true){                     //Se evalua si el valor entregado por el administrador verdaderamente se encuentra en el mapa
        for (auto id = begin(combos); id != end(combos); id++){             //Se itera sobre las claves del mapa, en éste caso son ints
            if((id->first)==ubicacion){
                cin.ignore();
                cout << "\n\n...................................CAMBIOS EN LOS COMBOS..................................";
                combos = manejo_de_combos(inventario, *(begin(id->second)), ubicacion, combos);                                     //Se llama a la función que se encarga de editar el vector que contiene los productos base para la zona de comidas
                cout << "..........................................................................................\n\n";
                break;
            }
        }
    }

    else
        cout << "El numero del producto ingresado no se encuentra.\n";
    return combos;
}

//..........................................................................................................................//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - En edición - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
//..........................................................................................................................//



void disponibilidad(map<int,vector<Producto_venta>> combos){   //FALTA CUANDO UN COMBO NO ESTÁ DISPONIBLE

    ///Ésta función itera sobre la estructura que contiene todos los combos                                   ///
    ///Durante la iteración, ésta va mostrandole al usuario el contenido del inventario en una cierta manera  ///

    cout << endl;
    for (auto id = begin(combos); id != end(combos); id++){         //Se itera sobre las claves del mapa, en éste caso son ints
        cout << "|-(" << id->first << ")";                          //Se muestra la clave del mapa

        for (auto caracteristicas = begin(id->second); caracteristicas != end(id->second); caracteristicas++){  //Se comienza a iterar sobre cada valor del mapa
                                                                                                                //Es importante resaltar que cada valor del mapa es de la siguiente manera vector<Producto_venta>
                                                                                                                //Donde cada clase es de la siguiente manera: nombre, costoX1, vector<ingrediente> implementos
            cout << " " << caracteristicas->nombre;
            cout << ".................. $" << caracteristicas->costoX1;
            cout << endl;
        }
    }
    cout << endl;
}




int main()
{
    Producto_base elementos;
    map<int,vector<Producto_base>> inventario;
    inventario = elementos.abrir();

    Producto_venta ingrediente;
    map<int,vector<Producto_venta>> combos;
    combos = ingrediente.abrir();
    combos = ingrediente.agregar(inventario, combos);
    ingrediente.mostrar(combos);

    //ingrediente.guardar(combos);






/*
        Producto_base elementos;
        map<int,vector<Producto_base>> inventario;
        inventario = elementos.abrir();
        elementos.mostrar(inventario);
        inventario = elementos.editar_inventario(inventario);
        //elementos.mostrar(inventario);


        //inventario = elementos.agregar_nuevo(inventario);
        elementos.guardar(inventario);
*/
}

//1 { cabum 2.0 } 20000 [ salsa de tomate , 150 pasta de tomate , 15 ]
