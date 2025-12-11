# 🎮 GUÍA PRÁCTICA: Ejecutar y Desarrollar en EjemplosJuego

## ⚡ Inicio Rápido (5 minutos)

### 1. Compilar todos los ejemplos
```bash
cd c:\Users\mrcan\OneDrive\Documentos\GitHub\3E252\EjemplosJuego
make clean
make all
```

### 2. Ejecutar un ejemplo
```bash
make run09_Vaqueros    # Juego de vaqueros
make run011_AudioVaq   # Demo de audio
make run07_Fisica      # Simulación física
make run00_Ventana     # Ejemplo básico
```

### 3. Ejecutar directamente
```bash
./bin/09_Vaqueros.exe
./bin/011_AudioVaq.exe
./bin/07_Fisica.exe
```

---

## 🎯 Guía de Juego: 09_Vaqueros

### Pantalla 1: Selección de Modo
```
VAQUEROS
Wild West Duel

SELECT GAME MODE
1 - Player vs Player
2 - Player vs Bot
ESC - Exit
```
**Acción:** Presiona `1` o `2`

### Pantalla 2: Selección de Dificultad (solo si vs Bot)
```
VAQUEROS
Wild West Duel

SELECT BOT DIFFICULTY
1 - EASY (Slow shooting)
2 - MEDIUM (Normal)
3 - HARD (Fast & Aggressive)
```
**Acción:** Presiona `1`, `2` o `3`

### Pantalla 3: Entrada de Nombres
```
VAQUEROS
Wild West Duel

Red Cowboy name: [TuNombre]
Press ENTER when done

[Si PvP - te pedirá nombre para Jugador 2]
```
**Acción:** Escribe nombre y presiona `ENTER`

### Pantalla 4: Juego
```
Red Hits: X  |  Blue Hits: Y

[BARRA DE VIDA 1] [LINE CENTRAL] [BARRA DE VIDA 2]
[VAQUERO ROJO]                      [VAQUERO AZUL/BOT]

Instrucciones según modo...
```

**Controles Jugador 1 (Rojo):**
- `W` - Arriba
- `S` - Abajo
- `A` - Izquierda
- `D` - Derecha
- `SPACE` - Disparar

**Controles Jugador 2 (Azul, solo PvP):**
- `↑` Flecha arriba - Arriba
- `↓` Flecha abajo - Abajo
- `←` Flecha izquierda - Izquierda
- `→` Flecha derecha - Derecha
- `ENTER` - Disparar

**Bot (VS_BOT):** Movimiento y disparo automático según dificultad

### Pantalla 5: Victoria
```
VICTORY!

[NombreGanador]

Press SPACE to return to menu
```
**Acción:** Presiona `SPACE` para jugar de nuevo

---

## 🔧 Desarrollo: Modificar 09_Vaqueros.cpp

### Estructura del Código
```cpp
// 1. INCLUDES y CONSTANTES
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
// ...

// 2. STRUCT: Bullet (proyectil)
struct Bullet { /* ... */ };

// 3. CLASS: Cowboy (vaquero)
class Cowboy { /* ... */ };

// 4. MAIN: Máquina de estados
int main() {
    // Enum de estados
    // Inicialización
    // Game Loop
    //   - Procesamiento de eventos
    //   - Actualización de lógica
    //   - Renderizado
}
```

### Cambiar la Resolución
**Archivo:** `09_Vaqueros.cpp` (línea ~11)

```cpp
// Actual:
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Para cambiar a 1024x768:
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

// Luego compilar:
make clean
make 09_Vaqueros
```

### Cambiar la Velocidad de los Vaqueros
**Archivo:** `09_Vaqueros.cpp` (línea ~14)

```cpp
// Actual:
const float COWBOY_SPEED = 300.0f;

// Para más rápido (500):
const float COWBOY_SPEED = 500.0f;

// Para más lento (150):
const float COWBOY_SPEED = 150.0f;
```

### Cambiar el Tamaño de los Vaqueros
**Archivo:** `09_Vaqueros.cpp` (línea ~12)

```cpp
// Actual:
const float COWBOY_SIZE = 30.0f;

// Para más grande:
const float COWBOY_SIZE = 50.0f;

// Para más pequeño:
const float COWBOY_SIZE = 20.0f;
```

### Cambiar Daño por Bala
**Archivo:** `09_Vaqueros.cpp` (búscar: `cowboy1->health -= 20`)

```cpp
// Actual (línea ~601):
cowboy1->health -= 20;

// Para cambiar a 25:
cowboy1->health -= 25;

// Para cambiar a 10:
cowboy1->health -= 10;
```

### Cambiar Salud Inicial
**Archivo:** `09_Vaqueros.cpp` (búscar: `health(100)` en clase Cowboy)

```cpp
// En constructor de Cowboy (línea ~33):
health(100)   // Vida inicial

// Para cambiar a 150:
health(150)

// Para cambiar a 50:
health(50)
```

### Cambiar Velocidad de Disparo del Bot
**Archivo:** `09_Vaqueros.cpp` (búscar: `BOT_SHOOT_INTERVAL`)

```cpp
// Los intervalos se asignan según dificultad:

// EASY (línea ~259):
BOT_SHOOT_INTERVAL = 2.5f;  // Dispara cada 2.5 segundos

// MEDIUM (línea ~265):
BOT_SHOOT_INTERVAL = 1.5f;  // Dispara cada 1.5 segundos

// HARD (línea ~271):
BOT_SHOOT_INTERVAL = 0.8f;  // Dispara cada 0.8 segundos
```

### Cambiar Colores de los Vaqueros
**Archivo:** `09_Vaqueros.cpp` (búscar: `sf::Color::Red` y `sf::Color::Blue`)

```cpp
// Vaquero 1 usa Red (línea ~508 en draw()):
sf::Color cowboyColor = (id == 1) ? sf::Color::Red : sf::Color::Blue;

// Cambiar rojo por verde:
sf::Color cowboyColor = (id == 1) ? sf::Color::Green : sf::Color::Blue;

// Cambiar azul por magenta:
sf::Color cowboyColor = (id == 1) ? sf::Color::Red : sf::Color::Magenta;

// O usar colores RGB custom:
sf::Color cowboyColor = (id == 1) ? sf::Color(255, 100, 0) : sf::Color(0, 100, 255);
```

### Cambiar Tamaño de las Balas
**Archivo:** `09_Vaqueros.cpp` (línea ~13)

```cpp
// Actual:
const float BULLET_SIZE = 2.0f;

// Para balas más grandes:
const float BULLET_SIZE = 5.0f;

// Para balas invisibles (debug):
const float BULLET_SIZE = 0.5f;
```

### Agregar Sonido de Disparo
**Paso 1:** Crear archivo WAV/OGG en `assets/sounds/gunshot.ogg`

**Paso 2:** En `09_Vaqueros.cpp`, después de cargar música (línea ~202):

```cpp
// Cargar sonido de disparo
sf::SoundBuffer gunShotBuffer;
gunShotBuffer.loadFromFile("./assets/sounds/gunshot.ogg");
sf::Sound gunShot(gunShotBuffer);
gunShot.setVolume(50);
```

**Paso 3:** Cuando se dispara (línea ~508 para jugador 1):

```cpp
if (!spacePressedGame) {
    spacePressedGame = true;
    sf::Vector2f spawnPos = cowboy1->getBulletSpawnPos();
    bullets.emplace_back(spawnPos, sf::Vector2f(BULLET_SPEED, 0), 1);
    gunShot.play();  // ← Agregar esta línea
}
```

---

## 🎵 Agregar Música Propia

### Paso 1: Preparar archivo de audio
1. Convertir a OGG Vorbis (usar Audacity gratis: https://www.audacityteam.org/)
2. Nombres sugeridos:
   - `menu_vaqueros.ogg` - Música de menú (20-60 segundos, tranquila)
   - `game_vaqueros.ogg` - Música de juego (30+ segundos, rápida)

### Paso 2: Guardar en carpeta
```
EjemplosJuego/
└── assets/
    └── music/
        ├── menu_vaqueros.ogg  ← Aquí
        └── game_vaqueros.ogg  ← Aquí
```

### Paso 3: Verificar carga
Ejecutar `make run09_Vaqueros`
- Si no hay errores en consola: ✅ Se cargó correctamente
- Si hay advertencia "Advertencia: No se cargó...": Verificar rutas

---

## 📊 Debug y Troubleshooting

### Música no suena
```
1. Verificar archivos existen:
   - EjemplosJuego/assets/music/menu_vaqueros.ogg
   - EjemplosJuego/assets/music/game_vaqueros.ogg

2. Verificar formato: OGG Vorbis (no MP3, no WAV)

3. Ver terminal para advertencias (línea ~199-209 de 09_Vaqueros.cpp)
```

### Juego se congela
```
1. Abrir en terminal de MSYS2 (no CMD)
2. Ver si hay error en consola
3. Verificar que Ring.ttf existe: EjemplosJuego/assets/fonts/Ring.ttf
```

### Vaqueros no se ven
```
1. Verificar que gameState es PLAYING
2. Verificar que cowboy1 y cowboy2 no son nullptr
3. Comprobar método draw() en clase Cowboy (línea ~505)
```

### Balas pasan a través
```
1. Verificar detección de colisiones (línea ~600-635)
2. Comprobar getBounds() devuelve rect correcto
3. Aumentar tamaño de balas para debug:
   const float BULLET_SIZE = 10.0f;
```

---

## 📝 Crear Variante del Juego

### Ejemplo: Juego de "Duelo Instantáneo"
**Archivo:** Crear `src/12_VaquerosRapido.cpp`

```cpp
// Copiar 09_Vaqueros.cpp completo
// Cambios:
// 1. Salud inicial = 30 (en lugar de 100)
// 2. Daño por bala = 30 (en lugar de 20) → 1 shot kill
// 3. Velocidad vaqueros = 400 (en lugar de 300)
// 4. Velocidad balas = 600 (en lugar de 500)

// Compilar:
g++ src/12_VaquerosRapido.cpp -o bin/12_VaquerosRapido.exe \
  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d -Iinclude

// Ejecutar:
./bin/12_VaquerosRapido.exe
```

---

## 🚀 Optimizaciones

### Mejorar FPS (si está lento)
```cpp
// Línea ~187, cambiar:
window.setFramerateLimit(60);

// A:
window.setFramerateLimit(120);  // Más fluido

// O para ahorrar CPU:
window.setFramerateLimit(30);   // Menos fluido pero menos CPU
```

### Reducir consumo de memoria
```cpp
// En lugar de crear mucho audio:
// Usar un vector compartido de efectos de sonido

vector<sf::Sound> gunshotSounds;
for(int i = 0; i < 5; i++) {
    gunshotSounds.emplace_back(gunShotBuffer);
}
// Luego ciclar entre ellos
```

---

## 📚 Ejemplos Adicionales para Aprender

### Modificar otros ejemplos:

**07_Fisica.cpp** - Motor Box2D
```cpp
// Cambiar gravedad:
worldDef.gravity = {0.0f, 10.0f};  // Actual (normal)
worldDef.gravity = {0.0f, 20.0f};  // Más fuerte
worldDef.gravity = {0.0f, 0.0f};   // Sin gravedad (espacio)

// Cambiar fricción:
fixtureSueloDef.friction = 1.0f;   // Fricción alta
fixtureSueloDef.friction = 0.0f;   // Hielo (sin fricción)
```

**010_Textovaq.cpp** - Animaciones
```cpp
// Ver cómo hace animaciones de color cíclico
// Ver cómo escala el texto dinámicamente
// Ver rotación de texto

// Copiar patrón a 09_Vaqueros para animar vaqueros
```

**011_AudioVaq.cpp** - Sistema de Audio
```cpp
// Ver patrón de máquina de estados con audio
// Ver cómo manejar archivos no encontrados
// Copiar este patrón para agregar más sonidos
```

---

## 🔗 Enlaces Útiles

- [SFML Documentación](https://www.sfml-dev.org/documentation/2.6.0/)
- [Box2D Manual](https://box2d.org/documentation/)
- [Audacity (convertir audio)](https://www.audacityteam.org/)
- [DaFont (descargar fuentes)](https://www.dafont.com/es/)
- [OpenGameArt (assets gratis)](https://opengameart.org/)

---

## 💡 Próximos Pasos

1. **Agregar música**: Crear/descargar archivos OGG para menu y game
2. **Agregar efectos**: Sonido de disparo, impacto, victoria
3. **Mejorar gráficos**: Sprites más detallados, animaciones
4. **Agregar modos**: Supervivencia, tiempo limitado, etc.
5. **Guardar puntuaciones**: Persistencia en archivo
6. **Menú mejorado**: Opciones de volumen, dificultad
7. **Inteligencia artificial mejorada**: Patrones de ataque
8. **Multijugador en red**: (Avanzado)

---

**Última actualización:** 11 de Diciembre de 2025

