#ifndef PRODUCTO_VENTA_H
#define PRODUCTO_VENTA_H

#include <Producto_bases.h>
#include <Funciones.h>
#include <string>

class Producto_venta{
private:
    struct ingrediente{
        string nombre;
        unsigned int cantidad;
    };
    bool existencia_en_inventario(map<int,vector<Producto_base>> inventario, string nombre_producto);
    map<int,vector<Producto_venta>> manejo_de_combos(map<int,vector<Producto_base>> inventario, Producto_venta elemento, unsigned short int indice, map<int,vector<Producto_venta>> combo);
public:
    string nombre;
    unsigned int costoX1;
    vector<ingrediente> implementos;
    void guardar(map<int, vector<Producto_venta>> combos);
    void mostrar(map<int,vector<Producto_venta>> combos);
    map<int,vector<Producto_venta>> abrir();
    map<int,vector<Producto_venta>> agregar(map<int,vector<Producto_base>> inventario, map<int,vector<Producto_venta>> combos);
    map<int,vector<Producto_venta>> editar(map<int,vector<Producto_base>> inventario, map<int,vector<Producto_venta>> combos);

    bool disponibilidad(map<int,vector<Producto_venta>> combos, unsigned short int tipodecombo, map<int,vector<Producto_base>> inventario);
    map<int,vector<Producto_base>> compra(map<int,vector<Producto_venta>> combos, unsigned short int tipodecombo, map<int,vector<Producto_base>> inventario);
    unsigned short int seleccion(map<int,vector<Producto_venta>> combos, map<int,vector<Producto_base>> inventario);
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
        elemento.implementos = {};
    }

    fichero.close();                                                        //Se cierra el archivo
    return combos;                                                          //Se retorna un mapa con el contenido de la información recolectada del archivo
}

map<int,vector<Producto_venta>> Producto_venta::manejo_de_combos(map<int,vector<Producto_base>> inventario, Producto_venta elemento, unsigned short int indice, map<int,vector<Producto_venta>> combo){

    ///Ésta función recibe el mapa que contiene los productos basicos para formar combos para el publico, un objeto de la clase Producto_base, ///
    ///un indice que se usará como clave en el mapa (y así poder asignarle un nuevo vector como clave), además de que también recibe el mapa   ///
    ///que contiene toda la información de los combos.                                                                                         ///
    ///La función retorna el mapa original de los combos con las modificaciones hechas.                                                        ///


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
    cin.ignore();
    cout << "\n\n.......................................NUEVOS COMBOS......................................";
    Producto_base materiaprima;
    materiaprima.mostrar(inventario);               //Al llamar esa función en éste punto, le permite al usuario (en este caso el administrador) poder ver los diferentes elementos que se tienen disponibles
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
                Producto_base materiaprima;
                materiaprima.mostrar(inventario);               //Al llamar esa función en éste punto, le permite al usuario (en este caso el administrador) poder ver los diferentes elementos que se tienen disponibles
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

bool Producto_venta::existencia_en_inventario(map<int,vector<Producto_base>> inventario, string nombre_producto){

    ///Recibe un mapa que contiene toda la información del inventario y un string que representa el nombre de algún elemento    ///
    ///retorna true si el string se encontró en el mapa y false si no                                                           ///

    for(auto id_inventario=begin(inventario); id_inventario!=end(inventario); id_inventario++){             //Itera sobre el identificador de cada elemento
        for (auto elemento_inventario=begin(id_inventario->second); elemento_inventario!=end(id_inventario->second); elemento_inventario++){    //Se itera sobre un vector<Producto_base>
            if((elemento_inventario->nombre)==(nombre_producto))
                return true;    //Retorna true si se encontró el producto
        }
    }
    return false;   //Retorna false si no se encontró
}
bool Producto_venta::disponibilidad(map<int,vector<Producto_venta>> combos, unsigned short int tipodecombo, map<int,vector<Producto_base>> inventario){   //FALTA CUANDO UN COMBO NO ESTÁ DISPONIBLE

    ///Se supone que el tipo de combo sí se encuentra en la base de datos del inventario o sino se imprime que el combo no está disponible          ///
    ///Recibe todos los datos contenidos en el inventario y tambien los de los combos, además también recibe que tipo de combo hay que evaluar      ///
    ///se procede a evaluar los implementos de cada combo en el contenido del inventario, y retorna true si el combo está disponible y false si no  ///

    for (auto id = begin(combos); id != end(combos); id++){                                                         //Se itera sobre las claves del mapa de los combos (los identificadores de cada combo)
        if((id->first)==tipodecombo){
            for (auto caracteristicas = begin(id->second); caracteristicas != end(id->second); caracteristicas++){  //Se comienza a iterar sobre el vector<Producto_venta>
                                                                                                                    //(ahí se encuentra basicamente toda la información relevante y necesaria de los combos)
                for (auto ingre = begin(caracteristicas->implementos); ingre != end(caracteristicas->implementos); ingre++){    //Se inicia la evaluación en el vector<ingrediente>
                                                                                                                                //Ese vector que se encuentra dentro de vector<Producto_venta>, contiene toda la información relacionada con los implementos necesarios para poder armar el combo

                    if(existencia_en_inventario(inventario, ingre->nombre)==true){                                              //Si el valor se encontró se procede a evaluar la cantidad que hay
                        for(auto id_inventario=begin(inventario); id_inventario!=end(inventario); id_inventario++){             //Itera sobre el identificador de cada elemento
                            for (auto elemento_inventario=begin(id_inventario->second); elemento_inventario!=end(id_inventario->second); elemento_inventario++){    //Se itera sobre un vector<Producto_base>
                                                                                                                                                                    //de ahí saca el nombre y la cantidad de cada producto del inventario para de esa manera poder saber si hay disponibilidad del combo o no
                                if((elemento_inventario->nombre)==(ingre->nombre) && (elemento_inventario->cantidad)<(ingre->cantidad)){            //Si el nombre del ingrediente que se tiene dentro del combo coincide
                                                                                                                                                    //con algún nombre en el inventario, y si tambien se sabe que la cantidad asociada
                                                                                                                                                    //al producto que está en el inventario es menor a la que está en el combo, entonces,
                                                                                                                                                    //se devuelve falso, o sea, que no hay disponibilidad del combo
                                    return false;                                                                       //El combo no está disponible
                                }
                                else if((elemento_inventario->nombre)==(ingre->nombre) && (elemento_inventario->cantidad)>=(ingre->cantidad)){            //Si el nombre del ingrediente que se tiene dentro del combo coincide
                                    return true;    //El combo está disponible
                                }
                            }
                        }
                    }
                    else
                        return false;                                                                                   //Como el elemento no existe en la base de datos del inventario, se retorna que el combo no está disponible
                }
                break;
            }
            break;
        }
    }
    return false;
}
map<int,vector<Producto_base>> Producto_venta::compra(map<int,vector<Producto_venta>> combos, unsigned short int tipodecombo, map<int,vector<Producto_base>> inventario){

    ///Parte de la suposición de que hay disponibilidad del combo   ///
    ///retorna un mapa con la información del inventario modificada ///

    for (auto id = begin(combos); id != end(combos); id++){                                                                                     //Se itera sobre las claves del mapa de los combos (los identificadores de cada combo)
        if((id->first)==tipodecombo){
            for (auto caracteristicas = begin(id->second); caracteristicas != end(id->second); caracteristicas++){                              //Se comienza a iterar sobre el vector<Producto_venta>
                                                                                                                                                //(ahí se encuentra basicamente toda la información relevante y necesaria de los combos)
                for (auto ingre = begin(caracteristicas->implementos); ingre != end(caracteristicas->implementos); ingre++){                                    //Se inicia la evaluación en el vector<ingrediente>
                                                                                                                                                                //Ese vector que se encuentra dentro de vector<Producto_venta>, contiene toda la información relacionada con los implementos necesarios para poder armar el combo
                    for(auto id_inventario=begin(inventario); id_inventario!=end(inventario); id_inventario++){                                                 //Itera sobre el identificador de cada elemento
                        for (auto elemento_inventario=begin(id_inventario->second); elemento_inventario!=end(id_inventario->second); elemento_inventario++){        //Se itera sobre un vector<Producto_base>
                            if((elemento_inventario->nombre)==(ingre->nombre)){            //Si el nombre del ingrediente que se tiene dentro del combo coincide con algún nombre en el inventario, se procede a alterar la cantidad de productos en el inventario

                                Producto_base aux;                                          //Se pasa toda la información de el vector elemento a otro vector y se le hace la modificación en la cantidad

                                bool estado=true;
                                string aux_cantidad= to_string((elemento_inventario->cantidad)-(ingre->cantidad));

                                for(unsigned short int n=0; n<aux_cantidad.size();n++){  //Se itera sobre todo el string en busca de algún caracter que no sea un digito
                                    if(!isdigit(aux_cantidad.at(n)))
                                        estado = false;
                                }
                                if(estado==true){
                                    aux.nombre=elemento_inventario->nombre;
                                    aux.tipodecantidad = elemento_inventario->tipodecantidad;
                                    aux.cantidad = stoi(aux_cantidad);
                                    aux.costoX1 = elemento_inventario->costoX1;
                                    unsigned int aux_id = id_inventario->first;                //Se crea esa variable para evitar que a información se desordene

                                    id_inventario = inventario.erase(id_inventario);
                                    inventario[aux_id].push_back(aux);    //Se actualiza todo el vector y se le da ese valor a la clave
                                }
                                break;
                            }
                        }
                    }
                }
            }
            break;
        }
    }
    return inventario;
}
unsigned short int Producto_venta::seleccion(map<int,vector<Producto_venta>> combos, map<int,vector<Producto_base>> inventario){

    ///Ésta función le pregunta al usuario que tipo de combo de comida quiere y a su vez lo evalúa en la base de datos de los combos. ///
    ///Ésta función recibe el mapa de los combos y la del inventario.                                                                 ///

    Producto_venta comboavender;
    unsigned int numerodecombo;
    do{
        numerodecombo=evaluacion_dato_ingresado("el combo que desea");  //Al llamar esa función, se puede asegurar que numerodecombo será un
                                                                        //numero entero y no permitirá el ingreso de otro dato por parte del usuario
    }while(evaluacion_de_indices(combos, numerodecombo) == false);  //El proceso de evaluación del dato entregado se repite hasta que el
                                                                    //numero que el cliente ingrese esté en las claves del mapa que contiene
                                                                    //toda la información sobre los combos de comida que hay.
    if(comboavender.disponibilidad(combos, numerodecombo, inventario) == true){
        return numerodecombo;    //El combo está listo para la facturación y se retorna el combo elegido.
    }
    else
        cout << "El combo no tiene disponibilidad en este momento.\n";
    return 0;
}



#endif // PRODUCTO_VENTA_H
