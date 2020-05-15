#ifndef VENTAS_H
#define VENTAS_H

#include <vector>
#include <chrono>
#include <ctime>
#include <Producto_venta.h>

struct venta{
    string fecha;
    string nombredelcombo;
    unsigned int precio;
    unsigned long int usuario;
};

vector<venta> facturacion(map<int,vector<Producto_venta>> combos, unsigned short int tipodecombo, vector<venta> facturacompleta, unsigned long int usuario){

    ///Esta funcion calcula almacena las ventas para poder así generar un reporte de ventas a futuro.   ///
    ///La función se almacena en un vector<venta>                                                       ///

    venta factura;
    for (auto id = begin(combos); id != end(combos); id++){                                                                                     //Se itera sobre las claves del mapa de los combos (los identificadores de cada combo)
        if((id->first)==tipodecombo){
            for (auto caracteristicas = begin(id->second); caracteristicas != end(id->second); caracteristicas++){                              //Se comienza a iterar sobre el vector<Producto_venta>
                                                                                                                                                //(ahí se encuentra basicamente toda la información relevante y necesaria de los combos)
                factura.nombredelcombo = caracteristicas->nombre;
                factura.precio = caracteristicas->costoX1;
            }
            break;
        }
    }
    time_t fecha = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());  //Se calcula la hora real en la que fue hecha la factura
    factura.fecha = ctime(&fecha);
    factura.usuario = usuario;
    facturacompleta.push_back(factura);
    return facturacompleta;
}
unsigned int mostrar_factura(vector<venta> factura){

    ///Esta función imprime el vector<venta> el cual contiene la información de una factura en cierto momento  ///
    ///Esta función simplemente es otra manera de imprimir el vector, para poder mostrarselo al cliente        ///

    unsigned short int precio=0;
    cout << "\n..............................Factura..............................\n";
    for(auto venta = begin(factura); venta != end(factura); venta++){
        if(precio==0)
            cout << venta->fecha << endl;
        cout << venta->nombredelcombo << "......................." << venta->precio << endl;
        precio+=(venta->precio);
    }
    return precio;
}
void guardar(vector<venta> facturas){

    ///Ésta función itera sobre la estructura que almacena todas las facturas                                   ///
    ///Mientras va iterando a su vez va ingresando la información a la base de datos que será un archivo .txt   ///

    ofstream fichero;
    fichero.open("../ZonaDeComidasVirtual/BasesDeDatos/ReporteDeVentas.txt");    //Se abre el archivo Combos.txt en el cual se almacenará el mapa que contendrá todos los combos existentes

    if(!fichero.is_open()){
        cout << "Error abriendo el archivo" << endl;                    //Si el archivo no se logra abrir, se imprime ese mensaje
        exit(1);
    }
    unsigned int longitud = facturas.size(), iterador = 0;
    string aux, aux2;
    int n_aux;

    for (auto id=begin(facturas); id!=end(facturas); id++){                 //Se itera sobre los elementos del vector
        aux="";
        aux2="";
        aux = id->fecha;
        n_aux = aux.size();
        for(int i=0; i<n_aux-1; i++)
            aux2+=aux.at(i);
        fichero << aux2;
        fichero << " { " << id->nombredelcombo << " } ";
        fichero << id->precio << " ";
        fichero << id->usuario;
        iterador++;
        if(iterador!=longitud)
            fichero << endl;
    }
    fichero.close();                                                         //Se cierra el archivo
}
vector<venta> abrirVentas(){

    ///Ésta función itera sobre la base de datos que contiene todas las facturas                                      ///
    ///Ésta función retorna un vector de estructuras de venta vector<venta>, ese vector contiene todas las facturas   ///

    venta factura;
    vector<venta> facturas = {};
    string auxiliarqueevalua, nombredelelemento = "";

    ifstream fichero;                                                         //Abre el archivo en modo lectura
    fichero.open("../ZonaDeComidasVirtual/BasesDeDatos/ReporteDeVentas.txt");   //Se abre el archivo ProductosBase.txt del cual se sacará el mapa que contendrá el inventario de comida del cine

    if(!fichero.is_open()){                                                 //Se comprueba si el archivo fue abierto exitosamente
        cout << "Error abriendo el archivo" << endl;                        //Si el archivo no se logra abrir, se imprime ese mensaje
        exit(1);
    }


    while(!fichero.eof()){                                                  //Se itera mientras que no se haya llegado al final del archivo
                                                                            //Se va asignando los valores encontrados en el archivo, cada valor va hasta antes de encontrar un salto de linea o un espacio
        //fichero >> auxiliarqueevalua;
        //cout << "auxiliar: " << auxiliarqueevalua << endl;
        do{
            fichero >> auxiliarqueevalua;
            if(auxiliarqueevalua=="{")
                break;
            nombredelelemento+=auxiliarqueevalua;
            nombredelelemento+=" ";
        }while(auxiliarqueevalua != "{");

        auxiliarqueevalua = nombredelelemento;
        nombredelelemento = "";
        for(unsigned short int pos=0; pos<auxiliarqueevalua.size()-1; pos++)
            nombredelelemento+=auxiliarqueevalua[pos];

        factura.fecha = nombredelelemento;

        nombredelelemento="";
        auxiliarqueevalua="";
        do{
            fichero >> auxiliarqueevalua;
            if(auxiliarqueevalua=="}")
                break;
            nombredelelemento += auxiliarqueevalua;
            nombredelelemento+=" ";
        }while(auxiliarqueevalua != "}");

        auxiliarqueevalua = nombredelelemento;
        nombredelelemento = "";

        for(unsigned short int pos=0; pos<auxiliarqueevalua.size()-1; pos++)
            nombredelelemento+=auxiliarqueevalua[pos];



        factura.nombredelcombo = nombredelelemento;
        fichero >> factura.precio;
        fichero >> factura.usuario;
        facturas.push_back(factura);
    }
    fichero.close();                                                        //Se cierra el archivo
    return facturas;                                                        //Se retorna un mapa con el contenido de la información recolectada del archivo
}
void mostrarVentas(vector<venta> factura){

    ///Esta función imprime el vector<venta> el cual contiene la información de todas las facturas  ///
    ///Esta función simplemente es otra manera de imprimir el vector, para poder mostrarselo al     ///
    ///administrador con mayor precisión.                                                           ///

    unsigned short int precio=0;
    for(auto venta = begin(factura); venta != end(factura); venta++){
        if(precio==0)
            cout << venta->fecha << endl;
        cout << venta->nombredelcombo << "......................." << venta->precio << "    cliente: " << venta->usuario << endl;
        precio+=(venta->precio);
    }
}
vector<venta> SumaFacturas(vector<venta> facturita, vector<venta>facturatotal){

    ///Esta funcion itera en un vector y a su vez le va pasando los datos de éste a otro vector   ///
    ///Basicamente suma las facturas, las acumula                                                 ///

    venta factura;
    for (auto id = begin(facturita); id != end(facturita); id++){
        factura.fecha = id->fecha;
        factura.nombredelcombo = id->nombredelcombo;
        factura.precio = id->precio;
        factura.usuario = id->usuario;
        facturatotal.push_back(factura);
        factura = {};
    }
    return facturatotal;
}


#endif // VENTAS_H
