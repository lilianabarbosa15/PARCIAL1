#ifndef TRADUCCION_H
#define TRADUCCION_H

#include <iostream>
#include <math.h>
#include <sstream>
using namespace std;


class traduccion{
public:
    traduccion();
    string decimal_a_string_binario(int numerodecimal);
    string string_binario_a_ASCII(string datocompletobinario);
    ~traduccion();
};


int StringAInt (string binario){  //Para ésta función es muy importante tener la librería math.h
    int acumulador = 0;
    int exponente = 0;
    for(int pos=7; pos>=0; pos--){
        if(binario[pos]=='1')
            acumulador+=(pow(2,exponente));
        exponente++;
    }
    return acumulador;
}

string traduccion::decimal_a_string_binario(int numerodecimal){  //Recibe un int y devuelve el binario del numero en string
    int cociente, residuo, i=0;
    stringstream cadena;
    string numerobinario = "";
    do{
        cociente = numerodecimal/2;
        residuo = numerodecimal%2;
        numerodecimal = cociente;
        cadena<<residuo;
        numerobinario=cadena.str();
        i++;
    }while(cociente!=0 or i<8);
    return string(numerobinario.rbegin(), numerobinario.rend());  //DEVUELVE EL STRING AL REVÉS
}

string traduccion::string_binario_a_ASCII (string datocompletobinario){  //Traduce los caracteres en binario
    unsigned int longitudbinario = datocompletobinario.size(), cantidad = 0;
    string traduccion = "";
    string aux = "";
    int significadonumerico;
    for(unsigned int p=0; p<longitudbinario; p++){
        cantidad++;
        aux+=datocompletobinario[p];
        if(cantidad==8){
            significadonumerico=StringAInt(aux);
            aux = "";
            cantidad = 0;
            traduccion += char(significadonumerico);
        }
    }
    return traduccion;
}


traduccion::traduccion(){
}
traduccion::~traduccion(){
}

#endif // TRADUCCION_H
