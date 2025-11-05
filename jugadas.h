#ifndef JUGADAS_H
#define JUGADAS_H

#include "tablero.h"


bool esMovimientoSimpleValido(int tablero[TAMANIO][TAMANIO], Posicion origen, Posicion destino);
bool esCapturaValida(int tablero[TAMANIO][TAMANIO], Posicion origen, Posicion destino, Posicion &piezaCapturada);
bool puedeCapturarMas(int tablero[TAMANIO][TAMANIO], int fila, int columna);
bool sonEnemigas(int pieza1, int pieza2);
int obtenerColor(int pieza);
bool esDama(int pieza);

void realizarMovimientoSimple(int tablero[TAMANIO][TAMANIO], Posicion origen, Posicion destino);
void realizarCaptura(int tablero[TAMANIO][TAMANIO], Posicion origen, Posicion destino, Posicion piezaCapturada);
void verificarPromocion(int tablero[TAMANIO][TAMANIO], int fila, int columna);

#endif
