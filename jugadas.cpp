#include "jugadas.h"
#include <cmath> 
#include <iostream> 
using namespace std;


int obtenerColor(int pieza) {
    if (pieza == blanca || pieza == damaBlanca) {
        return blanca;
    } else if (pieza == negra || pieza == damaNegra) {
        return negra;
    }
    return vacia;
}

bool esDama(int pieza) {
    return (pieza == damaBlanca || pieza == damaNegra);
}

bool sonEnemigas(int pieza1, int pieza2) {
    if (pieza1 == vacia || pieza2 == vacia) return false;
    return obtenerColor(pieza1) != obtenerColor(pieza2);
}

bool esMovimientoSimpleValido(int tablero[tamanoTablero][tamanoTablero], posicion origen, posicion destino) {
    if (!casillaValida(origen.fila, origen.columna) || !casillaValida(destino.fila, destino.columna)) {
        return false;
    }
    
    if (tablero[destino.fila][destino.columna] != vacia) {
        return false;
    }
    
    if (!casillaJugable(destino.fila, destino.columna)) {
        return false;
    }
    
    int pieza = tablero[origen.fila][origen.columna];
    if (pieza == vacia) return false; 
    
    int deltaFila = destino.fila - origen.fila;
    int deltaColumna = destino.columna - origen.columna;
    
    if (std::abs(deltaFila) != std::abs(deltaColumna)) return false;
    if (std::abs(deltaFila) != 1) return false;
    
    if (esDama(pieza)) {
        return true;
    } else {
        if (obtenerColor(pieza) == blanca) {
            return deltaFila < 0; 
        } else if (obtenerColor(pieza) == negra) {
            return deltaFila > 0; 
        }
    }
    return false;
}

bool esCapturaValida(int tablero[tamanoTablero][tamanoTablero], posicion origen, posicion destino, posicion &piezaCapturada) {
    if (!casillaValida(origen.fila, origen.columna) || !casillaValida(destino.fila, destino.columna)) {
        return false;
    }
    
    if (tablero[destino.fila][destino.columna] != vacia) return false;
    
    if (!casillaJugable(destino.fila, destino.columna)) return false;
    
    int pieza = tablero[origen.fila][origen.columna];
    if (pieza == vacia) return false;
    
    int deltaFila = destino.fila - origen.fila;
    int deltaColumna = destino.columna - origen.columna;
    
    if (std::abs(deltaFila) != std::abs(deltaColumna)) return false;
    if (std::abs(deltaFila) != 2) return false;
    
    
    piezaCapturada.fila = origen.fila + (deltaFila / 2);
    piezaCapturada.columna = origen.columna + (deltaColumna / 2);
    
    int piezaEnMedio = tablero[piezaCapturada.fila][piezaCapturada.columna];
    
    if (piezaEnMedio == vacia) return false;
    if (!sonEnemigas(pieza, piezaEnMedio)) return false; 
    
    return true;
}

bool puedeCapturarMas(int tablero[tamanoTablero][tamanoTablero], int fila, int columna) {
    int direcciones[4][2] = { {-2, -2}, {-2, 2}, {2, -2}, {2, 2} };
    posicion origen;
    origen.fila = fila;
    origen.columna = columna;
  
    for (int i = 0; i < 4; i++) {
        posicion destino;
        destino.fila = fila + direcciones[i][0];
        destino.columna = columna + direcciones[i][1];
        posicion capturada;

        if (esCapturaValida(tablero, origen, destino, capturada)) {
            return true;
        }
    }
    return false;
}

void realizarMovimientoSimple(int tablero[tamanoTablero][tamanoTablero], posicion origen, posicion destino) {
    int pieza = tablero[origen.fila][origen.columna];
    tablero[destino.fila][destino.columna] = pieza;
    tablero[origen.fila][origen.columna] = vacia;
    verificarPromocion(tablero, destino.fila, destino.columna);
}

void realizarCaptura(int tablero[tamanoTablero][tamanoTablero], posicion origen, posicion destino, posicion piezaCapturada) {
    int pieza = tablero[origen.fila][origen.columna];
    tablero[destino.fila][destino.columna] = pieza;
    tablero[origen.fila][origen.columna] = vacia;
    tablero[piezaCapturada.fila][piezaCapturada.columna] = vacia;
    verificarPromocion(tablero, destino.fila, destino.columna);
}

void verificarPromocion(int tablero[tamanoTablero][tamanoTablero], int fila, int columna) {
    int pieza = tablero[fila][columna];
    int color = obtenerColor(pieza); 
    
    if (color == blanca && fila == 0 && !esDama(pieza)) {
        tablero[fila][columna] = damaBlanca;
        cout << "¡Promocion a Dama Blanca!" << endl;
    }
    else if (color == negra && fila == tamanoTablero - 1 && !esDama(pieza)) {
        tablero[fila][columna] = damaNegra;
        cout << "¡Promocion a Dama Negra!" << endl;
    }
}

