#include "jugadas.h"
using namespace std;


int abs(int numero) {
    if (numero < 0) {
        return -numero;  
    }
    return numero;
}


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
    if (pieza1 == vacia || pieza2 == vacia) {
        return false;
    }
    
    return obtenerColor(pieza1) != obtenerColor(pieza2);
}

bool esMovimientoSimpleValido(int tablero[tamanoTablero][tamanoTablero], posicion origen, posicion destino) {

    if (!casillaValida(origen.fila, origen.columna) || 
        !casillaValida(destino.fila, destino.columna)) {
        return false;
    }
    
  
    if (tablero[destino.fila][destino.columna] != vacia) {
        return false;
    }
    
    if (casillaJugable(destino.fila, destino.columna)) {
        return false;
    }
    
  
    int pieza = tablero[origen.fila][origen.columna];
    if (pieza == vacia) {
        return false; 
    }
    
    
    int deltaFila = destino.fila - origen.fila;
    int deltaColumna = destino.columna - origen.columna;
    
    
    if (abs(deltaFila) != abs(deltaColumna)) {
        return false;
    }
    

    if (abs(deltaFila) != 1) {
        return false;
    }
    
   
    if (esDama(pieza)) {
        return true;
    } else {
        if (pieza == blanca) {
            return deltaFila < 0;
        } else if (pieza == negra) {
            return deltaFila > 0;
        }
    }
    
    return false;
}


bool esCapturaValida(int tablero[tamanoTablero][tamanoTablero], posicion origen, posicion destino, posicion &piezaCapturada) {
    if (!casillaValida(origen.fila, origen.columna) || 
        !casillaValida(destino.fila, destino.columna)) {
        return false;
    }
    
    if (tablero[destino.fila][destino.columna] != vacia) {
        return false;
    }
    
  if (!casillaJugable(destino.fila, destino.columna)) {
        return false;
    }
    
    int pieza = tablero[origen.fila][origen.columna];
    if (pieza == vacia) {
        return false;
    }
    
    int deltaFila = destino.fila - origen.fila;
    int deltaColumna = destino.columna - origen.columna;
    
    if (abs(deltaFila) != abs(deltaColumna)) {
        return false;
    }
    
    if (abs(deltaFila) != 2) {
        return false;
    }
    
    if (!esDama(pieza)) {
        if (pieza == blanca && deltaFila > 0) {
            return false; // Blanca no puede capturar hacia atrás
        }
        if (pieza == negra && deltaFila < 0) {
            return false; // Negra no puede capturar hacia atrás
        }
    }
    
    piezaCapturada.fila = origen.fila + (deltaFila / 2);
    piezaCapturada.columna = origen.columna + (deltaColumna / 2);
    
    int piezaEnMedio = tablero[piezaCapturada.fila][piezaCapturada.columna];
    if (piezaEnMedio == vacia) {
        return false;
    }
    
    if (!sonEnemigas(pieza, piezaEnMedio)) {
        return false; 
    }
    
    return true;
}

bool puedeCapturarMas(int tablero[tamanoTablero][tamanoTablero], int fila, int columna) {

    int direcciones[4][2] = {
        {-2, -2},  // arrib-izq
        {-2, 2},   // arrib-der
        {2, -2},   // aba-izq
        {2, 2}     // aba.der
    };
    
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
    
    
    if (pieza == blanca || pieza == negra) {
        if (pieza == blanca && fila == 0) {
            tablero[fila][columna] = damaBlanca;
        }
        else if (pieza == negra && fila == tamanoTablero - 1) {
            tablero[fila][columna] = damaNegra;
        }
    }
}
