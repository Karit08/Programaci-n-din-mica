/**
 * ============================================================================
 * PROYECTO: Juego de Tic Tac Toe (Tres en Raya / Gato)
 * ASIGNATURA: Estructuras de Datos / Programacion Dinamica
 * ESTUDIANTE: Karla Itzel Jimenez Molina
 * 
 * DESCRIPCIÓN:
 *   Estructura modular para dos jugadores con validación robusta de entradas.
 *   Modularización del flujo de juego en funciones separadas y limpieza de pantalla.
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>

using namespace std;

// Prototipos de funciones
void limpiarPantalla();
void pausarConsola();
void inicializarTablero(char tablero[3][3]);
void mostrarTablero(const char tablero[3][3]);
bool casillaDisponible(const char tablero[3][3], int casilla);
bool colocarFicha(char tablero[3][3], int casilla, char ficha);
bool verificarGanador(const char tablero[3][3], char ficha);
bool verificarEmpate(const char tablero[3][3]);
int pedirCasillaValida(const char tablero[3][3], const string &nombreJugador, char ficha);
void jugarPartida();

int main() {
    char repetir = 's';
    while (repetir == 's' || repetir == 'S') {
        jugarPartida();
        cout << "\n ¿Desea jugar otra partida? (s/n): ";
        cin >> repetir;
    }
    cout << "\n ¡Gracias por jugar!\n";
    return 0;
}

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausarConsola() {
    cout << "\n Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
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

bool verificarGanador(const char tablero[3][3], char ficha) {
    for (int i = 0; i < 3; ++i) {
        if (tablero[i][0] == ficha && tablero[i][1] == ficha && tablero[i][2] == ficha) return true;
    }
    for (int j = 0; j < 3; ++j) {
        if (tablero[0][j] == ficha && tablero[1][j] == ficha && tablero[2][j] == ficha) return true;
    }
    if (tablero[0][0] == ficha && tablero[1][1] == ficha && tablero[2][2] == ficha) return true;
    if (tablero[0][2] == ficha && tablero[1][1] == ficha && tablero[2][0] == ficha) return true;
    return false;
}

bool verificarEmpate(const char tablero[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (tablero[i][j] != 'X' && tablero[i][j] != 'O') return false;
        }
    }
    return true;
}

int pedirCasillaValida(const char tablero[3][3], const string &nombreJugador, char ficha) {
    int casilla = 0;
    while (true) {
        cout << " " << nombreJugador << " [" << ficha << "], elija casilla (1-9): ";
        
        if (!(cin >> casilla)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  -> Entrada invalida. Debe ingresar un numero entero entre 1 y 9.\n";
            continue;
        }

        if (casilla < 1 || casilla > 9) {
            cout << "  -> Numero fuera de rango. Solo se permiten casillas del 1 al 9.\n";
            continue;
        }

        if (!casillaDisponible(tablero, casilla)) {
            cout << "  -> Casilla ocupada. Por favor seleccione otra casilla libre.\n";
            continue;
        }

        break;
    }
    return casilla;
}

void jugarPartida() {
    char tablero[3][3];
    inicializarTablero(tablero);

    string nombreJ1 = "Jugador 1";
    string nombreJ2 = "Jugador 2";
    int turno = 1;
    bool juegoTerminado = false;

    while (!juegoTerminado) {
        limpiarPantalla();
        cout << " =====================================================\n";
        cout << "             PARTIDA: MODO 2 JUGADORES                \n";
        cout << " =====================================================\n";
        mostrarTablero(tablero);

        char fichaActual = (turno == 1) ? 'X' : 'O';
        string jugadorActual = (turno == 1) ? nombreJ1 : nombreJ2;

        int casilla = pedirCasillaValida(tablero, jugadorActual, fichaActual);
        colocarFicha(tablero, casilla, fichaActual);

        if (verificarGanador(tablero, fichaActual)) {
            limpiarPantalla();
            mostrarTablero(tablero);
            cout << " *****************************************************\n";
            cout << "   ¡FELICIDADES! Ha ganado " << jugadorActual << " [" << fichaActual << "]\n";
            cout << " *****************************************************\n";
            juegoTerminado = true;
        } else if (verificarEmpate(tablero)) {
            limpiarPantalla();
            mostrarTablero(tablero);
            cout << " *****************************************************\n";
            cout << "   ¡EMPATE! El tablero esta lleno sin ganador.        \n";
            cout << " *****************************************************\n";
            juegoTerminado = true;
        } else {
            turno = (turno == 1) ? 2 : 1;
        }
    }
}
