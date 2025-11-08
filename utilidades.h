#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "tablero.h"

struct RegistroMovimiento {
    int numeroTurno;
    char jugador[10];      
    char movimiento[20];   
    char tipo[15];         
};


int letraAColumna(char letra);

char columnaALetra(int columna);

bool notacionAPosicion(const char* notacion, Posicion &pos);

void posicionANotacion(Posicion pos, char* notacion);

void limpiarPantalla();

void pausar();

void mostrarMensaje(const char* mensaje);


void mostrarEncabezado();



void guardarMovimientoCSV(RegistroMovimiento registro);

void inicializarArchivoCSV();

#endif
