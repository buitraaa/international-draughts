#ifndef TABLERO_H
#define TABLERO_H

const int tamanoTablero = 10;

const int vacia = 0;
const int blanca = 1;
const int negra = 2;
const int damaBlanca = 3;
const int damaNegra = 4;

struct posicion{
  int fila;
  int columna;
};

void inicializarTablero(int tablero[tamanoTablero][tamanoTablero]);
void mostrarTablero(int tablero[tamanoTablero][tamanoTablero]);
int obtenerPosPieza(int tablero[tamanoTablero][tamanoTablero]);
void colocarPieza(int tablero[tamanoTablero][tamanoTablero], int fila, int columna, int pieza);
bool casillaValida(int fila, int columna);
int casillaJugable(int fila, int columna);
int contarPiezas(int tablero[tamanoTablero][tamanoTablero], int color);

#endif




