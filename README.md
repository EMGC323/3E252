# 🎮 VAQUEROS: Wild West Duel

> Un juego de duelo del viejo oeste desarrollado en C++ con SFML y Box2D
> 
## 📋 Descripción del Proyecto

Es un juego estilo **Wild West Gunman** donde controlás un vaquero en épicos duelos. Cuenta con múltiples modos de juego incluyendo Jugador vs Jugador (PvP) y Jugador vs Bot con 3 niveles de dificultad progresiva.

## 🎯 Objetivo del Juego

¡Disfrutar venciendo al bot o a tus amigos en duelos del viejo oeste! Esquiva balas, destruye obstáculos y demuestra quién es el mejor tirador.

## 🎮 Controles

### 🎰 Menú Principal
| Acción | Tecla |
|--------|-------|
| Seleccionar PvP | `1` |
| Seleccionar VS_BOT | `2` |
| Salir | `ESC` |

### 💪 Durante el Juego - Jugador 1 (Rojo)
| Acción | Tecla |
|--------|-------|
| Mover arriba | `W` |
| Mover abajo | `S` |
| Mover izquierda | `A` |
| Mover derecha | `D` |
| Disparar | `SPACE` |
| Recargar | `R` |

### 🎯 Durante el Juego - Jugador 2 / Bot (Azul)
| Acción | Tecla |
|--------|-------|
| Mover arriba | `↑` |
| Mover abajo | `↓` |
| Mover izquierda | `←` |
| Mover derecha | `→` |
| Disparar (PvP) | `ENTER` |
| Recargar (PvP) | `P` |

### 🏆 Pantalla de Victoria
| Acción | Tecla |
|--------|-------|
| Volver al menú | `SPACE` |
---

## ⚙️ Mecánicas Principales

### 1️⃣ Sistema de Combate
- **Disparos**: Balas amarillas (Jugador 1) y cian (Jugador 2)
- **Daño**: Cada impacto causa 20 puntos de daño
- **Salud**: Comienza con 100 HP, termina en 0 HP

### 2️⃣ Sistema de Munición
- **Cargador**: 5 balas por cargador
- **Recarga**: 
  - Jugador 1: `R`
  - Jugador 2: `P`
  - Bot: Automática
- **Visualización**: 5 círculos bajo la barra de vida

### 3️⃣ Animaciones de Disparo
- Frames rápidos sincronizados (0.1 segundos)
- Diferentes sprites para cada personaje
- Transiciones suaves

### 4️⃣ Movimiento
- **Velocidad**: 300 píxeles/segundo
- **Bot**: Varía según dificultad
- Sin restricciones de mapa

---

## 🏆 Características Destacadas

### 🗺️ Generación Procedural de Mapas
- Mapa único en cada partida
- Obstáculos y elementos aleatorios
- Infinita rejugabilidad

### 💥 Estructuras Destructibles
4 tipos distintos con resistencias variadas:
- **Madera**: 1 disparo
- **Piedra**: 2 disparos  
- **Barriles**: 1 disparo
- **Torres**: 3 disparos

Pueden usarse como cobertura estratégica.

### 🤖 IA Inteligente (3 Niveles)

| Dificultad | Cadencia de Disparo | Velocidad |
|-----------|-------------------|-----------|
| 🟢 EASY | 1.8 segundos | Lenta |
| 🟡 MEDIUM | 1.0 segundos | Normal |
| 🔴 HARD | 0.5 segundos | Rápida |

---

## 🛠️ Tecnologías Utilizadas

| Componente | Descripción | Versión |
|-----------|-------------|---------|
| **C++** | Lenguaje principal | C++11+ |
| **SFML** | Gráficos, audio, entrada | 2.6+ |
| **Box2D** | Motor de física 2D | 3.0+ |
| **MinGW64** | Compilador | Latest |
| **Git** | Control de versiones | Latest |

---

## 🚀 Instalación y Ejecución

### Método 1: Ejecutable Compilado (⚡ Más Fácil)
1. Ve a [Releases](../../releases)
2. Descarga `JuegoProyecto.exe`
3. Ejecuta el archivo

### Método 2: Compilar desde Código
**Requisitos**: MSYS2, MinGW64, SFML, Box2D

```bash
cd 3E252/EjemplosJuego
make all              # Compilar todo
make run09_Vaqueros   # Compilar y ejecutar
make clean            # Limpiar binarios
```

---

## 📊 Estructura del Proyecto

```
3E252/
├── .github/
│   └── workflows/
│       └── publish.yml         ← GitHub Actions (CI/CD)
├── EjemplosJuego/
│   ├── src/
│   │   ├── 09_Vaqueros.cpp     ← Juego principal (1,474 líneas)
│   │   └── 00-13_*.cpp         ← Otros 12 ejemplos
│   ├── assets/
│   │   ├── images/             ← Texturas y sprites
│   │   ├── music/              ← Audio OGG
│   │   └── fonts/              ← Fuentes TTF
│   ├── include/                ← Headers
│   └── makefile                ← Build system
├── gallery/
│   └── cover.png               ← Portada del juego
├── screenshots/                ← Capturas de pantalla
├── video/                      ← Demo gameplay
└── README.md                   ← Esta guía
```

---

## 👥 Equipo de Desarrollo

**Líder de Proyecto**: Eric Misael Godoy Canela (EMGC323)

### 🎮 Nuevas Características
- [ ] Multijugador en línea
- [ ] Modo Torneo
- [ ] Personalización de personajes
- [ ] Tabla de puntuaciones global
- [ ] Logros y desbloqueos
- [ ] Niveles de dificultad dinámicos

### ⚡ Optimizaciones
- [ ] Renderizado por octree
- [ ] Object pooling para balas
- [ ] Shaders gráficos avanzados
- [ ] Streaming de recursos

---

## 📚 Recursos Útiles

### 📖 Documentación Oficial
- [SFML Docs](https://www.sfml-dev.org/documentation/)
- [Box2D Manual](https://box2d.org/documentation/)
- [C++ Reference](https://en.cppreference.com/)

### 🎓 Tutoriales
- [SFML Game Dev](https://www.sfml-dev.org/tutorials/)
- [Game Design Patterns](https://gameprogrammingpatterns.com/)

### 🎨 Assets Gratuitos
- [OpenGameArt](https://opengameart.org/)
- [DaFont](https://www.dafont.com/es/)
- [Freesound](https://freesound.org/)

---

## 📄 Licencia y Créditos

### 📜 Licencia
El proyecto está bajo licencia **MIT**. Ver [LICENSE](LICENSE) para detalles.

### 🙏 Dependencias
- **SFML**: Licencia Zlib
- **Box2D**: Licencia MIT
- **MinGW64**: GPL v3+

### 🎨 Assets Utilizados
- **Música**: Fuentes Creative Commons
- **Sprites**: Creación original para el proyecto
- **Fondos**: Generados con Google Gemini
- **Fuentes**: DaFont (Fuente "Ring")

### ✨ Inspiraciones
- Clásicos western (Gun Slinger, Duels)
- Arcade retro (Worms, Bomberman)
- Comunidad global de gamedev

## 🎉 ¡Que Disfrutes el Duelo!

```
    ┌─────────────────────────────────┐
    │   🤠 VAQUEROS: Wild West Duel  🤠│
    │      ¡Que gane el mejor!        │
    └─────────────────────────────────┘
```
