#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
using namespace std;

unsigned short int evaluacion_dato_ingresado(string tipo){

    ///Ésta función toma un string y evalúa si él es un número entero o no///

    string aux;
    bool estado;
    do{
        estado=true;
        cout << "Ingrese " + tipo + ": ";
        cin >> aux;
        for(unsigned short int n=0; n<aux.size();n++){  //Se itera sobre todo el string en busca de algún caracter que no sea un digito
            if(!isdigit(aux.at(n)))
                estado = false;
        }
        if(estado==true){
            return stoi(aux);   //Si se sabe con certeza que es un número entero, se transforma el string a tal
        }
    }while (estado==false);
    return 0;
}

template <class T>
bool evaluacion_de_indices(T inventario, unsigned short int indice){

    ///Es una función tipo plantilla                                                                    ///
    ///Ésta función recible cualquier mapa o vector y un valor a evaluar dentro de las claves de este   ///
    ///Si el valor a evaluar se encuentra en el mapa o vector retorna true sino false                   ///

    for (auto id = begin(inventario); id != end(inventario); id++){ //Se itera sobre las claves del mapa, en éste caso son ints
        if(id->first == indice)
            return true;                                            //Se retorna true si el valor a evaluar se encuentra dentro de la clave del mapa
    }
    return false;                                                   //Si se acaba el ciclo de iteración de las claves significa que el valor a evaluar no se encuentra en el mapa
                                                                    //como no se encuentra en el mapa entonces retorna false
}

void cambio(unsigned int precio){
    unsigned int c1=0,c2=0,c3=0,c4=0,c5=0,c6=0,c7=0,c8=0,c9=0,c10=0;
    unsigned int N;
    do{
        N = evaluacion_dato_ingresado("la cantidad con la que va a pagar");
        if(N<precio)
            cout << "Cantidad insuficiente.\n";
    }while(N<precio);

    N-=precio;

    while (N>=50000) {
        N-=50000;
        c1+=1;
    }
    while (N>=20000) {
        N-=20000;
        c2+=1;
    }
    while (N>=10000) {
        N-=10000;
        c3+=1;
    }
    while (N>=5000) {
        N-=5000;
        c4+=1;
    }
    while (N>=2000) {
        N-=2000;
        c5+=1;
    }
    while (N>=1000) {
        N-=1000;
        c6+=1;
    }
    while (N>=500) {
        N-=500;
        c7+=1;
    }
    while (N>=200) {
        N-=200;
        c8+=1;
    }
    while (N>=100) {
        N-=100;
        c9+=1;
    }
    while (N>=50) {
        N-=50;
        c10+=1;
    }
    cout << "Su cambio es: \n";
    cout << "50000: " << c1 << endl ;
    cout << "20000: " << c2 << endl ;
    cout << "10000: " << c3 << endl ;
    cout << "5000: " << c4 << endl ;
    cout << "2000: " << c5 << endl ;
    cout << "1000: " << c6 << endl ;
    cout << "500: " << c7 << endl ;
    cout << "200: " << c8 << endl ;
    cout << "100: " << c9 << endl ;
    cout << "50: " << c10 << endl ;

    if (N>0)
        cout << "Faltante: " << N << endl;
}
string decision(string producto){

    ///Funcion que se cerciona de que el usuario ingrese un dato correcto   ///

    bool estado;
    string opcionI;
    do{
        do{
            estado=true;
            cout << "(0)- Para agregar nuevo "+producto+"\n";
            cout << "(1)- Para modificar alguno existente\n";
            cout << "Ingrese el numero de la opcion que desea: ";
            cin >> opcionI;
            for(unsigned short int n=0; n<opcionI.size();n++){
                if(!isdigit(opcionI.at(n)))
                    estado = false;
            }
            if(estado==true){
                return opcionI;
            }
        }while (estado==false);
    }while (stoi(opcionI)>1);
    return "";
}
string veces(){

    ///Funcion que permite saber cuantas veces desea el usuario ingresar un dato ///
    ///se cerciona de que el usuario ingrese un dato correcto                    ///

    bool estado;
    string opcionI2;
    do{
        estado=true;
        cout << "Ingrese el numero de productos que desea editar: ";
        cin >> opcionI2;
        for(unsigned short int n=0; n<opcionI2.size();n++){
            if(!isdigit(opcionI2.at(n)))
                estado = false;
        }
        if(estado==true && stoi(opcionI2)>0)
            return opcionI2;
        else
            estado = false;
    }while(estado==false);
    return "";
}








#endif // FUNCIONES_H
