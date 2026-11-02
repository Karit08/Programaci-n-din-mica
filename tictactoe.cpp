/**
 * ============================================================================
 * PROYECTO: Juego de Tic Tac Toe (Tres en Raya / Gato)
 * ASIGNATURA: Estructuras de Datos / Programacion Dinamica
 * ESTUDIANTE: Karla Itzel Jimenez Molina
 * 
 * DESCRIPCIÓN:
 *   Estructura inicial del juego de Tic Tac Toe en C++.
 *   Representación del tablero mediante una matriz de 3x3 e inicialización.
 * ============================================================================
 */

#include <iostream>

using namespace std;

// Prototipos de funciones
void inicializarTablero(char tablero[3][3]);
void mostrarTablero(const char tablero[3][3]);

int main() {
    char tablero[3][3];

    cout << "=== TIC TAC TOE (TRES EN RAYA) ===\n\n";

    inicializarTablero(tablero);
    mostrarTablero(tablero);

    return 0;
}

/**
 * Inicializa la matriz del tablero con números del '1' al '9'
 * que indican visualmente la posición al jugador.
 */
void inicializarTablero(char tablero[3][3]) {
    char contador = '1';
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            tablero[i][j] = contador++;
        }
    }
}

/**
 * Dibuja el tablero en consola con bordes y formato visual claro.
 */
void mostrarTablero(const char tablero[3][3]) {
    cout << "\n";
    cout << "             TABLERO ACTUAL        \n";
    cout << "        +-------+-------+-------+  \n";
    for (int i = 0; i < 3; ++i) {
        cout << "        |   " << tablero[i][0]
             << "   |   " << tablero[i][1]
             << "   |   " << tablero[i][2] << "   |  \n";
        if (i < 2) {
            cout << "        +-------+-------+-------+  \n";
        }
    }
    cout << "        +-------+-------+-------+  \n\n";
}
