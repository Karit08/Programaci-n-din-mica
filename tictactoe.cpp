/**
 * ============================================================================
 * PROYECTO: Juego de Tic Tac Toe (Tres en Raya / Gato)
 * ASIGNATURA: Programacion Dinamica
 * ESTUDIANTE: Karla Itzel Jimenez Molina
 * 
 * DESCRIPCIÓN:
 *   Programa interactivo en C++ para jugar Tic Tac Toe en consola.
 *   Cumple con todos los estándares pedagógicos:
 *   - Modularización mediante funciones.
 *   - Manejo de arreglos bidimensionales (matriz 3x3).
 *   - Validación robusta de entradas de usuario (evita ciclos infinitos).
 *   - Detección precisa de ganador (filas, columnas y diagonales) y empate.
 *   - Mejoras opcionales: Menú interactivo, Modo 1 vs 1, Modo vs CPU
 *     y marcador acumulativo de partidas.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// ============================================================================
// VARIABLES GLOBALES DE ESTADO Y MARCADOR
// ============================================================================
int victoriasJugador1 = 0; // Victorias de 'X'
int victoriasJugador2 = 0; // Victorias de 'O'
int partidasEmpatadas = 0;  // Conteo de empates acumulados

// ============================================================================
// DECLARACIÓN DE PROTOTIPOS DE FUNCIONES
// ============================================================================
void limpiarPantalla();
void pausarConsola();
void inicializarTablero(char tablero[3][3]);
void mostrarTablero(const char tablero[3][3]);
bool casillaDisponible(const char tablero[3][3], int casilla);
bool colocarFicha(char tablero[3][3], int casilla, char ficha);
bool verificarGanador(const char tablero[3][3], char ficha);
bool verificarEmpate(const char tablero[3][3]);
int pedirCasillaValida(const char tablero[3][3], const string &nombreJugador, char ficha);
int jugadaComputadora(const char tablero[3][3]);
void jugarPartida(bool contraCPU);
void mostrarMarcador();
void mostrarInstrucciones();
void mostrarMenu();

// ============================================================================
// FUNCIÓN PRINCIPAL (main)
// ============================================================================
int main() {
    // Semilla para generación de números aleatorios en modo CPU
    srand(static_cast<unsigned int>(time(nullptr)));

    int opcion = 0;

    do {
        mostrarMenu();
        cout << " Seleccione una opcion (1-5): ";

        // Validación de entrada para el menú
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = 0; // Opción inválida para volver a preguntar
        }

        switch (opcion) {
            case 1:
                jugarPartida(false); // Modo 2 Jugadores (Humano vs Humano)
                break;
            case 2:
                jugarPartida(true);  // Modo Humano vs CPU
                break;
            case 3:
                mostrarMarcador();
                break;
            case 4:
                mostrarInstrucciones();
                break;
            case 5:
                limpiarPantalla();
                cout << "\n =====================================================\n";
                cout << "   ¡Gracias por jugar Tic Tac Toe! Hasta la proxima.  \n";
                cout << " =====================================================\n\n";
                break;
            default:
                cout << "\n [ERROR] Opcion no valida. Intente nuevamente.\n";
                pausarConsola();
                break;
        }

    } while (opcion != 5);

    return 0;
}

// ============================================================================
// IMPLEMENTACIÓN DE FUNCIONES DE UTILIDAD Y SISTEMA
// ============================================================================

/**
 * Limpia la pantalla de la consola según el sistema operativo (Windows o POSIX).
 */
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * Detiene la ejecución esperando que el usuario presione Enter para continuar.
 */
void pausarConsola() {
    cout << "\n Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
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

/**
 * Verifica si una casilla (1 al 9) está libre (no ocupada por 'X' ni 'O').
 */
bool casillaDisponible(const char tablero[3][3], int casilla) {
    if (casilla < 1 || casilla > 9) return false;
    int fila = (casilla - 1) / 3;
    int col  = (casilla - 1) % 3;
    return (tablero[fila][col] != 'X' && tablero[fila][col] != 'O');
}

/**
 * Coloca la ficha ('X' u 'O') en la casilla correspondiente si está libre.
 * Retorna true si fue exitosa, o false si la casilla ya estaba ocupada.
 */
bool colocarFicha(char tablero[3][3], int casilla, char ficha) {
    if (!casillaDisponible(tablero, casilla)) return false;
    int fila = (casilla - 1) / 3;
    int col  = (casilla - 1) % 3;
    tablero[fila][col] = ficha;
    return true;
}

/**
 * Revisa exhaustivamente si la ficha indicada ('X' u 'O') ha formado
 * una línea ganadora de 3 elementos en:
 * - 3 Filas horizontales
 * - 3 Columnas verticales
 * - 2 Diagonales (principal y secundaria)
 */
bool verificarGanador(const char tablero[3][3], char ficha) {
    // 1. Revisión de las 3 filas
    for (int i = 0; i < 3; ++i) {
        if (tablero[i][0] == ficha && tablero[i][1] == ficha && tablero[i][2] == ficha) {
            return true;
        }
    }

    // 2. Revisión de las 3 columnas
    for (int j = 0; j < 3; ++j) {
        if (tablero[0][j] == ficha && tablero[1][j] == ficha && tablero[2][j] == ficha) {
            return true;
        }
    }

    // 3. Diagonal principal (superior izquierda a inferior derecha)
    if (tablero[0][0] == ficha && tablero[1][1] == ficha && tablero[2][2] == ficha) {
        return true;
    }

    // 4. Diagonal secundaria (superior derecha a inferior izquierda)
    if (tablero[0][2] == ficha && tablero[1][1] == ficha && tablero[2][0] == ficha) {
        return true;
    }

    return false;
}

/**
 * Verifica si se ha llegado a un empate.
 * Existe empate cuando todas las 9 casillas están ocupadas por 'X' u 'O'
 * y ningún jugador ha ganado.
 */
bool verificarEmpate(const char tablero[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (tablero[i][j] != 'X' && tablero[i][j] != 'O') {
                return false; // Todavía hay al menos una casilla libre
            }
        }
    }
    return true; // No quedan casillas libres
}

/**
 * Solicita de forma segura al usuario el número de casilla,
 * validando que sea numérico, esté en el rango 1-9 y que no esté ocupada.
 */
int pedirCasillaValida(const char tablero[3][3], const string &nombreJugador, char ficha) {
    int casilla = 0;
    while (true) {
        cout << " " << nombreJugador << " [" << ficha << "], elija casilla (1-9): ";
        
        // Validación de tipo de dato (si escriben letras o signos)
        if (!(cin >> casilla)) {
            cin.clear(); // Limpia bandera de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta caracteres sobrantes
            cout << "  -> Entrada invalida. Debe ingresar un numero entero entre 1 y 9.\n";
            continue;
        }

        // Validación de rango
        if (casilla < 1 || casilla > 9) {
            cout << "  -> Numero fuera de rango. Solo se permiten casillas del 1 al 9.\n";
            continue;
        }

        // Validación de ocupación
        if (!casillaDisponible(tablero, casilla)) {
            cout << "  -> Casilla ocupada. Por favor seleccione otra casilla libre.\n";
            continue;
        }

        break; // Entrada completamente válida
    }
    return casilla;
}

/**
 * Algoritmo de Inteligencia Artificial para la Computadora:
 * 1. Prioridad 1: Si la CPU ('O') puede ganar en esta jugada, toma esa casilla.
 * 2. Prioridad 2: Si el humano ('X') está a punto de ganar, bloquea su casilla.
 * 3. Prioridad 3: Toma el centro (casilla 5) si está disponible.
 * 4. Prioridad 4: Elige una casilla libre al azar.
 */
int jugadaComputadora(const char tablero[3][3]) {
    // 1. Revisar si la CPU puede ganar en este turno
    for (int c = 1; c <= 9; ++c) {
        if (casillaDisponible(tablero, c)) {
            char copiaTablero[3][3];
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    copiaTablero[i][j] = tablero[i][j];

            colocarFicha(copiaTablero, c, 'O');
            if (verificarGanador(copiaTablero, 'O')) {
                return c; // Jugada ganadora encontrada
            }
        }
    }

    // 2. Revisar si el Humano ('X') puede ganar y bloquearlo
    for (int c = 1; c <= 9; ++c) {
        if (casillaDisponible(tablero, c)) {
            char copiaTablero[3][3];
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    copiaTablero[i][j] = tablero[i][j];

            colocarFicha(copiaTablero, c, 'X');
            if (verificarGanador(copiaTablero, 'X')) {
                return c; // Bloqueo de victoria rival
            }
        }
    }

    // 3. Tomar el centro estratégico (casilla 5)
    if (casillaDisponible(tablero, 5)) {
        return 5;
    }

    // 4. Si no, elegir una de las casillas libres aleatoriamente
    vector<int> libres;
    for (int c = 1; c <= 9; ++c) {
        if (casillaDisponible(tablero, c)) {
            libres.push_back(c);
        }
    }

    int indiceAleatorio = rand() % libres.size();
    return libres[indiceAleatorio];
}

/**
 * Controla el ciclo completo de una partida, alternando turnos
 * y actualizando el marcador global.
 */
void jugarPartida(bool contraCPU) {
    char tablero[3][3];
    inicializarTablero(tablero);

    string nombreJ1 = "Jugador 1";
    string nombreJ2 = contraCPU ? "Computadora (CPU)" : "Jugador 2";

    int turno = 1; // 1 = Jugador 1 ('X'), 2 = Jugador 2 / CPU ('O')
    bool juegoTerminado = false;

    while (!juegoTerminado) {
        limpiarPantalla();
        cout << " =====================================================\n";
        cout << "   MODO: " << (contraCPU ? "HUMANO VS COMPUTADORA" : "2 JUGADORES (1 VS 1)") << "\n";
        cout << " =====================================================\n";
        mostrarTablero(tablero);

        int casillaElegida = 0;
        char fichaActual = (turno == 1) ? 'X' : 'O';
        string jugadorActual = (turno == 1) ? nombreJ1 : nombreJ2;

        if (turno == 1 || !contraCPU) {
            // Turno de un jugador humano
            casillaElegida = pedirCasillaValida(tablero, jugadorActual, fichaActual);
        } else {
            // Turno de la CPU
            cout << " Turno de la Computadora (CPU) pensando jugada...\n";
            casillaElegida = jugadaComputadora(tablero);
            cout << "  -> La CPU eligio la casilla " << casillaElegida << "\n";
        }

        // Colocar la ficha en el tablero
        colocarFicha(tablero, casillaElegida, fichaActual);

        // 1. Verificar si hay ganador
        if (verificarGanador(tablero, fichaActual)) {
            limpiarPantalla();
            cout << " =====================================================\n";
            cout << "                  ¡FIN DE LA PARTIDA!                 \n";
            cout << " =====================================================\n";
            mostrarTablero(tablero);

            cout << " *****************************************************\n";
            cout << "   ¡FELICIDADES! Ganador: " << jugadorActual << " [" << fichaActual << "]\n";
            cout << " *****************************************************\n";

            if (turno == 1) {
                victoriasJugador1++;
            } else {
                victoriasJugador2++;
            }

            juegoTerminado = true;
        }
        // 2. Verificar si hay empate
        else if (verificarEmpate(tablero)) {
            limpiarPantalla();
            cout << " =====================================================\n";
            cout << "                  ¡FIN DE LA PARTIDA!                 \n";
            cout << " =====================================================\n";
            mostrarTablero(tablero);

            cout << " *****************************************************\n";
            cout << "   ¡EMPATE! El tablero se ha llenado sin vencedor.    \n";
            cout << " *****************************************************\n";

            partidasEmpatadas++;
            juegoTerminado = true;
        }
        // 3. Alternar turno
        else {
            turno = (turno == 1) ? 2 : 1;
        }
    }

    pausarConsola();
}

/**
 * Muestra el marcador acumulativo de partidas ganadas y empatadas.
 */
void mostrarMarcador() {
    limpiarPantalla();
    cout << "\n =====================================================\n";
    cout << "           MARCADOR HISTORICO DE PARTIDAS             \n";
    cout << " =====================================================\n";
    cout << "   Jugador 1 [X]            : " << victoriasJugador1 << " victorias\n";
    cout << "   Jugador 2 / CPU [O]      : " << victoriasJugador2 << " victorias\n";
    cout << "   Empates                  : " << partidasEmpatadas << " partidas\n";
    cout << "   Total partidas jugadas   : " 
         << (victoriasJugador1 + victoriasJugador2 + partidasEmpatadas) << "\n";
    cout << " =====================================================\n";
    pausarConsola();
}

/**
 * Despliega las reglas formales y la forma de jugar.
 */
void mostrarInstrucciones() {
    limpiarPantalla();
    cout << "\n =====================================================\n";
    cout << "            REGLAS E INSTRUCCIONES DE USO             \n";
    cout << " =====================================================\n";
    cout << " 1. El juego se desarrolla en un tablero de 3x3 celdas.\n";
    cout << " 2. Cada celda esta identificada por un numero del 1 al 9:\n\n";
    cout << "        1 | 2 | 3\n";
    cout << "       ---+---+---\n";
    cout << "        4 | 5 | 6\n";
    cout << "       ---+---+---\n";
    cout << "        7 | 8 | 9\n\n";
    cout << " 3. El Jugador 1 siempre utiliza la ficha 'X'.\n";
    cout << " 4. El Jugador 2 (o la Computadora) utiliza la ficha 'O'.\n";
    cout << " 5. Gana el primero que consiga alinear 3 fichas iguales\n";
    cout << "    en horizontal, vertical o diagonal.\n";
    cout << " 6. Si se llenan las 9 casillas sin un ganador, es EMPATE.\n";
    cout << " 7. Las entradas invalidas (letras, fuera de rango o en\n";
    cout << "    casillas ya ocupadas) seran rechazadas por el sistema.\n";
    cout << " =====================================================\n";
    pausarConsola();
}

/**
 * Muestra el menú de navegación principal de la aplicación.
 */
void mostrarMenu() {
    limpiarPantalla();
    cout << "\n =====================================================\n";
    cout << "         PROYECTO: TIC TAC TOE (TRES EN RAYA)         \n";
    cout << " =====================================================\n";
    cout << "   [1] Jugar en Modo 2 Jugadores (Humano vs Humano)   \n";
    cout << "   [2] Jugar contra la Computadora (Humano vs CPU)    \n";
    cout << "   [3] Ver Marcador de Victorias                      \n";
    cout << "   [4] Ver Reglas e Instrucciones                     \n";
    cout << "   [5] Salir del Juego                                \n";
    cout << " =====================================================\n";
}

