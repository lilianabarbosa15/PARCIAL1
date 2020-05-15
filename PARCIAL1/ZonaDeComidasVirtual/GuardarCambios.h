#ifndef GUARDARCAMBIOS_H
#define GUARDARCAMBIOS_H

#include <iostream>
#include <fstream>
using namespace std;

void Escritura(string archivobinario){
    ofstream fichero;                                                         // Abre el archivo en modo escritura
    fichero.open("../ZonaDeComidasVirtual/BasesDeDatos/Combos.txt");      // Se pone de manera explicita la ruta donde se encuentra el archivo
    if (!fichero.is_open())                                                   // Se comprueba si el archivo fue abierto exitosamente
    {
      std::cout << "Error abriendo el archivo" << endl;
      exit(1);
    }
    fichero << archivobinario;
    fichero.close();                                                          // Se cierra el archivo abierto
}

#endif // GUARDARCAMBIOS_H
