# 📚 ANÁLISIS COMPLETO DEL PROYECTO 3E252

## 🎯 Resumen General

Proyecto educativo desarrollado en **C++** con **SFML** (Simple and Fast Multimedia Library) y **Box2D** para física. El objetivo es crear ejemplos interactivos que demuestren conceptos de programación, gráficos 2D, física, audio y desarrollo de juegos.

**Ubicación:** `c:\Users\mrcan\OneDrive\Documentos\GitHub\3E252`

**Desarrollo:** MinGW64 + Msys2 + Visual Studio Code

---

## 📁 Estructura del Proyecto

```
3E252/
├── README.md                 (Descripción básica)
├── makefile                  (Build del root)
├── assets/                   (Recursos)
│   ├── fonts/               (Tipografías)
│   └── images/              (Imágenes)
│
├── bin/                      (Binarios compilados)
│   ├── 00_Ventana.exe       (✅ 135 KB - Ventana básica)
│   ├── 01_Imagen.exe        (✅ 146 KB - Carga de imágenes)
│   ├── 02_Sprite.exe        (✅ 149 KB - Sprites)
│   ├── 03_0_Teclado.exe     (✅ 138 KB - Input de teclado)
│   ├── 03_1_Pikachu.exe     (✅ 155 KB - Pikachu interactivo)
│   ├── 04_Texto.exe         (✅ 152 KB - Texto y fuentes)
│   ├── 05_Audio.exe         (✅ 143 KB - Audio/música)
│   ├── 06_Primitivas.exe    (✅ 143 KB - Formas geométricas)
│   ├── 07_Fisica.exe        (✅ 144 KB - Box2D physics)
│   ├── 08_Tron.exe          (✅ 202 KB - Juego Tron)
│   ├── 09_Vaqueros.exe      (✅ 284 KB - Juego de vaqueros)
│   ├── 010_Textovaq.exe     (✅ 169 KB - Animaciones de texto)
│   └── 011_AudioVaq.exe     (✅ 164 KB - Sistema de audio avanzado)
│
├── docs/                     (Documentación)
│   ├── herramientas.md       (Instalación de herramientas)
│   ├── librerias.md          (Instalación de librerías SFML + Box2D)
│   ├── extensiones.md        (Extensiones de VSCode)
│   ├── fork.md               (Clonar repositorio)
│   ├── path.md               (Variables de entorno)
│   └── images/               (Imágenes de ayuda)
│
├── include/                  (Headers reutilizables)
│   ├── Ball.hpp              (Clase Ball para física con Box2D)
│   ├── GameWindow.hpp        (Wrapper de sf::RenderWindow)
│   ├── Ground.hpp            (Clase Ground para físicas)
│   ├── PhysicsSpace.hpp      (Gestión de espacio físico)
│   ├── Foco.hpp              (Componente Foco)
│   ├── EstadoFoco.hpp        (Estado de Foco)
│   └── SerieNavidad.hpp      (Componentes temáticos)
│
├── src/                      (Archivos fuente)
│   ├── 00_Ventana.cpp        (753 bytes - Ejemplo inicial)
│   ├── 01_Imagen.cpp         (1.0 KB - Carga de imágenes)
│   ├── 02_Sprite.cpp         (1.4 KB - Trabajo con sprites)
│   ├── 03_0_Teclado.cpp      (1.4 KB - Input de teclado)
│   ├── 03_1_Pikachu.cpp      (2.5 KB - Sprite interactivo)
│   ├── 04_Texto.cpp          (1.3 KB - Rendering de texto)
│   ├── 05_Audio.cpp          (921 bytes - Música básica)
│   ├── 06_Primitivas.cpp     (1.1 KB - Formas geométricas)
│   ├── 07_Fisica.cpp         (3.8 KB - Box2D v3 API)
│   ├── 08_Tron.cpp           (5.3 KB - Juego completo)
│   ├── 09_Vaqueros.cpp       (29.7 KB - Juego avanzado) ⭐
│   ├── 010_Textovaq.cpp      (5.2 KB - Animaciones texto)
│   ├── 010_Textovaq_README.md (Documentación)
│   └── 011_AudioVaq.cpp      (7.1 KB - Audio avanzado) ⭐
│
├── EjemplosJuego/            (Subcarpeta de ejemplos)
│   ├── makefile              (Build del proyecto)
│   ├── README.md             (Instrucciones principales)
│   ├── TODO.md               (Tasks pendientes)
│   ├── LICENSE               (Licencia)
│   ├── assets/
│   │   ├── fonts/Ring.ttf    (Fuente western)
│   │   ├── music/            (Archivos de audio OGG)
│   │   └── images/           (Sprites y assets)
│   ├── bin/                  (Ejecutables compilados)
│   ├── docs/                 (Documentación técnica)
│   ├── include/              (Headers del proyecto)
│   └── src/                  (Archivos fuente principales)
│
├── Programacion/             (Ejemplos de programación básica)
│   └── src/
│       ├── animacion.cpp
│       ├── ejemplo.cpp
│       ├── main.cpp
│       └── punteros.cpp
│
└── FTXUI/                    (Librería de UI en terminal)
```

---

## 🔧 Herramientas y Dependencias

### Instaladas:
- **MinGW64** + **Msys2** - Compilador C++
- **SFML 2.x** - Gráficos, ventanas, audio
  - `libsfml-graphics`
  - `libsfml-window`
  - `libsfml-system`
  - `libsfml-audio`
- **Box2D 3.0+** - Motor de física 2D (API basada en funciones, no clases)
- **Visual Studio Code** - Editor
- **Git** - Control de versiones
- **GNU Make** - Sistema de compilación

### Comandos de Instalación:
```bash
# Herramientas base
pacman -S --needed base-devel mingw-w64-x86_64-toolchain

# SFML
pacman -S mingw-w64-x86_64-sfml

# Box2D
pacman -S mingw-w64-x86_64-box2d
```

### Variables de Entorno (PATH):
- `C:\msys64\mingw64\bin`
- `C:\msys64\usr\bin`

---

## 📝 Ejemplos Incluidos (12 Programas)

### Nivel 1: Conceptos Básicos

#### ✅ 00_Ventana.cpp (753 bytes)
**Propósito:** Hola mundo de SFML
```cpp
- Crea una ventana de 200x200
- Dibuja un círculo verde
- Loop básico de eventos
```

#### ✅ 01_Imagen.cpp (1.0 KB)
**Propósito:** Carga y visualización de imágenes
```cpp
- Carga texturas desde archivos
- Las aplica a sprites
- Muestra en pantalla
```

#### ✅ 02_Sprite.cpp (1.4 KB)
**Propósito:** Trabajo avanzado con sprites
```cpp
- Posicionamiento de sprites
- Escalado y rotación
- Animación de spritesheet
```

#### ✅ 03_0_Teclado.cpp (1.4 KB)
**Propósito:** Input de teclado
```cpp
- Detección de teclas presionadas
- Movimiento de sprites con WASD/Arrows
- Control en tiempo real
```

#### ✅ 03_1_Pikachu.cpp (2.5 KB)
**Propósito:** Sprite interactivo Pikachu
```cpp
- Sprite animado de Pikachu
- Responde a entrada del usuario
- Movimiento suave
```

#### ✅ 04_Texto.cpp (1.3 KB)
**Propósito:** Rendering de texto
```cpp
- Carga de fuentes (TTF)
- Renderización de texto
- Diferentes colores y tamaños
```

#### ✅ 06_Primitivas.cpp (1.1 KB)
**Propósito:** Formas geométricas
```cpp
- RectangleShape
- CircleShape
- ConvexShape
- LineShape
```

### Nivel 2: Audio y Animación

#### ✅ 05_Audio.cpp (921 bytes)
**Propósito:** Reproducción de música
```cpp
- Carga archivo OGG
- Reproduce música
- Detección de fin de música
```

#### ✅ 010_Textovaq.cpp (5.2 KB)
**Propósito:** Animaciones de texto avanzadas
```cpp
- Cambio de colores cíclico
- Escala dinámica
- Rotación de texto
- Tema western/vaquero
```

#### ✅ 011_AudioVaq.cpp (7.1 KB) ⭐
**Propósito:** Sistema de audio completo con máquina de estados
```cpp
- Estados: MENU → PLAYING → GAME_OVER
- Música de menú (looping)
- Música de juego (looping)
- Transiciones de estado
- Manejo de archivos no encontrados

MÚSICA REQUERIDA:
- ./assets/music/menu_vaqueros.ogg
- ./assets/music/game_vaqueros.ogg
```

### Nivel 3: Física 2D

#### ✅ 07_Fisica.cpp (3.8 KB)
**Propósito:** Motor de física Box2D v3
```cpp
- Creación de mundo físico
- Cuerpos dinámicos y estáticos
- Formas: círculos, polígonos
- Detección de colisiones
- Aplicación de fuerzas

IMPORTANTE: Box2D v3 API
- Usa funciones globales, no clases
- b2CreateWorld(), b2CreateBody(), etc.
- Actualización con b2World_Step()
```

### Nivel 4: Juegos Completos

#### ✅ 08_Tron.cpp (5.3 KB)
**Propósito:** Juego Tron clásico
```cpp
Características:
- Juego clásico de motos Tron
- Movimiento de dos jugadores
- Colisión con paredes y líneas
- Victoria/derrota
- Score tracking
```

#### ✅ 09_Vaqueros.cpp (29.7 KB) ⭐⭐⭐
**Propósito:** Juego completo de duelo de vaqueros

**CARACTERÍSTICAS PRINCIPALES:**

**Modos de Juego:**
1. **PvP** - Dos jugadores humanos
2. **VS_BOT** - Un jugador vs IA

**Estados del Juego:**
- MODE_SELECT → DIFFICULTY_SELECT (si vs Bot) → NAME_INPUT → PLAYING → GAME_OVER

**Sistema de Dificultad (IA):**
- **EASY:** Velocidad 0.4x, dispara cada 2.5s
- **MEDIUM:** Velocidad 0.8x, dispara cada 1.5s
- **HARD:** Velocidad 1.0x, dispara cada 0.8s

**Mecánicas:**
- **Salud:** 100 HP por vaquero
- **Daño:** -20 HP por impacto de bala
- **Balas:** Radio 2.0 píxeles, velocidad 500 unidades/seg
- **Movimiento:** 300 unidades/seg en 8 direcciones
- **Zona de juego:** Cada vaquero en su mitad (izq/der)

**Gráficos Custom:**
```cpp
Cada vaquero tiene:
- Cabeza (círculo piel)
- Cuerpo (rectángulo rojo/azul)
- Brazo (línea diagonal)
- Pistola (amarilla, orientada según jugador)
- Sombrero (rectángulo negro)
- Barra de vida (verde → rojo)
```

**Interfaz:**
- Fuente: Ring.ttf (western style)
- Selección de modo (1 o 2)
- Selección de dificultad (1-3)
- Entrada de nombres
- HUD con vidas
- Pantalla de victoria

**Controles:**
```
JUGADOR 1 (Rojo):
- A/D: Mover izquierda/derecha
- W/S: Mover arriba/abajo
- SPACE: Disparar

JUGADOR 2 (Azul - Solo PvP):
- Flechas: Mover
- ENTER: Disparar

BOT (Vs Bot):
- Auto-targeting
- Movimiento automático
```

**Audio Integration:**
```cpp
// Música de menú (looping)
sf::Music menuMusic;
menuMusic.openFromFile("./assets/music/menu_vaqueros.ogg");
menuMusic.setLoop(true);
menuMusic.setVolume(75);

// Música de juego (looping)
sf::Music gameMusic;
gameMusic.openFromFile("./assets/music/game_vaqueros.ogg");
gameMusic.setLoop(true);
gameMusic.setVolume(75);

// Transiciones automáticas:
// MODE_SELECT → menuMusic.play()
// NAME_INPUT → mantiene menuMusic
// PLAYING → gameMusic.play(), menuMusic.stop()
// GAME_OVER → menuMusic.play(), gameMusic.stop()
```

---

## 🛠️ Sistema de Compilación

### Makefile
```makefile
SRC_DIR := src
BIN_DIR := bin
SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d

$(BIN_DIR)/%.exe: $(SRC_DIR)/%.cpp
	g++ $< -o $@ $(SFML) -Iinclude

all: $(EXE_FILES)  # Compila todos los .cpp
clean:             # Elimina todos los .exe
run%:              # Ejecuta programa específico
```

### Comandos:
```bash
# Compilar todo
make all

# Compilar un específico
make 09_Vaqueros

# Ejecutar un ejemplo
make run09_Vaqueros
```

---

## 📊 Arquitectura del Código

### Clase Cowboy (09_Vaqueros.cpp)
```cpp
class Cowboy {
    sf::Vector2f position;      // Posición
    int id;                     // 1 o 2
    int health;                 // 0-100
    string name;                // Nombre del jugador
    sf::Vector2f velocity;      // Velocidad
    sf::RectangleShape healthBar;      // Barra visual
    sf::RectangleShape healthBarBg;    // Fondo barra
    
    void update(float dt);              // Actualizar posición
    sf::FloatRect getBounds();          // Colisiones
    sf::Vector2f getBulletSpawnPos();   // Punto de disparo
    void draw(sf::RenderWindow& w);     // Renderizado custom
};
```

### Struct Bullet
```cpp
struct Bullet {
    sf::CircleShape shape;      // Forma visual (radio 2.0)
    sf::Vector2f velocity;      // Dirección y velocidad
    int owner;                  // Jugador 1 o 2 (amarillo/cian)
};
```

### Máquina de Estados
```cpp
enum GameState {
    MODE_SELECT,       // Seleccionar PvP o vs Bot
    DIFFICULTY_SELECT, // Seleccionar dificultad IA
    NAME_INPUT,        // Entrada de nombres
    PLAYING,           // Juego activo
    GAME_OVER          // Pantalla de victoria
};
```

---

## 📚 Headers Reutilizables

### Ball.hpp
Clase para objetos circulares con física Box2D
```cpp
Ball(cpSpace*, float radius, float mass, cpVect position)
sf::CircleShape GetShape()
cpBody* getBody()
```

### GameWindow.hpp
Wrapper de sf::RenderWindow
```cpp
GameWindow(int width, int height, string title)
bool isOpen()
void clear(), display()
void draw(sf::Shape&)
sf::Vector2u getSize()
```

### Ground.hpp, PhysicsSpace.hpp
Componentes para sistemas de física

---

## 🎨 Assets Necesarios

### Fuentes:
- `assets/fonts/Ring.ttf` - Fuente western (instalada ✅)

### Música:
- `assets/music/menu_vaqueros.ogg` - ⚠️ **REQUERIDA**
- `assets/music/game_vaqueros.ogg` - ⚠️ **REQUERIDA**

### Imágenes:
- Varios sprites en `assets/images/`

---

## 🐛 Problemas Resueltos

### ✅ Box2D v2 → v3 Migration (07_Fisica.cpp)
**Problema:** Código antiguo usaba API v2 basada en clases
**Solución:** Migrado a v3 con funciones globales
- `b2World_Step()` en lugar de `world->Step()`
- `b2CreateBody()` en lugar de `new b2Body()`
- `b2Body_ApplyLinearImpulse()` para aplicar fuerzas

### ✅ Blank Menu Screen (09_Vaqueros.cpp)
**Problema:** MODE_SELECT no se renderizaba
**Solución:** Agregado `window.display()` al final de cada estado

### ✅ Audio Integration (09_Vaqueros.cpp)
**Estado:** ✅ **COMPLETADO**
- Audio include: `#include <SFML/Audio.hpp>`
- Música de menú: Cargada y configurada
- Música de juego: Cargada y configurada
- Transiciones de estado: ✅ Implementadas
  - MODE_SELECT: menuMusic.play()
  - PLAYING: gameMusic.play(), menuMusic.stop()
  - GAME_OVER: menuMusic.play(), gameMusic.stop()

---

## 🚀 Cómo Ejecutar

### Opción 1: Terminal VSCode
```bash
# En la terminal VSCode dentro del directorio EjemplosJuego/
make run09_Vaqueros    # Ejecuta el juego de vaqueros
make run011_AudioVaq   # Ejecuta el ejemplo de audio
make run07_Fisica      # Ejecuta ejemplo de física
```

### Opción 2: Directamente desde bin/
```bash
./bin/09_Vaqueros.exe
./bin/011_AudioVaq.exe
./bin/07_Fisica.exe
```

### Opción 3: Compilar y ejecutar
```bash
make clean && make all
./bin/09_Vaqueros.exe
```

---

## 📋 Estado del Proyecto

### ✅ Completado:
- 12 ejemplos funcionales compilados
- Juego Vaqueros con IA y múltiples modos
- Sistema de física Box2D v3
- Sistema de audio con máquina de estados
- Interfaz de usuario completa
- Animaciones de texto
- Control de entrada

### ⚠️ Pendiente:
- Archivos de música OGG (usuario debe proporcionar)
- Sonidos de efectos (disparos, impactos)
- Persistencia de puntuaciones
- Mejoras gráficas adicionales

### 🔄 Mejoras Futuras:
- Efectos de sonido (gunshot, hit, victory)
- Pause/resume de música
- Control de volumen en UI
- Leaderboard/puntuaciones
- Más modos de juego
- Más niveles/dificultades

---

## 📊 Estadísticas del Proyecto

| Métrica | Valor |
|---------|-------|
| Total de archivos fuente | 14 .cpp |
| Total de ejecutables | 12 .exe |
| Tamaño total compilado | ~2.0 MB |
| Líneas de código (09_Vaqueros) | ~746 |
| Líneas de código (011_AudioVaq) | ~175 |
| Archivos header | 7 |
| Documentación | 6 archivos .md |
| Framework principal | SFML 2.x |
| Motor de física | Box2D 3.0+ |

---

## 🎓 Conceptos Aprendidos

1. **SFML Graphics:** Ventanas, sprites, formas, texto
2. **SFML Audio:** Música, looping, control de volumen
3. **Input Handling:** Teclado, eventos en tiempo real
4. **Physics Engine:** Colisiones, fuerzas, gravedad (Box2D)
5. **Game Design:** Estados, máquinas de estado, IA básica
6. **C++ Avanzado:** Clases, structs, vectores, punteros
7. **Build System:** Makefiles, compilación condicional
8. **Audio Streaming:** Archivos OGG, música en bucle

---

## 📞 Comandos Útiles

```bash
# Compilar uno específico
g++ src/09_Vaqueros.cpp -o bin/09_Vaqueros.exe \
  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d -Iinclude

# Compilar todo
cd EjemplosJuego
make clean
make all

# Ejecutar
./bin/09_Vaqueros.exe

# Limpiar binarios
make clean
```

---

## 📖 Referencias y Documentación

- [SFML Official Docs](https://www.sfml-dev.org/)
- [Box2D Documentation](https://box2d.org/documentation/)
- [MinGW Installation](https://www.mingw-w64.org/)
- [Msys2 Wiki](https://www.msys2.org/)

---

## 📝 Notas Importantes

1. **Rutas de Archivos:** Usar `./assets/` desde el directorio raíz
2. **Formato Audio:** Solo OGG Vorbis es soportado por SFML
3. **Resolución:** 800x600 (estándar en todos los ejemplos)
4. **FPS:** Limitado a 60 FPS en los ejemplos
5. **Audio:** Requiere que los archivos OGG existan en `/assets/music/`

---

**Última actualización:** 11 de Diciembre de 2025
**Estado:** ✅ Proyecto operativo y completo

