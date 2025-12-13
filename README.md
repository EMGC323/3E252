<<<<<<< HEAD
# EjemplosJuego

El proyecto esta desarrollado sobre MinGW64 utilizando Msys2
y como editor se esta utilizando Visual Studio Code.

## Prerequisitos

[Instalar las herramientas necesarias](./docs/herramientas.md)

[Instalar las Extensiones VSCode](./docs/extensiones.md)

[Instalar las librerias](./docs/librerias.md)

[Clonar el repositorio](./docs/fork.md)

## Como ejecutar los ejemplos

Instalar todas las dependencias descritas arriba y dentro de una terminal de vscode ejecutar:

> make run'NombreEjecutable'

Por ejemplo para ejecutar '00_Ventana.cpp' correr el comando en la terminal de vscode:

> make run00_Ventana

## Errores comunes
- [Los diagramas de PUML no se visualizan bien]()

## Buenas Practicas
- [Como Crear un buen readme](https://www.makeareadme.com/)
- [Patrones de diseño](https://refactoring.guru/es/design-patterns)
- [Como hacer commits semanticos]()
- [Como estructurar un proyecto]()
- [Que tipos de licencias existen]()

## Tutoriales Github
- [Creacion de un repositorio]()
- [Como colaborar en un proyecto]()
- [Solicitar developer pack]()

## Recursos Gratis
- [Fuentes de texto gratis](https://www.dafont.com/es/)
- [Recursos gratis de Videojuegos](https://opengameart.org/)
=======
# 🤠 VAQUEROS - Wild West Duel

## 🎯 Objetivo del Juego

El objetivo principal es ganar el duelo contra tu oponente disparando tus balas mientras esquivas los ataques enemigos. Puedes jugar en modo **Jugador vs Jugador (PvP)** o contra un **Bot con diferentes niveles de dificultad**. 

Derrota al oponente reduciendo su salud a 0 puntos para ganar la partida.

---

## 🎮 Controles

### Vaquero 1 (Lado Izquierdo - Rojo)
- **A/D**: Movimiento izquierda/derecha
- **W/S**: Movimiento arriba/abajo
- **SPACE**: Disparar
- **R**: Recargar munición

### Vaquero 2 (Lado Derecho - Azul)
- **FLECHAS IZQUIERDA/DERECHA**: Movimiento izquierda/derecha
- **FLECHAS ARRIBA/ABAJO**: Movimiento arriba/abajo
- **ENTER**: Disparar
- **P**: Recargar munición

### Menús
- **1**: Seleccionar modo PvP
- **2**: Seleccionar modo vs Bot
- **3**: Seleccionar dificultad (en modo Bot)
- **ESC**: Salir del juego
- **SPACE**: Continuar/Volver al menú

---

## ⚙️ Mecánicas

### Sistema de Salud
- Cada jugador comienza con **100 puntos de vida**
- Cada disparo acertado inflige **20 puntos de daño**
- Cuando la salud llega a 0, el jugador es derrotado

### Sistema de Munición
- Cada jugador tiene **5 balas por cargador**
- Presiona **R** (P para jugador 2) para recargar
- Los barriles de munición se muestran debajo de la barra de vida

### Estructuras Destructibles
El mapa incluye varios tipos de obstáculos que puedes destruir:
- **Cajas de Madera** (🟨): Destruidas en 1 disparo
- **Cajas de Piedra** (⬜): Requieren 2 disparos
- **Barriles** (⭕): Destruidas en 1 disparo
- **Torres** (🏛️): Requieren 3 disparos

### IA del Bot
El bot ajusta su comportamiento según la dificultad:
- **FÁCIL**: Movimiento lento, disparos espaciados
- **MEDIO**: Comportamiento equilibrado
- **DIFÍCIL**: Movimiento rápido y agresivo, dispara frecuentemente

---

## 🏆 Características

✅ **Dos Modos de Juego**
- Modo PvP para jugar contra otro jugador
- Modo vs Bot con tres niveles de dificultad

✅ **Sistema de Entrada de Nombres**
- Personaliza el nombre de tu vaquero antes de jugar

✅ **Animaciones de Disparo**
- Animaciones dinámicas cuando disparas

✅ **Barras de Salud Visuales**
- Seguimiento visual del daño recibido

✅ **Mapa Procedural**
- Cada partida genera un nuevo mapa con estructuras destructibles aleatorias
- Rocas, cactus y arbustos en el terreno

✅ **Efectos de Sonido**
- Música de menú y juego
- Sonidos de disparo

✅ **Sistema de Puntuación**
- Contador de disparos acertados por cada jugador

✅ **Interfaz Intuitiva**
- Menús claros y fáciles de usar
- Todo el texto en color amarillo para mejor visibilidad

---

## 👥 Equipo

- **Desarrollador Principal**: @navarroceti
- **Basado en**: Proyecto educativo de SFML para la clase 3E252

---

## 🛠️ Tecnologías

**Motor/Framework**: SFML (Simple Fast Multimedia Library)
**Lenguaje**: C++ (C++11 o superior)
**Compilador**: MinGW64 (g++)

### Librerías Utilizadas
- **SFML 2.5+**: Gráficos, audio y entrada
- **Box2D**: Simulaciones de física (incluida para futuros usos)

### Herramientas de Desarrollo
- **VS Code**: Editor de código
- **MSYS2**: Entorno de compilación
- **Make**: Sistema de compilación
- **Git**: Control de versiones

---

## 📜 Créditos

### Recursos Utilizados
- Imágenes de fondo: Generadas con IA (Gemini)
- Fuente "Ring.ttf": Fuente estilizada Western
- Sonidos: Efectos de sonido de armas y música vaquera

### Referencias
- Documentación oficial de SFML
- Tutoriales de programación de juegos en C++
- Ejemplos educativos de visualización y entrada de usuarios

### Agradecimientos
- A todos los contribuidores y testers
- Comunidad de SFML por la excelente documentación
- Proyecto educativo 3E252 por el apoyo y dirección

---

## 📖 Cómo Jugar

1. **Ejecutar el juego**:
   ```bash
   make run09_Vaqueros
   ```

2. **Seleccionar modo**:
   - Presiona **1** para PvP
   - Presiona **2** para vs Bot

3. **Ingresar nombre**:
   - Escribe tu nombre y presiona **ENTER**

4. **Jugar**:
   - Usa los controles para moverte y disparar
   - Esquiva los ataques enemigos
   - Destruye obstáculos para tener ventaja táctica

5. **Victoria**:
   - Reduce la salud del enemigo a 0 para ganar
   - Presiona **SPACE** para volver al menú

---

## 🐛 Solución de Problemas

Si el juego no inicia:
1. Verifica que las imágenes de fondo estén en `assets/images/`
2. Verifica que las fuentes estén en `assets/fonts/`
3. Verifica que la música esté en `assets/music/`
4. Recompila con `make clean` y luego `make all`

---

## 📝 Notas de Desarrollo

- El código está completamente comentado en español
- Todos los textos del juego han sido personalizados a color amarillo
- El sistema de munición permite estrategia táctica
- El mapa procedural asegura partidas variadas

---

**¡Diviértete en el Oeste Salvaje! 🤠🔫**
>>>>>>> 0915846ab8b1087cae9b1f5373abb6152effd550
