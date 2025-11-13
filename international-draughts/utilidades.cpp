#include "utilidades.h"
#include <iostream>
#include <fstream>  
#include <cstdlib>  
#include <cstring>  
using namespace std;


int letraAColumna(char letra) {
    if (letra >= 'a' && letra <= 'z') {
        letra = letra - 'a' + 'A';  
    }
    
    if (letra >= 'A' && letra <= 'J') {
        return letra - 'A';  
    }
    
    return -1; 
}


char columnaALetra(int columna) {
    if (columna >= 0 && columna < tamanoTablero) {
        return 'A' + columna;  
    }
    return '?'; 
}


bool notacionAPosicion(const char* notacion, posicion &pos) {
    if (notacion == NULL || notacion[0] == '\0') {
        return false;
    }
    int columna = letraAColumna(notacion[0]);
    if (columna == -1) {
        return false;
    }
    int fila = -1;


    if (notacion[1] == '1' && notacion[2] == '0') {
        fila = 9;  
    }
    
    else if (notacion[1] >= '1' && notacion[1] <= '9') {
        fila = (notacion[1] - '1');  
    }
    else {
        return false; 
    }
    
    
    if (fila < 0 || fila >= tamanoTablero) {
        return false;
    }
    
    
    pos.fila = fila;
    pos.columna = columna;
    
    return true;
}


void posicionANotacion(posicion pos, char* notacion) {
    notacion[0] = columnaALetra(pos.columna);
    int numeroFila = pos.fila + 1;
    
    if (numeroFila == 10) {
        notacion[1] = '1';
        notacion[2] = '0';
        notacion[3] = '\0';  
    } else {
        notacion[1] = '0' + numeroFila;  
        notacion[2] = '\0';  
    }
}


void limpiarPantalla() {
    // Detectar sistema operativo
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Linux/Mac
    #endif
}


void pausar() {
    cout << "\nPresiona ENTER para continuar...";
    cin.ignore(1000, '\n'); 
    cin.get();  
}


void mostrarMensaje(const char* mensaje) {
    int longitud = 0;

    while (mensaje[longitud] != '\0') {
        longitud++;
    }
    cout << "\n";


    for (int i = 0; i < longitud + 4; i++) {
        cout << "=";
    }
    cout << "\n";
    
    
    cout << "  " << mensaje << "  \n";
    
    for (int i = 0; i < longitud + 4; i++) {
        cout << "=";
    }
    cout << "\n\n";
}





void mostrarEncabezado() {
    cout << "\n";
    cout << "===========================================\n";
    cout << "|                                         |\n";
    cout << "|    DAMAS INTERNACIONALES 10x10          |\n";
    cout << "|                                         |\n";
    cout << "|   B = Blanca      N = Negra             |\n";
    cout << "|   W = Dama Blanca Q = Dama Negra        |\n";
    cout << "|   # = Casilla jugable  . = No jugable   |\n";
    cout << "|                                         |\n";
    cout << "===========================================\n";
}

void inicializarArchivoCSV() {
    ifstream verificar("historial.csv");
    if (!verificar.good()) {
        verificar.close();
        
        ofstream archivo("historial.csv");
        if (archivo.is_open()) {
            archivo << "Turno,Jugador,Movimiento,Tipo\n";
            archivo.close();
        }
    } else {
        verificar.close();
    }
}


void guardarMovimientoCSV(RegistroMovimiento registro) {
    ofstream archivo("historial.csv", ios::app);
    
    if (archivo.is_open()) {
        archivo << registro.numeroTurno << ","
                << registro.jugador << ","
                << registro.movimiento << ","
                << registro.tipo << "\n";
        
        archivo.close();
    } else {
        cout << "Error: No se pudo guardar el movimiento en el historial.\n";
    }
}
