#include "tablero.h"
#include <iostream>
using namespace std;


void inicializarTablero(int tablero[tamanoTablero][tamanoTablero]) {
    for (int i = 0; i < tamanoTablero; i++) {
        for (int j = 0; j < tamanoTablero; j++) {
            tablero[i][j] = vacia;
        }
    }
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < tamanoTablero; j++) {
            if (esCasillaOscura(i, j)) {
                tablero[i][j] = negra;
            }
        }
    }
    
    for (int i = 6; i < tamanoTablero; i++) {
        for (int j = 0; j < tamanoTablero; j++) {
            if (esCasillaOscura(i, j)) {
                tablero[i][j] = blanca;
            }
        }
    }
}


void mostrarTablero(int tablero[tamanoTablero][tamanoTablero]) {
    cout << "\n   ";
    
    for (char letra = 'A'; letra <= 'J'; letra++) {
        cout << " " << letra << " ";
    }
    cout << "\n";
    
    for (int i = 0; i < tamanoTablero; i++) {
        if (i + 1 < 10) {
            cout << " " << (i + 1) << " ";
        } else {
            cout << (i + 1) << " ";
        }
        
        for (int j = 0; j < tamanoTablero; j++) {
            int pieza = tablero[i][j];
            
            if (!esCasillaOscura(i, j)) {
                cout << " . ";  
            } else {
                switch (pieza) {
                    case vacia:
                        cout << " # ";  
                        break;
                    case blanca:
                        cout << " B ";  
                        break;
                    case negra:
                        cout << " N ";  
                        break;
                    case damaBlanca:
                        cout << " W ";  
                        break;
                    case damaNegra:
                        cout << " Q ";  
                        break;
                    default:
                        cout << " ? ";
                }
            }
        }
        cout << "\n";
    }
    cout << "\n";
}


int obtenerPieza(int tablero[tamanoTablero][tamanoTablero], int fila, int columna) {
    
    if (!esCasillaValida(fila, columna)) {
        return -1;
    }
    return tablero[fila][columna];
}


void colocarPieza(int tablero[tamanoTablero][tamanoTablero], int fila, int columna, int pieza) {
    if (esCasillaValida(fila, columna)) {
        tablero[fila][columna] = pieza;
    }
}
bool esCasillaValida(int fila, int columna) {

    return (fila >= 0 && fila < tamanoTablero && columna >= 0 && columna < tamanoTablero);
}


bool esCasillaOscura(int fila, int columna) {
    return (fila + columna) % 2 != 0;
}

int contarPiezas(int tablero[tamanoTablero][tamanoTablero], int color) {
    int contador = 0;
    
    for (int i = 0; i < tamanoTablero; i++) {
        for (int j = 0; j < tamanoTablero; j++) {
            int pieza = tablero[i][j];
            
            if (color == blanca) {
                if (pieza == blanca || pieza == damaBlanca) {
                    contador++;
                }
            } else if (color == negra) {
                if (pieza == negra || pieza == damaNegra) {
                    contador++;
                }
            }
        }
    }
    
    return contador;
}
