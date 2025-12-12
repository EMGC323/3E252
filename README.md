Descripción del Proyecto
es un juego estilo wild gunman en pixel, el cual se caracteriza por tener 2 modos de juego los cuales son JvzJ o JvsBot,
el bot cuenta con 3 niveles de dificultad los cuales aumentan su velocidad de disparo.

🎯 Objetivo del Juego
disfrutar el vencer al bot o a tus amigos.

🎮 Controles
Lista los controles:Lista de Controles - 09_Vaqueros
MENÚ PRINCIPAL
Acción	Tecla
Seleccionar PvP (Jugador vs Jugador)	1
Seleccionar VS_BOT (Jugador vs Bot)	2
Salir	ESC
SELECCIÓN DE DIFICULTAD (Modo VS_BOT)
Acción	Tecla
Dificultad EASY	1
Dificultad MEDIUM	2
Dificultad HARD	3
ENTRADA DE NOMBRES
Acción	Tecla
Escribir nombre	Cualquier letra/número
Borrar última letra	Backspace
Confirmar nombre	ENTER
DURANTE EL JUEGO
Jugador 1 (Rojo)
Acción	Tecla
Mover arriba	W
Mover abajo	S
Mover izquierda	A
Mover derecha	D
Disparar	SPACE
Recargar	R
Jugador 2 / Bot (Azul)
Acción	Tecla
Mover arriba	↑ (Flecha arriba)
Mover abajo	↓ (Flecha abajo)
Mover izquierda	← (Flecha izquierda)
Mover derecha	→ (Flecha derecha)
Disparar (solo PvP)	ENTER
Recargar (solo PvP)	P
PANTALLA DE VICTORIA
Acción	Tecla
Volver al menú	SPACE


⚙️ MecánicasMecánicas Principales - 09_Vaqueros
1. Sistema de Combate
Disparos: Los jugadores disparan balas amarillas (Jugador 1) y cian (Jugador 2)
Daño: Cada impacto causa 20 puntos de daño
Salud: Cada vaquero comienza con 100 HP, la partida termina cuando alguien llega a 0 HP
2. Sistema de Munición
Cargador: 5 balas por cargador
Recarga:
Jugador 1: Presionar R
Jugador 2 (PvP): Presionar P
Bot: Recarga automática
Visualización: 5 círculos bajo la barra de vida (amarillo = ammo, gris = vacío)
3. Animaciones de Disparo
Jugador 1: Frames rotados 90° (pixil-frame-0 y pixil-frame-0 (1))
Jugador 2: Sin rotación (pixil-frame-0 (2) y pixil-frame-0 (3))
Bot: Usa enemigo.png y enemigodisp.png
Velocidad: 0.1 segundos por frame (muy rápida, sincronizada con balas)
4. Movimiento
Jugador 1: WASD (sin restricciones de mapa)
Jugador 2: Flechas direccionales
Velocidad: 300 píxeles/segundo
Velocidad del Bot: Varía según dificultad

🏆 Características1. 
Generación Procedural de Mapas Aleatorios
Cada partida genera un mapa único y diferente con:

Rocas, cactus, arbustos y elementos de terreno dispersados aleatoriamente
Garantiza que ninguna partida sea igual a otra
Proporciona infinita rejugabilidad y variedad táctica
2. Estructuras Destructibles Dinámicas
Sistema de obstáculos interactivos que:

Se rompen con disparos (1-3 impactos según tipo)
Cambian color visualmente al recibir daño
Agregación de profundidad estratégica: los jugadores pueden usar estructuras como cobertura
4 tipos distintos (madera, piedra, barriles, torres) con diferentes resistencias
3. IA Inteligente con 3 Niveles de Dificultad
Bot de juego adaptable que:

Persigue activamente al jugador
Dispara con cadencia ajustable (1.8s / 1.0s / 0.5s según dificultad)
Cambia velocidad de movimiento (lenta/normal/rápida)
Recarga automáticamente sin limitaciones
Proporciona desafío progresivo desde principiantes hasta expertos

👥 Equipo
Líder : Eric Misael Godoy Canela (EMGC323)

🛠️ Tecnologías

Motor/Marco
SFML 2.x (Simple and Fast Multimedia Library)
Módulo Graphics: Renderizado de sprites y formas
Módulo Window: Gestión de ventanas y eventos
Módulo System: Timing y utilidades del sistema
Módulo Audio: Reproducción de música y sonidos
Lenguaje
C++ (C Plus Plus)
Compilador: MinGW64 g++
Estándar: C++11 o superior
Características: Orientado a objetos, clases personalizadas
Librerías Adicionales
Box2D 3.0+
Motor de física
API basada en funciones (no clases tradicionales)
Simulación de cuerpos rígidos y colisiones
Sistema de Construcción
GNU Makefile
Reglas de patrón para compilación automática
Compilación: g++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d
Entorno de Desarrollo
Visual Studio Code (VS Code)
Windows PowerShell (compilación y ejecución)
Msys2 (entorno MinGW64)
Formato de Recursos
Imágenes: PNG (transparencia RGBA), JPEG (convertido a PNG)
Audio: OGG Vorbis (comprimido, streaming)
Resolución: 800x600 píxeles
Control de Versiones
Git (repositorio local)
Rama: main
Commits frecuentes con progreso
Herramientas Auxiliares
PowerShell Scripts: Conversión de imágenes JPEG → PNG
Procesamiento de fondos y assets visuales
Características Técnicas
Renderización: 2D con sprites y formas geométricas
Física: Colisiones AABB (axis-aligned bounding box)
Animaciones: Frame-based (2 frames por acción)
Audio: Múltiples instancias de sonido (3 canales para disparos)
Generación procedural: Terreno y estructuras dinámicas

📜 Créditos - 09_Vaqueros
Assets de Terceros Utilizados
Música y Audio
"Cowboy Serenade" (cowboy-serenade_92401.ogg)

Fuente: Audio library (presumiblemente libre de derechos o Creative Commons)
Uso: Música de menú (loop al 75% volumen)
"Musica" (musica.ogg)

Fuente: Archivo de proyecto original
Uso: Música de juego (loop al 75% volumen)
Efecto de Sonido: Disparo de Pistola (pistol-12-gauge-self-loading-shoots-version-2-Trimmed-by-FlexClip.ogg)

Fuente: FlexClip (editor de video)
Modificación: Trimmed/cortado a medida
Uso: Efectos de sonido en combate
Imágenes Generadas
Gemini_Generated_Image_l3zcj6l3zcj6l3zc.png
Generada con: Google Gemini (IA generativa)
Uso: Fondo de menú principal (tema desierto)
Sprites y Assets Visuales
Pixil Art Frames (pixil-frame-0.png, pixil-frame-0 (1-3).png)

Creadas manualmente para el proyecto
Uso: Animaciones de personajes (vaqueros)
Enemy Assets (enemigo.png, enemigodisp.png)

Creadas manualmente para el proyecto
Uso: Imagen y animación del bot/enemigo
Fondos de Dificultad

facil.png (EASY)
medio.png (MEDIUM)
hard.png (HARD)
Creadas manualmente para el proyecto
Imágenes de Victoria

vaquerowins.png (Jugador gana vs Bot)
iawins.png (Bot gana)
gano1.png (Jugador 1 gana en PvP)
gano2.png (Jugador 2 gana en PvP)
Creadas manualmente para el proyecto
Referencias e Inspiraciones
Género
Duelos de vaqueros clásicos: Inspiración visual y temática
Juegos de estrategia táctica: Sistema de cobertura y destructibilidad
Juegos arcade retro: Mecánicas simples pero profundas
Mecánicas Inspiradas En
Worms: Destrucción ambiental, estrategia táctica
Bomberman: Generación procedural de mapas, obstáculos dinámicos
Dueling games: Combate uno contra uno o versus IA
Shoot-em-ups clásicos: Sistema de munición y recarga
Librerías de Terceros
SFML 2.x: Laurent Gomila y colaboradores

Licencia: Zlib
Descripción: Abstracción de bajo nivel para gráficos, audio y eventos
Box2D 3.0+: Erin Catto

Licencia: MIT
Descripción: Motor de física 2D robusto
MinGW64: GNU Compiler Collection

Licencia: GPL v3+
Descripción: Compilador C++ para Windows
Agradecimientos Especiales
Colaboradores del Proyecto
Equipo de desarrollo: Dedicado a pulir el juego y añadir características
Testers: Por ayudar a identificar bugs y mejorar la jugabilidad
Comunidades de Código Abierto
SFML Community: Por documentación y soporte
Box2D Community: Por el excelente motor de física
MinGW Project: Por proporcionar herramientas de compilación gratuitas
Inspiración Visual
Pixel Art Community: Técnicas de animación frame-based
Pixel Game Developers: Mejores prácticas en juegos 2D
Herramientas y Recursos
Visual Studio Code: Editor de código gratuito
Git/GitHub: Control de versiones
Google Gemini: Generación de imágenes para fondos
Referencias Técnicas
Documentación oficial de SFML: Implementación de gráficos y audio
Box2D Manual: Física y colisiones
C++ Reference: Estándar del lenguaje
Licencia del Proyecto
El proyecto 09_Vaqueros utiliza:

Código propio: Disponible bajo la licencia del repositorio
Dependencias de terceros: Respetando sus respectivas licencias (Zlib, MIT, GPL)
Assets visuales: Creados específicamente para este proyecto
Contacto y Soporte
Para reportar bugs, sugerencias o contribuciones:

Repositorio: GitHub 3E252
Rama principal: main
Estado: En desarrollo activo
Gracias a todos quienes han hecho posible este proyecto, desde los desarrolladores de las librerías hasta la comunidad global de gamedev.
