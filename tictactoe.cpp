/**
 * ============================================================================
 * PROYECTO: Juego de Tic Tac Toe (Tres en Raya / Gato)
 * ASIGNATURA: Estructuras de Datos / Programacion Dinamica
 * ESTUDIANTE: Karla Itzel Jimenez Molina
 * 
 * DESCRIPCIÓN:
 *   Estructura modular para dos jugadores por turnos en consola.
 *   Permite ingresar casillas del 1 al 9 y colocar las fichas 'X' y 'O'.
 * ============================================================================
 */

#include <iostream>

using namespace std;

// Prototipos de funciones
void inicializarTablero(char tablero[3][3]);
void mostrarTablero(const char tablero[3][3]);
bool casillaDisponible(const char tablero[3][3], int casilla);
bool colocarFicha(char tablero[3][3], int casilla, char ficha);

int main() {
    char tablero[3][3];
    inicializarTablero(tablero);

    cout << "=== TIC TAC TOE (TRES EN RAYA) - MODO 2 JUGADORES ===\n";

    int turno = 1; // 1: Jugador 1 ('X'), 2: Jugador 2 ('O')
    int jugadas = 0;

    while (jugadas < 9) {
        mostrarTablero(tablero);

        char fichaActual = (turno == 1) ? 'X' : 'O';
        int casilla = 0;

        cout << "Jugador " << turno << " [" << fichaActual << "], elija casilla (1-9): ";
        cin >> casilla;

        if (casilla < 1 || casilla > 9) {
            cout << "Casilla fuera de rango. Debe ser entre 1 y 9.\n";
            continue;
        }

        if (!colocarFicha(tablero, casilla, fichaActual)) {
            cout << "Casilla ocupada. Elija otra.\n";
            continue;
        }

        jugadas++;
        turno = (turno == 1) ? 2 : 1;
    }

    mostrarTablero(tablero);
    cout << "Fin del juego por limite de jugadas.\n";

    return 0;
}

void inicializarTablero(char tablero[3][3]) {
    char contador = '1';
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            tablero[i][j] = contador++;
        }
    }
}

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

bool casillaDisponible(const char tablero[3][3], int casilla) {
    if (casilla < 1 || casilla > 9) return false;
    int fila = (casilla - 1) / 3;
    int col  = (casilla - 1) % 3;
    return (tablero[fila][col] != 'X' && tablero[fila][col] != 'O');
}

bool colocarFicha(char tablero[3][3], int casilla, char ficha) {
    if (!casillaDisponible(tablero, casilla)) return false;
    int fila = (casilla - 1) / 3;
    int col  = (casilla - 1) % 3;
    tablero[fila][col] = ficha;
    return true;
}
