#include <fstream>
#include <Ventas.h>
#include <Funciones.h>
#include <Producto_bases.h>
#include <Producto_venta.h>
#include <Administrador.h>

int main()
{
    string opcionG, opcionI, opcionI2, n;
    short int auxiliar=1;
    do{
        unsigned long int cedula;
        Producto_base elementos;
        map<int,vector<Producto_base>> inventario;
        Producto_venta ingredientes;
        map<int,vector<Producto_venta>> combos;

        map<int,vector<Producto_base>> auxiliar_inventario;

        vector<venta> facturasTODAS = abrirVentas();
        vector<venta> facturas;

        combos = ingredientes.abrir();
        inventario = elementos.abrir();

        unsigned int combo_tipo;
        bool estado;
        cout << "\n......................................................ROYAL CINEX......................................................\n";
        do{
            do{
                estado=true;
                cout << "(0)- Para ingresar como administrador\n";
                cout << "(1)- Para ingresar como cliente\n";
                cout << "Ingrese el numero de la opcion que desea: ";
                cin >> opcionG;
                for(unsigned short int n=0; n<opcionG.size();n++){
                    if(!isdigit(opcionG.at(n)))
                        estado = false;
                }
                if(estado==true){
                    break;
                }
            }while (estado==false);
        }while (stoi(opcionG)>1);


        cout << "\n........................................................BIENVENIDO......................................................\n";


        if(stoi(opcionG)==0){
            bool estado = validacion(); //LA CONTRASEÑA ES 123, ESTÁ ENCRIPTADA Y NO SE PUEDE CAMBIAR
            if(estado == true){
                do{
                    do{
                        estado=true;
                        cout << "(0)- Para salir de la interfaz\n";
                        cout << "(1)- Para modificar el inventario\n";
                        cout << "(2)- Para editar los combos que se le ofrece al publico\n";
                        cout << "(3)- Para ver el reporte de ventas\n";
                        cout << "Ingrese el numero de la opcion que desea: ";
                        cin >> opcionI;
                        auxiliar = stoi(opcionI);
                        for(unsigned short int n=0; n<opcionI.size();n++){
                            if(!isdigit(opcionI.at(n)))
                                estado = false;
                        }
                        if(estado==true){
                            break;
                        }
                    }while (estado==false);
                }while (stoi(opcionI)>3);

                if(stoi(opcionI) == 1){                                                                     //OPCION DE MODIFICAR EL INVENTARIO

                    //inventario = elementos.abrir();
                    cout << "\n\n************SE TIENE EL SIGUIENTE INVENTARIO:************\n";
                    elementos.mostrar(inventario);
                    cout << "*********************************************************\n\n";
                    opcionI=decision("inventario");
                    opcionI2=veces();

                    int contador=0;
                    if(stoi(opcionI)==0){   //Para agregar nuevo inventario
                        do{
                            inventario = elementos.agregar(inventario);
                            contador++;
                        }while(stoi(opcionI2)!=contador);
                    }
                    else{                   //Para modificar el inventario existente
                        do{
                            inventario = elementos.editar(inventario);
                            contador++;
                        }while(stoi(opcionI2)!=contador);
                    }

                    elementos.mostrar(inventario);
                    elementos.guardar(inventario);
                    cout << "cambios guardados...\n";
                }
                else if(stoi(opcionI) == 2){                                                                //OPCION DE EDICIÓN DE COMBOS
                    //combos = ingredientes.abrir();
                    cout << "\n-------------SE TIENEN LOS SIGUIENTES COMBOS:-------------\n";
                    ingredientes.mostrar(combos);
                    cout << "----------------------------------------------------------\n";
                    //inventario = elementos.abrir();

                    opcionI=decision("combo");
                    opcionI2=veces();

                    int contador=0;
                    if(stoi(opcionI)==0){   //Para agregar nuevo inventario
                        do{
                            combos = ingredientes.agregar(inventario, combos);
                            contador++;
                        }while(stoi(opcionI2)!=contador);
                    }
                    else{                   //Para modificar el inventario existente
                        do{
                            combos = ingredientes.editar(inventario, combos);
                            contador++;
                        }while(stoi(opcionI2)!=contador);
                    }
                    ingredientes.guardar(combos);
                    cout << "cambios guardados...\n";
                }
                else if(stoi(opcionI) == 3){
                    cout << "-----------------------------Reporte de ventas-----------------------------\n";
                    mostrarVentas(facturasTODAS);
                    cout << "----------------------------------------------------------------------------\n";
                }
            }   //  <----------------------------------------------------------------------PROCESO DEL ADMINISTRADOR
        }

        else{
            cout << "Ingrese su cedula: ";
            cin >> cedula;
            auxiliar_inventario = elementos.abrir();
            cout << "\n-------------SE TIENEN LOS SIGUIENTES COMBOS:-------------\n";
            ingredientes.mostrar(combos);
            cout << "----------------------------------------------------------\n";
            facturas = {};
            unsigned int precio;

            do{
                do{
                    do{
                        estado=true;
                        cout << "(0)- Para salir de la interfaz\n";
                        cout << "(1)- Para elegir un combo\n";
                        cout << "(2)- Para finalizar la compra\n";
                        cout << "Ingrese el numero de la opcion que desea: ";
                        cin >> opcionI;
                        auxiliar = stoi(opcionI);
                        for(unsigned short int n=0; n<opcionI.size();n++){
                            if(!isdigit(opcionI.at(n)))
                                estado = false;
                        }
                        if(estado==true){
                            break;
                        }
                    }while (estado==false);
                }while (stoi(opcionI)>2);

                if(stoi(opcionI) == 1){
                    combo_tipo = ingredientes.seleccion(combos, auxiliar_inventario);
                    if(combo_tipo != 0){
                        facturas = facturacion(combos, combo_tipo, facturas, cedula);
                        auxiliar_inventario = ingredientes.compra(combos, combo_tipo, auxiliar_inventario);
                    }
                }
            }while(stoi(opcionI) != 2);

            if(facturas.size()>0){                                  //Se hace el proceso de facturación y venta de los combos
                precio = mostrar_factura(facturas);
                cout << "Precio total a pagar: " << precio << endl;
                cambio(precio);
                elementos.guardar(auxiliar_inventario);
                //Falta pedir la ubicación en el cine
                cout << "Ingrese la posicion del asiento y la sala: ";
                cin >> n;
                cout << "----------------------Factura-----------------------\n";
                cout << "ubicacion: " << n;
                facturasTODAS = SumaFacturas(facturas, facturasTODAS);
                guardar(facturasTODAS);
            }
        }
    }while(auxiliar != 0);
}

