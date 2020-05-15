#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <fstream>
#include <Metodos.h>
//#include <GuardarCambios.h>
#include <Traduccion.h>
using namespace std;

bool validacion(){
    unsigned int n=2;
    string nombredelfichero = "sudo";                                         // Nombre del archivo donde se encuentra la contraseña del administrador
    string data, numerobinariodeldato = "";
    bool iguales = false;
    ifstream fichero;                                                         // Abre el archivo en modo lectura

    fichero.open("../ZonaDeComidasVirtual/BasesDeDatos/SUDO.txt");      // Se pone de manera explicita la ruta donde se encuentra el archivo
    if (!fichero.is_open())                                                   // Se comprueba si el archivo fue abierto exitosamente
    {
      std::cout << "Error abriendo el archivo" << endl;
      exit(1);
    }
    //............................................................

    if(n>0){
         fichero >> data;                                                     //Se lee el archivo
         numerobinariodeldato =data;

         primermetodo aux1(numerobinariodeldato, n);
         numerobinariodeldato = aux1.desencriptacion();


         traduccion Traduccion;
         string clave = Traduccion.string_binario_a_ASCII(numerobinariodeldato);

         cout << "Ingrese la clave de administrador: ";
         string password;
         cin.ignore();
         getline(cin, password);
         password += '\n';

         if(password == clave && password.size()==clave.size())
             iguales=true;
    }

    fichero.close();                                                          // Se cierra el archivo abierto
    return iguales;
}





#endif // ADMINISTRADOR_H
