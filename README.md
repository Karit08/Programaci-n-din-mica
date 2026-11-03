# 📚 Mini Proyectos de Programación Dinámica y Estructuras de Datos

Repositorio oficial para la entrega y seguimiento del desarrollo de los **Mini Proyectos** correspondientes a la asignatura de Programación Dinámica / Estructuras de Datos.

---

## 🎮 1. Proyecto: Tic Tac Toe (Tres en Raya / Gato)

- **Estudiante:** Karla Itzel Jimenez Molina
- **Lenguaje:** C++ (Estándar C++11 o superior)
- **Archivo fuente principal:** [`tictactoe.cpp`](file:///Users/karlajimenez/Desktop/Programacion%20D%C3%ADnamica/tictactoe.cpp)

---

## 📌 Descripción General del Proyecto

Este mini proyecto implementa el clásico juego de **Tic Tac Toe** (Tres en Raya) en consola, diseñado y desarrollado aplicando buenas prácticas de ingeniería de software, arquitectura modular basada en funciones, representación de estado mediante matrices bidimensionales y algoritmos de control de flujo.

El sistema ofrece una experiencia completa con dos modalidades de juego (1 vs 1 local y Humano vs Computadora), gestión de marcador de partidas, menú dinámico e interactivo, y prevención total de errores de ejecución mediante validación exhaustiva de entradas.

---

## 📋 Cumplimiento de Criterios de Evaluación

### 1. Funcionalidad Básica
- ✅ **Juego entre dos usuarios:** Permite enfrentamientos locales entre dos jugadores en turnos alternados (`'X'` y `'O'`).
- ✅ **Detección precisa de ganador o empate:** El algoritmo evalúa después de cada movimiento todas las combinaciones de victoria (3 filas, 3 columnas y 2 diagonales) o declara empate si las 9 celdas se agotan sin vencedor.
- ✅ **Validación estricta de entradas:**
  - Control de tipo de dato: descarta letras o símbolos sin entrar en ciclo infinito mediante `cin.clear()` y `cin.ignore()`.
  - Control de rango: solo admite casillas numéricas del 1 al 9.
  - Control de ocupación: impide sobreescribir celdas ocupadas.
- ✅ **Ejecución sin errores:** Código probado y compilado con banderas estrictas (`-Wall -Wextra`), garantizando cero advertencias y sin fugas de memoria.

### 2. Uso de Estructuras de Programación
- ✅ **Modularización:** Lógica separada en funciones independientes con responsabilidad única (`mostrarTablero`, `casillaDisponible`, `colocarFicha`, `verificarGanador`, `verificarEmpate`, etc.).
- ✅ **Arreglos / Matrices:** El tablero se modela con una matriz bidimensional `char tablero[3][3]`.
- ✅ **Estructuras de control:** Uso adecuado de bucles (`do-while`, `while`, `for`) y ramificaciones condicionales (`switch-case`, `if-else`).

### 3. Calidad del Código
- ✅ **Legibilidad y estilo:** Código limpio, formateado uniformemente e intuitivo.
- ✅ **Nombres significativos:** Identificadores autodescriptivos en español (`victoriasJugador1`, `casillaDisponible`, `jugadaComputadora`).
- ✅ **Comentarios y documentación técnica:** Cabeceras y bloques descriptivos que explican el propósito de cada sección y algoritmo.

### 4. Innovación y Mejoras Opcionales
- 🌟 **Menú Principal Interactivo:** Menú de opciones (1 al 5) para iniciar partidas, consultar estadísticas o salir limpiamente.
- 🌟 **Modo contra la Computadora (IA Táctica):**
  1. *Estrategia ganadora:* Si la CPU puede completar 3 en línea en el turno, realiza la jugada ganadora.
  2. *Estrategia de bloqueo:* Si el jugador rival está a punto de ganar, la CPU bloquea su casilla.
  3. *Control posicional:* Intenta asegurar el centro (casilla 5).
  4. *Exploración:* Elige casillas disponibles aleatoriamente.
- 🌟 **Marcador Histórico Acumulado:** Conteo persistente de victorias del Jugador 1, Jugador 2 / CPU y empates en la sesión.
- 🌟 **Multiplataforma:** Detección automática del sistema operativo para limpieza de consola (`cls` en Windows / `clear` en macOS/Linux).

---

## 🗺️ Mapa del Tablero

Cada celda se selecciona numéricamente según la siguiente distribución:

```text
       +-------+-------+-------+
       |   1   |   2   |   3   |
       +-------+-------+-------+
       |   4   |   5   |   6   |
       +-------+-------+-------+
       |   7   |   8   |   9   |
       +-------+-------+-------+
```

---

## ⚙️ Instrucciones de Compilación y Ejecución

### Requisitos Previos
Tener instalado un compilador moderno de C++ (`g++` o `clang++`).

### 🍎 En macOS / 🐧 En Linux

1. Abrir la terminal en la carpeta del proyecto:
   ```bash
   cd "Programacion Dínamica"
   ```
2. Compilar el programa:
   ```bash
   g++ -std=c++11 -Wall -Wextra tictactoe.cpp -o tictactoe
   ```
3. Ejecutar:
   ```bash
   ./tictactoe
   ```

### 🪟 En Windows (MinGW / CMD / PowerShell)

1. Abrir la consola en la carpeta del proyecto.
2. Compilar:
   ```cmd
   g++ -std=c++11 tictactoe.cpp -o tictactoe.exe
   ```
3. Ejecutar:
   ```cmd
   tictactoe.exe
   ```

---

## 🕹️ Guía de Uso

1. Al iniciar la aplicación se mostrará el menú principal:
   - `[1]` Iniciar partida de dos jugadores humanos por turnos.
   - `[2]` Iniciar partida contra la Inteligencia Artificial.
   - `[3]` Consultar el marcador acumulativo de partidas ganadas y empates.
   - `[4]` Desplegar las reglas oficiales e instrucciones detalladas.
   - `[5]` Salir del sistema.
2. En cada turno, ingrese el número (1-9) de la casilla deseada y presione <kbd>Enter</kbd>.
3. El sistema validará su elección; si la casilla está ocupada o el valor es inválido, le solicitará una nueva opción sin interrumpir el flujo.
4. Al culminar la partida, se indicará el resultado y se actualizará automáticamente el marcador histórico.

---

## 📁 Estructura del Repositorio

```text
Programacion Dinamica/
├── .gitignore          # Exclusión de binarios y temporales
├── README.md           # Documentación general y del Proyecto 1
└── tictactoe.cpp       # Código fuente completo de Tic Tac Toe
```

---

## 👤 Autor

- **Karla Itzel Jimenez Molina**
- Estudiante de Programación Dinámica / Estructuras de Datos
