#ifndef JUGADAS_H
#define JUGADAS_H

#include "tablero.h"


bool esMovimientoSimpleValido(int tablero[tamanoTablero][tamanoTablero], posicion origen, posicion destino);
bool esCapturaValida(int tablero[tamanoTablero][tamanoTablero], posicion origen, posicion destino, posicion &piezaCapturada);
bool puedeCapturarMas(int tablero[tamanoTablero][tamanoTablero], int fila, int columna);
bool sonEnemigas(int pieza1, int pieza2);
int obtenerColor(int pieza);
bool esDama(int pieza);

void realizarMovimientoSimple(int tablero[tamanoTablero][tamanoTablero], posicion origen, posicion destino);
void realizarCaptura(int tablero[tamanoTablero][tamanoTablero], posicion origen, posicion destino, posicion piezaCapturada);
void verificarPromocion(int tablero[tamanoTablero][tamanoTablero], int fila, int columna);

#endif
