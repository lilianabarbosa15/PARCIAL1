#ifndef METODOS_H
#define METODOS_H

#include <iostream>
using namespace std;

class primermetodo{                     //Recibe un string binario y lo encripta/desencripta en el primer metodo.
private:
    string NUMERO;
    unsigned int n;
public:
    primermetodo(string numerobinario, unsigned int N);
    string encriptacion();
    string desencriptacion();
    ~primermetodo();
};

unsigned int NumeroDeUnos (string numerodelacadena, unsigned int longitud){   //Cuenta la cantidad de unos que hay en un caracter en binario
    unsigned int cantidadunos = 0;
    for(unsigned int f=0; f<longitud; f++){
        if(numerodelacadena[f]=='1')
            cantidadunos++;
    }
    return cantidadunos;
}
string IntercambioDeCerosyUnos (string original){                             //Intercambia los unos y ceros de un caracter en binario
    string cambio = "";
    unsigned int tamaniooriginal = original.size();
    for(unsigned int i=0; i<tamaniooriginal; i++){
        if(original[i]=='0')
            cambio+='1';
        else
            cambio+='0';
    }
    return cambio;
}
string Intercambiacadanbits (string original, unsigned int n){                 //Función que intercambia un 1 por un 0 y un 0 por un 1 cada n numeros
    string cambio = "";
    unsigned int contador = 0, tamaniooriginal = original.size();
    for(unsigned int x=0; x<tamaniooriginal; x++){
        contador++;
        if(contador == n){
            if(original[x] == '1')
                cambio += '0';
            else
                cambio += '1';
            contador = 0;
        }
        else
            cambio += original[x];
    }
    return cambio;
}

string primermetodo::encriptacion (){                                          //Encriptación del primer metodo
    unsigned int posicionenstr = 0, tamanio = NUMERO.size(), tamanioaux;
    string aux = "", mystring = "";
    unsigned int cantidaddeunos = 0, cantidaddeceros = 0;
    unsigned int x;
    if(tamanio>n){
        while (posicionenstr != tamanio) {              //Mientras que la posición+1 en el binario original sea diferente al tamaño de él, se itera
            x=0;
            for(;x<n; x++){
                aux+=NUMERO[posicionenstr];
                posicionenstr++;
                if(posicionenstr == tamanio)
                    break;
            }
            //-----------------------------------------------
            if((posicionenstr) == n)                      //Si la posición en el binario llega al valor de la semilla se intercabian todos los unos y ceros del primer bloque recolectado del caracter en binario
                mystring += IntercambioDeCerosyUnos(aux);
            else{
                if(cantidaddeunos == cantidaddeceros)     //Si la cantidad de 1's es igual a la de los 0's, se intercambian los unos y ceros de ese bloque
                    mystring += IntercambioDeCerosyUnos(aux);
                else if(cantidaddeceros > cantidaddeunos) //Si los ceros son mayores a los 1's se intercambian los 1's y 0's cada 2 bits
                    mystring += Intercambiacadanbits(aux, 2);
                else                                      //Si los 1's son mayores a los 0's se intercambian los 1's y 0's cada 3 bits
                    mystring += Intercambiacadanbits(aux, 3);
            }
            tamanioaux = aux.size();
            cantidaddeunos = NumeroDeUnos(aux, tamanioaux);
            cantidaddeceros = tamanioaux - cantidaddeunos;
            aux = "";
            //-----------------------------------------------
        }
    }
    else
        mystring += IntercambioDeCerosyUnos(NUMERO);    //Se intercambian los unos y ceros de todos los caracteres en binario si n es mayor o igual al tamaño de todo el archivo
    return mystring;
}

string primermetodo::desencriptacion (){
    unsigned int posicionenstr = 0, tamanio = NUMERO.size(), tamanioaux;
    string aux = "", mystring = "";
    unsigned int cantidaddeunos = 0, cantidaddeceros = 0;
    unsigned int x;
    if(tamanio>n){
        while (posicionenstr != tamanio) {              //Mientras que la posición+1 en el binario encriptado sea diferente al tamaño de él, se itera
            x=0;
            for(;x<n; x++){
                aux+=NUMERO[posicionenstr];
                posicionenstr++;
                if(posicionenstr == tamanio)
                    break;
            }

            //-----------------------------------------------
            if((posicionenstr) == n)                      //Si la posición en el binario llega al valor de la semilla se intercabian todos los unos y ceros del primer bloque recolectado del caracter encriptado
                aux = IntercambioDeCerosyUnos(aux);
            else{
                if(cantidaddeunos == cantidaddeceros)     //Si la cantidad de 1's es igual a la de los 0's, se intercambian los unos y ceros de ese bloque
                    aux = IntercambioDeCerosyUnos(aux);
                else if(cantidaddeceros > cantidaddeunos) //Si los ceros son mayores a los 1's se intercambian los 1's y 0's cada 2 bits
                    aux = Intercambiacadanbits(aux, 2);
                else                                      //Si los 1's son mayores a los 0's se intercambian los 1's y 0's cada 3 bits
                    aux = Intercambiacadanbits(aux, 3);
            }
            //-----------------------------------------------

            tamanioaux = aux.size();
            cantidaddeunos = NumeroDeUnos(aux, tamanioaux);
            cantidaddeceros = tamanioaux - cantidaddeunos;
            mystring += aux;
            aux= "";

        }
    }
    else
        mystring += IntercambioDeCerosyUnos(NUMERO);     //Se intercambian los unos y ceros de todos los caracteres en binario si n es mayor o igual al tamaño de todo el archivo
    return mystring;
}

primermetodo::primermetodo(string numerobinario, unsigned int N){
    NUMERO = numerobinario;
    n = N;
}
primermetodo::~primermetodo(){
}

#endif // METODOS_H
