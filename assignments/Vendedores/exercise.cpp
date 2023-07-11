#include <iostream>
#include <fstream>
using namespace std;
#include "Vendedor.h"
int buscaDepartamento(Depto listaDept[], int cantDept, int idDeptoABuscar) {
    // Función que busca un id de un departamento en el arreglo de departamentos
    // Si lo encuentra, regresa la posición del arreglo donde está; si no, regresa -1
    for (int i = 0; i < cantDept; i++) {
        if (listaDept[i].getIdDep() == idDeptoABuscar) {
            return i;
        }
    }
    return -1;
}

std::string nombreDepartamento(Depto listaDept[], int cantDept, int idDeptoABuscar) {
    // Función que busca un id de un departamento en el arreglo de departamentos
    // Si lo encuentra, regresa el nombre del departamento; si no, regresa ""
    for (int i = 0; i < cantDept; i++) {
        if (listaDept[i].getIdDep() == idDeptoABuscar) {
            return listaDept[i].getNombre();
        }
    }
    return "";
}

void cargaDatosDepartamentos(Depto listaDeptos[], int &cantDeptos) {
    // Carga datos del archivo Deptos.txt en listaDeptos y actualiza cantDeptos
    std::ifstream archivo("Deptos.txt");
    if (archivo.is_open()) {
        int idDep;
        std::string nombreDep;
        while (archivo >> idDep >> nombreDep) {
            Depto departamento(idDep, nombreDep);
            listaDeptos[cantDeptos] = departamento;
            cantDeptos++;
        }
        archivo.close();
    } else {
        std::cout << "Error al abrir " << std::endl;
    }
}

void muestraDepartamentos(Depto listaDept[], int cantDep) {
    // Muestra la lista de departamentos
    std::cout << "Departamentos de la tienda:" << std::endl;
    for (int i = 0; i < cantDep; i++) {
        listaDept[i].imprime();
    }
}

void cargaDatosVendedores(Vendedor listaVend[], int &cantVend, Depto listaDep[], int cantDep) {
    // Carga datos de los vendedores
    std::cout << "¿Cuántos vendedores vas a ingresar? ";
    std::cin >> cantVend;
    for (int i = 0; i < cantVend; i++) {
        std::string nombre;
        double ventas;
        int idDep;
        std::cin.ignore();
        std::cout << "Nombre: ";
        std::getline(std::cin, nombre);
        std::cout << "Ventas acumuladas: ";
        std::cin >> ventas;
        do {
            std::cout << "Departamento: ";
            std::cin >> idDep;
        } while (buscaDepartamento(listaDep, cantDep, idDep) == -1);
        listaVend[i] = Vendedor(nombre, ventas, listaDep[buscaDepartamento(listaDep, cantDep, idDep)]);
    }
}

void muestraVendedores(Vendedor listaVen[], int cantVen) {
    // Muestra la lista de vendedores
    std::cout << "Vendedores:" << std::endl;
    for (int i = 0; i < cantVen; i++) {
        listaVen[i].imprime();
    }
}

void vendedoresPorDepartamento(Vendedor listaVen[], int cantVend, Depto listaDep[], int cantDept, int idDeptoAConsultar) {
    // Muestra los nombres de los vendedores de un departamento
    std::cout << "Vendedores del departamento " << idDeptoAConsultar << ":" << std::endl;
    for (int i = 0; i < cantVend; i++) {
        if (listaVen[i].getDepartamento().getIdDep() == idDeptoAConsultar) {
            std::cout << listaVen[i].getNombre() << std::endl;
        }
    }
}

void registrarVentas(Vendedor listaVend[], int cantVend) {
    // Registra las ventas de un vendedor de la lista de vendedores existentes
    std::string nombreVend;
    double ventas;
    std::cout << "Ingrese el nombre del vendedosr: ";
    std::cin.ignore();
    std::getline(std::cin, nombreVend);
    int index = -1;
    for (int i = 0; i < cantVend; i++) {
        if (listaVend[i].getNombre() == nombreVend) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        std::cout << "Ingrese las ventas a registrar: ";
        std::cin >> ventas;
        listaVend[index].setVentas(listaVend[index].getVentas() + ventas);
        std::cout << "Ventas registradas correctamente." << std::endl;
    } else {
        std::cout << "Vendedor no encontrado." << std::endl;
    }
}

int main() {
    char opcion;
    int numDepto;
    Vendedor listaVendedores[10];
    int cantVendedores = 0;
    Depto listaDeptos[10];
    int cantDeptos = 0;
    cargaDatosDepartamentos(listaDeptos, cantDeptos);
    cargaDatosVendedores(listaVendedores, cantVendedores, listaDeptos, cantDeptos);
    do {
        std::cout << std::endl;
        std::cout << "Opciones disponibles:" << std::endl;
        std::cout << " 1) Ver la lista de Departamentos" << std::endl;
        std::cout << " 2) Ver la lista de Vendedores" << std::endl;
        std::cout << " 3) Consultar vendedores de un departamento" << std::endl;
        std::cout << " 4) Registrar ventas" << std::endl;
        std::cout << " 5) Terminar" << std::endl;
        std::cin >> opcion;
        switch (opcion) {
            case '1':
                muestraDepartamentos(listaDeptos, cantDeptos);
                std::cin.ignore();
                std::cout << "Presione Enter para continuar...";
                std::cin.get();
                break;
            case '2':
                muestraVendedores(listaVendedores, cantVendedores);
                std::cin.ignore();
                std::cout << "Presione Enter para continuar...";
                std::cin.get();
                break;
            case '3': 
                std::cout << "Ingrese el departamento que desea consultar: ";
                std::cin >> numDepto;
                vendedoresPorDepartamento(listaVendedores, cantVendedores, listaDeptos, cantDeptos, numDepto);
                std::cin.ignore();
                std::cout << "\nPresione Enter para continuar...";
                std::cin.get();
                break;
            case '4': 
                registrarVentas(listaVendedores, cantVendedores);
                std::cin.ignore();
                std::cout << "Presione Enter para continuar...";
                std::cin.get();
                break;
            case '5':
                std::cout << "Has elegido salir del programa." << std::endl;
                break;
            default:
                std::cout << "Opción inválida." << std::endl;
        }
        system("clear");
    } while (opcion != '5');
    return 0;
}