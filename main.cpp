#include <iostream>
#include <cstring>  
#include "tablero.h"
#include "jugadas.h"
#include "utilidades.h"

using namespace std;


bool solicitarPosicion(const char* mensaje, posicion &pos) {
    char entrada[10];
    
    cout << mensaje;
    cin >> entrada;
    
    
    if (!notacionAPosicion(entrada, pos)) {
        cout << "Error: Posicion invalida. Usa formato como A3, B4, etc.\n";
        return false;
    }
    
   
    if (!casillaValida(pos.fila, pos.columna)) {
        cout << "Error: Posicion fuera del tablero.\n";
        return false;
    }
    
    
    if (!casillaJugable(pos.fila, pos.columna)) {
        cout << "Error: Solo puedes mover en casillas oscuras.\n";
        return false;
    }
    
    return true;
}


bool esPiezaDelJugador(int tablero[tamanoTablero][tamanoTablero], posicion pos, int colorJugador) {
    int pieza = tablero[pos.fila][pos.columna];
    
    if (pieza == vacia) {
        cout << "Error: No hay ninguna pieza en esa posicion.\n";
        return false;
    }
    
    if (obtenerColor(pieza) != colorJugador) {
        cout << "Error: Esa pieza no es tuya.\n";
        return false;
    }
    
    return true;
}


bool procesarMovimiento(int tablero[tamanoTablero][tamanoTablero], int colorJugador, 
                       int &turnoActual, bool &capturaRealizada) {
    posicion origen, destino;
    

    if (!solicitarPosicion("Ingresa la posicion de origen (ej: A3): ", origen)) {
        return false;
    }
    
    
    if (!esPiezaDelJugador(tablero, origen, colorJugador)) {
        return false;
    }
    
  
    if (!solicitarPosicion("Ingresa la posicion de destino (ej: B4): ", destino)) {
        return false;
    }


    posicion piezaCapturada;
    if (esCapturaValida(tablero, origen, destino, piezaCapturada)) {
        
        realizarCaptura(tablero, origen, destino, piezaCapturada);
        
        cout << "\n¡Captura realizada!\n";
        capturaRealizada = true;
        
        
        RegistroMovimiento reg;
        reg.numeroTurno = turnoActual;
        
        if (colorJugador == blanca) {
            strcpy(reg.jugador, "Blancas");
        } else {
            strcpy(reg.jugador, "Negras");
        }
        
        
        char notacionOrigen[5], notacionDestino[5];
        posicionANotacion(origen, notacionOrigen);
        posicionANotacion(destino, notacionDestino);
        strcpy(reg.movimiento, notacionOrigen);
        strcat(reg.movimiento, "x");  
        strcat(reg.movimiento, notacionDestino);
        
        
        int piezaFinal = tablero[destino.fila][destino.columna];
        if (esDama(piezaFinal) && !esDama(tablero[origen.fila][origen.columna])) {
            strcpy(reg.tipo, "Captura+Promo");
            cout << "¡Tu pieza se ha convertido en DAMA!\n";
        } else {
            strcpy(reg.tipo, "Captura");
        }
        
        guardarMovimientoCSV(reg);
        
        
        if (puedeCapturarMas(tablero, destino.fila, destino.columna)) {
            cout << "\n¡Puedes seguir capturando!\n";
            mostrarTablero(tablero);
            
            char respuesta;
            cout << "¿Quieres continuar capturando? (s/n): ";
            cin >> respuesta;
            
            if (respuesta == 's' || respuesta == 'S') {
                return procesarMovimiento(tablero, colorJugador, turnoActual, capturaRealizada);
            }
        }
        
        return true;
    }
    
    else if (esMovimientoSimpleValido(tablero, origen, destino)) {
        
        realizarMovimientoSimple(tablero, origen, destino);
        
        cout << "\nMovimiento realizado.\n";
        capturaRealizada = false;
        
        
        RegistroMovimiento reg;
        reg.numeroTurno = turnoActual;

        if (colorJugador == blanca) {
            strcpy(reg.jugador, "Blancas");
        } else {
            strcpy(reg.jugador, "Negras");
        }
        
        
        char notacionOrigen[5], notacionDestino[5];
        posicionANotacion(origen, notacionOrigen);
        posicionANotacion(destino, notacionDestino);
        strcpy(reg.movimiento, notacionOrigen);
        strcat(reg.movimiento, "-");  
        strcat(reg.movimiento, notacionDestino);
        
        
        int piezaFinal = tablero[destino.fila][destino.columna];
        int piezaOriginal = tablero[origen.fila][origen.columna];
        
        if (esDama(piezaFinal)) {
            strcpy(reg.tipo, "Promocion");
            cout << "¡Tu pieza se ha convertido en DAMA!\n";
        } else {
            strcpy(reg.tipo, "Normal");
        }
        
        guardarMovimientoCSV(reg);
        
        return true;
    }
    else {
        cout << "Error: Movimiento invalido.\n";
        return false;
    }
}


int main() {
    
    int tablero[tamanoTablero][tamanoTablero];
    
    int turnoActual = 1;
    int jugadorActual = blanca;  
    bool juegoActivo = true;
    bool capturaRealizada = false;
    
    inicializarArchivoCSV();
    inicializarTablero(tablero);
    
    limpiarPantalla();
    mostrarEncabezado();
    
    cout << "\n¡Bienvenido al juego de Damas Internacionales!\n\n";
    cout << "Instrucciones:\n";
    cout << "- Las blancas (B) juegan primero\n";
    cout << "- Ingresa las posiciones usando notacion algebraica (ej: A3, B4)\n";
    cout << "- Las piezas normales solo pueden moverse hacia adelante\n";
    cout << "- Las damas (W,Q) pueden moverse en cualquier direccion\n";
    cout << "- Captura saltando sobre las piezas enemigas\n";
    cout << "- Gana quien capture todas las piezas del oponente\n\n";
    
    pausar();
    
    
    while (juegoActivo) {
        limpiarPantalla();
        mostrarEncabezado();
        
        
        cout << "\n--- TURNO " << turnoActual << " ---\n";
        
        if (jugadorActual == blanca) {
            cout << "Turno de las BLANCAS (B/W)\n\n";
        } else {
            cout << "Turno de las NEGRAS (N/Q)\n\n";
        }
        
       
        mostrarTablero(tablero);
        
        
        int piezasBlancas = contarPiezas(tablero, blanca);
        int piezasNegras = contarPiezas(tablero, negra);
        
        cout << "Piezas blancas: " << piezasBlancas << " | ";
        cout << "Piezas negras: " << piezasNegras << "\n\n";
        
        
        if (piezasBlancas == 0) {
            mostrarMensaje("¡LAS NEGRAS GANAN!");
            juegoActivo = false;
            cout << "\nPresiona ENTER para continuar...";
            cin.ignore(1000, '\n');  
            cin.get();  
            break;
        }
        
        if (piezasNegras == 0) {
            mostrarMensaje("¡LAS BLANCAS GANAN!");
            juegoActivo = false;
            cout << "\nPresiona ENTER para continuar...";
            cin.ignore(1000, '\n');  
            cin.get();  
            break;
        }
        
        
        bool movimientoExitoso = false;
        
        while (!movimientoExitoso) {
            movimientoExitoso = procesarMovimiento(tablero, jugadorActual, 
                                                  turnoActual, capturaRealizada);
            
            if (!movimientoExitoso) {
                cout << "\nIntenta nuevamente.\n";
                pausar();
                limpiarPantalla();
                mostrarEncabezado();
                mostrarTablero(tablero);
            }
        }
        
        
        if (jugadorActual == blanca) {
            jugadorActual = negra;
        } else {
            jugadorActual = blanca;
            turnoActual++;  
        }
        
        pausar();
    }
    

    cout << "\n¡Gracias por jugar!\n";
    cout << "El historial de movimientos se guardo en 'historial.csv'\n\n";
    cout << "\nPresiona ENTER para continuar...";
    cin.ignore(1000, '\n');  
    cin.get();  
    
    return 0;
}
