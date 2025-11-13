# Proyecto-taller-damas-internacionales
# Buitrago Forero Daniel Andres & Acero Cantor Gabriela.

--
## Desarrollos innovadores
## Historial en Archivo CSV
El principal desarrollo innovador que deseamos integrar en nuestra implementación fue lo visto en clase sobre la creación de un archivo CSV. 

Se implementó con el objetivo de en el futuro poder hacer una función para devolver movimientos, sin embargo, no logramos hacerlo de manera viable con nuestro conocimiento.

Lo consideramos necesario para aparte de poder hacer otra función en el futuro con base en el historial, poder lograr que los jugadores hiciesen un análisis de sus jugadas luego de la partida, y hasta en implementaciones más complejas, hacer un modelo de Machine Learning que pueda calificar los movimientos en una escala del 1-10.

Sin embargo, no logramos integrarlo exitosamente en este implemetnación, por lo cual decidimos utilizar una herramienta de LLM (Large Language Model), mejor conocida como Inteligencia Artificial. 

### ¿Por qué utilizarlo?

Se utilizó un LLM debido a la dificultad que tuvimos a la hora de integrar la función de generar un archivo CSV con los movimientos.

El LLM que utilizamos fue (Claude, Sonnet 4.5) como apoyo inicial a la hora de implementar la característica. El contenido generado fue aprobado, revisado e implementado por parte nuestra.

### Documentación de LLM
El prompt que se utilizó dentro de Claude, sonnet 4.5 fue el siguiente: "Estoy realizando un código de damas internacionales en un tablero 10x10, necesito implementar una función la cual registre todos los movimientos en un archivo .csv, tendrás que hacer lo siguiente:
1. Explica como implementarías correctamente esta función dentro de varios archivos .h y .cpp, debido a que estamos manejando modularidad con este programa.
2. Escribe el código que implementarías y explica que hace cada parte del código. 
3. Cumple con estos requisitos sin adentrarte mucho en funciones avanzadas que sean poco legibles.
Si tienes preguntas, hazmelas."

### Implementación del LLM

Las implementaciones que sugirió Claude, sonnet 4.5 fueron los siguientes

1. Utilidades.h
``` 
struct RegistroMovimiento {
    int numeroTurno;
    char jugador[10];      // "Blancas" o "Negras"
    char movimiento[20];   // Ej: "A3-B4" o "C5xE3"
    char tipo[15];         // "Normal", "Captura", "Promocion"
};

// Guarda un movimiento en el archivo CSV
void guardarMovimientoCSV(RegistroMovimiento registro);

// Crea el archivo CSV con encabezados (si no existe)
void inicializarArchivoCSV();

```

2. Utilidades.cpp

```
// ========== AL INICIO DEL ARCHIVO (Includes para CSV) ==========
#include <fstream>  // ← NECESARIO PARA CSV

// ========== SOLO ESTAS DOS FUNCIONES SON PARA CSV ==========

// FUNCIÓN 1: Inicializar archivo CSV
void inicializarArchivoCSV() {
    // Abrir archivo en modo lectura para verificar si existe
    ifstream verificar("historial.csv");
    
    // Si el archivo no existe, crearlo con encabezados
    if (!verificar.good()) {
        verificar.close();
        
        ofstream archivo("historial.csv");
        if (archivo.is_open()) {
            // Escribir encabezados
            archivo << "Turno,Jugador,Movimiento,Tipo\n";
            archivo.close();
        }
    } else {
        verificar.close();
    }
}

// FUNCIÓN 2: Guardar movimiento en CSV

void guardarMovimientoCSV(RegistroMovimiento registro) {
    // Abrir archivo en modo append (agregar al final)
    ofstream archivo("historial.csv", ios::app);
    
    if (archivo.is_open()) {
        // Escribir datos separados por comas
        archivo << registro.numeroTurno << ","
                << registro.jugador << ","
                << registro.movimiento << ","
                << registro.tipo << "\n";
        
        archivo.close();
    } else {
        cout << "Error: No se pudo guardar el movimiento en el historial.\n";
    }
}
```

3. Main.cpp Uso del CSV


```
int main() {
    // ... otras variables ...
    
    // ========== INICIALIZAR CSV ==========
    inicializarArchivoCSV();  // ← Crear el archivo si no existe
    
    // ... resto del código ...
}
```

3. Parte 2, dentro de la función procesarMovimiento() - después de captura

```
// ========== GUARDAR CAPTURA EN CSV ==========
// Crear registro para CSV
RegistroMovimiento reg;
reg.numeroTurno = turnoActual;

if (colorJugador == BLANCA) {
    strcpy(reg.jugador, "Blancas");
} else {
    strcpy(reg.jugador, "Negras");
}

// Crear notación del movimiento (ej: "A3xC5")
char notacionOrigen[5], notacionDestino[5];
posicionANotacion(origen, notacionOrigen);
posicionANotacion(destino, notacionDestino);
strcpy(reg.movimiento, notacionOrigen);
strcat(reg.movimiento, "x");  // 'x' indica captura
strcat(reg.movimiento, notacionDestino);

// Verificar si hubo promoción
int piezaFinal = tablero[destino.fila][destino.columna];
if (esDama(piezaFinal) && !esDama(tablero[origen.fila][origen.columna])) {
    strcpy(reg.tipo, "Captura+Promo");
} else {
    strcpy(reg.tipo, "Captura");
}

guardarMovimientoCSV(reg);  // ← GUARDAR EN CSV

```

3. Dentro de la función procesarMovimiento() - después de un movimiento normal

```
// ========== GUARDAR MOVIMIENTO NORMAL EN CSV ==========
// Crear registro para CSV
RegistroMovimiento reg;
reg.numeroTurno = turnoActual;

if (colorJugador == BLANCA) {
    strcpy(reg.jugador, "Blancas");
} else {
    strcpy(reg.jugador, "Negras");
}

// Crear notación del movimiento (ej: "A3-B4")
char notacionOrigen[5], notacionDestino[5];
posicionANotacion(origen, notacionOrigen);
posicionANotacion(destino, notacionDestino);
strcpy(reg.movimiento, notacionOrigen);
strcat(reg.movimiento, "-");  // '-' indica movimiento normal
strcat(reg.movimiento, notacionDestino);

// Verificar si hubo promoción
int piezaFinal = tablero[destino.fila][destino.columna];

if (esDama(piezaFinal)) {
    strcpy(reg.tipo, "Promocion");
} else {
    strcpy(reg.tipo, "Normal");
}

guardarMovimientoCSV(reg);  // ← GUARDAR EN CSV

```

3. Al final del main.cpp

```
// ========== FIN DEL JUEGO ==========
cout << "\n¡Gracias por jugar!\n";
cout << "El historial de movimientos se guardo en 'historial.csv'\n\n";  // ← Mensaje

return 0;

```

### ¿Como se implementó?

Primero, se analizó lo que propuso el LLM, nos pareció acorde y luego lo implementamos dentro de los archivos que sugirió Claude. Para implementar el código, lo adaptamos a cada parte del archivo, asegurando que si estuviera dentro del "entorno" del código. Luego, hicimos pruebas hasta que nos convenció de la implementación.
