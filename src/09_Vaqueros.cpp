#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float COWBOY_SIZE = 60.0f;
const float BULLET_SIZE = 2.0f;
const float BULLET_SPEED = 500.0f;
const float COWBOY_SPEED = 300.0f;

struct Bullet {
    sf::CircleShape shape;
    sf::Vector2f velocity;
    int owner; // 1 o 2
    
    Bullet(sf::Vector2f pos, sf::Vector2f vel, int own)
        : owner(own) {
        shape.setRadius(BULLET_SIZE);
        shape.setPosition(pos);
        shape.setFillColor(owner == 1 ? sf::Color::Yellow : sf::Color::Cyan);
        velocity = vel;
    }
};

// Clase para estructuras destructibles
class DestructibleStructure {
public:
    sf::RectangleShape shape;
    sf::CircleShape shapeCircle;
    int health;
    int maxHealth;
    int type; // 0=caja madera, 1=caja piedra, 2=barril, 3=torre
    bool isCircle;
    
    DestructibleStructure(sf::Vector2f pos, sf::Vector2f size, int typeIndex = 0) 
        : health(1), maxHealth(1), type(typeIndex), isCircle(false) {
        
        if (type == 2) { // Barril circular
            isCircle = true;
            float radius = size.x / 2;
            shapeCircle.setRadius(radius);
            shapeCircle.setPosition(pos);
            shapeCircle.setFillColor(sf::Color(139, 69, 19)); // Marrón oscuro
            shapeCircle.setOutlineThickness(2.f);
            shapeCircle.setOutlineColor(sf::Color(101, 50, 15));
        } else if (type == 1) { // Caja piedra (más resistente)
            maxHealth = 2;
            health = 2;
            shape.setSize(size);
            shape.setPosition(pos);
            shape.setFillColor(sf::Color(169, 169, 169)); // Gris piedra
            shape.setOutlineThickness(3.f);
            shape.setOutlineColor(sf::Color(105, 105, 105)); // Gris oscuro
        } else if (type == 3) { // Torre/pilar
            maxHealth = 3;
            health = 3;
            shape.setSize(sf::Vector2f(size.x, size.y * 1.5f));
            shape.setPosition(pos);
            shape.setFillColor(sf::Color(210, 180, 140)); // Arena oscura
            shape.setOutlineThickness(2.f);
            shape.setOutlineColor(sf::Color(184, 134, 11));
        } else { // Caja madera (tipo 0, por defecto)
            shape.setSize(size);
            shape.setPosition(pos);
            shape.setFillColor(sf::Color(184, 134, 11)); // Color arena oscura
            shape.setOutlineThickness(2.f);
            shape.setOutlineColor(sf::Color(139, 69, 19)); // Borde marrón
        }
    }
    
    bool isHit(const sf::CircleShape& bullet) {
        if (isCircle) {
            sf::FloatRect bulletBounds(bullet.getPosition().x, bullet.getPosition().y, 
                                      bullet.getRadius() * 2, bullet.getRadius() * 2);
            return shapeCircle.getGlobalBounds().intersects(bulletBounds);
        } else {
            sf::FloatRect bulletBounds(bullet.getPosition().x, bullet.getPosition().y, 
                                      bullet.getRadius() * 2, bullet.getRadius() * 2);
            return shape.getGlobalBounds().intersects(bulletBounds);
        }
    }
    
    void takeDamage() {
        health--;
    }
    
    bool isDestroyed() const {
        return health <= 0;
    }
    
    void draw(sf::RenderWindow& window) {
        if (isCircle) {
            window.draw(shapeCircle);
            // Mostrar daño con cambio de color
            if (health < maxHealth) {
                sf::CircleShape damageIndicator(shapeCircle.getRadius() * 0.3f);
                damageIndicator.setFillColor(sf::Color(255, 100, 100));
                damageIndicator.setPosition(shapeCircle.getPosition().x + shapeCircle.getRadius() * 0.35f,
                                           shapeCircle.getPosition().y + shapeCircle.getRadius() * 0.35f);
                window.draw(damageIndicator);
            }
        } else {
            // Cambiar color según daño recibido
            if (health < maxHealth) {
                sf::Color damageColor = shape.getFillColor();
                // Hacer más oscuro según daño
                int damage = maxHealth - health;
                damageColor.r = max(0, (int)damageColor.r - (damage * 30));
                damageColor.g = max(0, (int)damageColor.g - (damage * 30));
                damageColor.b = max(0, (int)damageColor.b - (damage * 30));
                shape.setFillColor(damageColor);
            }
            window.draw(shape);
            shape.setFillColor(sf::Color(184, 134, 11)); // Reset color
        }
    }
};

class Cowboy {
public:
    sf::Vector2f position;
    sf::RectangleShape healthBar;
    sf::RectangleShape healthBarBg;
    sf::Vector2f velocity;
    int id; // 1 o 2
    int health; // 100 puntos de vida
    string name;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    int ammunition = 5; // 5 balas por cargador
    const int MAX_AMMUNITION = 5;
    
    // Variables para animación de disparo
    sf::Texture shootAnimationTexture;
    sf::Sprite shootAnimationSprite;
    sf::Texture shootAnimationTexture2; // Segunda textura para animación
    bool isAnimating = false;
    int currentFrame = 0;
    float frameTimer = 0.0f;
    const float FRAME_TIME = 0.1f; // Tiempo entre frames (0.1 segundos)
    const int NUM_FRAMES = 2; // Total de frames en la animación (2 imágenes)
    sf::Clock animationClock;
    
    Cowboy(int cowboyId, float startX, string playerName, bool isBot = false)
        : id(cowboyId), velocity(0, 0), health(100), name(playerName),
          position(startX, WINDOW_HEIGHT / 2 - COWBOY_SIZE / 2) {
        // Barra de vida de fondo
        healthBarBg.setSize({100, 15});
        healthBarBg.setFillColor(sf::Color::White);
        
        // Barra de vida actual
        healthBar.setSize({100, 15});
        healthBar.setFillColor(sf::Color::Red);
        
        // Cargar textura del jugador 1
        if (id == 1) {
            if (playerTexture.loadFromFile("./assets/images/pixil-frame-0.png")) {
                playerSprite.setTexture(playerTexture);
                // Escalar si es necesario (ajusta según el tamaño de la imagen)
                float scale = COWBOY_SIZE / playerTexture.getSize().y;
                playerSprite.setScale(scale, scale);
            }
        }
        // Cargar textura del enemigo (jugador 2) o bot
        else if (id == 2) {
            // Si es bot en modo VS_BOT, usar enemigo.png
            if (isBot) {
                if (playerTexture.loadFromFile("./assets/images/enemigo.png")) {
                    playerSprite.setTexture(playerTexture);
                    float scale = COWBOY_SIZE / playerTexture.getSize().y;
                    playerSprite.setScale(scale, scale);
                }
            } else {
                // Si es jugador 2 en PvP, usar pixil-frame-0 (2).png
                if (playerTexture.loadFromFile("./assets/images/pixil-frame-0 (2).png")) {
                    playerSprite.setTexture(playerTexture);
                    float scale = COWBOY_SIZE / playerTexture.getSize().y;
                    playerSprite.setScale(scale, scale);
                }
            }
        }
        
        // Cargar spritesheet de animación de disparo
        if (id == 1) {
            // Jugador 1: usar pixil-frame-0 y pixil-frame-0 (1)
            if (shootAnimationTexture.loadFromFile("./assets/images/pixil-frame-0.png")) {
                shootAnimationSprite.setTexture(shootAnimationTexture);
                float scale = COWBOY_SIZE / shootAnimationTexture.getSize().y;
                shootAnimationSprite.setScale(scale, scale);
            }
            shootAnimationTexture2.loadFromFile("./assets/images/pixil-frame-0 (1).png");
        } else if (id == 2) {
            // Si es bot, usar enemigo.png y enemigodisp.png
            if (isBot) {
                if (shootAnimationTexture.loadFromFile("./assets/images/enemigo.png")) {
                    shootAnimationSprite.setTexture(shootAnimationTexture);
                    float scale = COWBOY_SIZE / shootAnimationTexture.getSize().y;
                    shootAnimationSprite.setScale(scale, scale);
                }
                shootAnimationTexture2.loadFromFile("./assets/images/enemigodisp.png");
            } else {
                // Si es jugador 2 en PvP, usar pixil-frame-0 (2) y pixil-frame-0 (3)
                if (shootAnimationTexture.loadFromFile("./assets/images/pixil-frame-0 (2).png")) {
                    shootAnimationSprite.setTexture(shootAnimationTexture);
                    float scale = COWBOY_SIZE / shootAnimationTexture.getSize().y;
                    shootAnimationSprite.setScale(scale, scale);
                }
                shootAnimationTexture2.loadFromFile("./assets/images/pixil-frame-0 (3).png");
            }
        }
    }
    
    void updateHealthBar() {
        float barWidth = 100 * (health / 100.0f);
        healthBar.setSize({barWidth, 15});
        
        if (id == 1) {
            healthBarBg.setPosition(10, 50);
            healthBar.setPosition(10, 50);
        } else {
            healthBarBg.setPosition(WINDOW_WIDTH - 110, 50);
            healthBar.setPosition(WINDOW_WIDTH - 110, 50);
        }
    }
    
    void drawAmmunition(sf::RenderWindow& window) {
        // Dibujar balas debajo de la barra de vida
        float bulletX = (id == 1) ? 10 : WINDOW_WIDTH - 110;
        float bulletY = 75;
        float bulletSpacing = 18;
        
        for (int i = 0; i < MAX_AMMUNITION; i++) {
            sf::CircleShape bulletDraw(3);
            bulletDraw.setFillColor(i < ammunition ? sf::Color::Yellow : sf::Color(100, 100, 100));
            bulletDraw.setPosition(bulletX + (i * bulletSpacing), bulletY);
            window.draw(bulletDraw);
        }
    }
    
    bool canShoot() const {
        return ammunition > 0;
    }
    
    void shoot() {
        if (ammunition > 0) {
            ammunition--;
        }
    }
    
    void reload() {
        ammunition = MAX_AMMUNITION;
    }
    
    void update(float dt) {
        position += velocity * dt;
        
        // Limitar movimiento horizontal (cada vaquero en su zona)
        if (id == 1) {
            // Vaquero 1: lado izquierdo (0 a mitad)
            if (position.x < 0) {
                position.x = 0;
            }
            if (position.x > WINDOW_WIDTH / 2 - COWBOY_SIZE) {
                position.x = WINDOW_WIDTH / 2 - COWBOY_SIZE;
            }
        } else {
            // Vaquero 2: lado derecho (mitad a ancho)
            if (position.x < WINDOW_WIDTH / 2) {
                position.x = WINDOW_WIDTH / 2;
            }
            if (position.x + COWBOY_SIZE > WINDOW_WIDTH) {
                position.x = WINDOW_WIDTH - COWBOY_SIZE;
            }
        }
        
        // Limitar movimiento vertical
        if (position.y < 0) {
            position.y = 0;
        }
        if (position.y + COWBOY_SIZE > WINDOW_HEIGHT) {
            position.y = WINDOW_HEIGHT - COWBOY_SIZE;
        }
    }
    
    // Iniciar animación de disparo
    void startShootAnimation() {
        isAnimating = true;
        currentFrame = 0;
        animationClock.restart();
    }
    
    // Actualizar animación de disparo
    void updateShootAnimation() {
        if (isAnimating) {
            if (animationClock.getElapsedTime().asSeconds() >= FRAME_TIME) {
                currentFrame++;
                if (currentFrame >= NUM_FRAMES) {
                    isAnimating = false;
                    currentFrame = 0;
                }
                animationClock.restart();
            }
        }
    }
    
    sf::Vector2f getBulletSpawnPos() {
        if (id == 1) {
            return {position.x + COWBOY_SIZE, 
                    position.y + COWBOY_SIZE / 2};
        } else {
            return {position.x, 
                    position.y + COWBOY_SIZE / 2};
        }
    }
    
    sf::FloatRect getBounds() const {
        return sf::FloatRect(position.x, position.y, COWBOY_SIZE, COWBOY_SIZE);
    }
    
    void draw(sf::RenderWindow& window) {
        // Si está animando disparo, mostrar la animación
        if (isAnimating) {
            shootAnimationSprite.setPosition(position);
            if (currentFrame == 0) {
                shootAnimationSprite.setTexture(shootAnimationTexture);
            } else {
                shootAnimationSprite.setTexture(shootAnimationTexture2);
            }
            // Rotación solo para jugador 1
            if (id == 1) {
                shootAnimationSprite.setRotation(90); // Rotada 90 grados a la derecha
            } else {
                shootAnimationSprite.setRotation(0); // Sin rotación para jugador 2
            }
            window.draw(shootAnimationSprite);
        }
        // Si no está animando, dibujar el personaje normal
        else if (playerTexture.getSize().x > 0) {
            playerSprite.setPosition(position);
            // Rotar el jugador 1 hacia la derecha
            if (id == 1) {
                playerSprite.setRotation(90);
            } else {
                playerSprite.setRotation(0);
            }
            window.draw(playerSprite);
        } else {
            // Si no hay imagen, dibujar vaquero simple: cabeza, cuerpo, brazos y pistola
            sf::Color cowboyColor = (id == 1) ? sf::Color::Red : sf::Color::Blue;
            
            // Cabeza (círculo pequeño)
            sf::CircleShape head(4);
            head.setPosition(position.x + 6, position.y);
            head.setFillColor(sf::Color(210, 180, 140)); // Piel
            window.draw(head);
            
            // Cuerpo (rectángulo vertical)
            sf::RectangleShape body(sf::Vector2f(8, 12));
            body.setPosition(position.x + 5, position.y + 8);
            body.setFillColor(cowboyColor);
            window.draw(body);
            
            // Brazo izquierdo (pequeña línea diagonal)
            sf::RectangleShape armLeft(sf::Vector2f(6, 2));
            armLeft.setPosition(position.x + 1, position.y + 10);
            armLeft.setFillColor(sf::Color(210, 180, 140));
            armLeft.setRotation(-30);
            window.draw(armLeft);
            
            // Pistola (triángulo simple representado con rectángulos)
            // Cañón
            if (id == 1) {
                // Vaquero 1 apunta a la derecha
                sf::RectangleShape gun(sf::Vector2f(8, 2));
                gun.setPosition(position.x + 13, position.y + 10);
                gun.setFillColor(sf::Color::Yellow);
                window.draw(gun);
            } else {
                // Vaquero 2 apunta a la izquierda
                sf::RectangleShape gun(sf::Vector2f(8, 2));
                gun.setPosition(position.x - 7, position.y + 10);
                gun.setFillColor(sf::Color::Yellow);
                window.draw(gun);
            }
            
            // Sombrero (rectángulo pequeño en la cabeza)
            sf::RectangleShape hat(sf::Vector2f(12, 2));
            hat.setPosition(position.x + 3, position.y - 1);
            hat.setFillColor(sf::Color::Black);
            window.draw(hat);
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "09_Vaqueros");
    window.setFramerateLimit(60);
    
    // Estado del juego
    enum GameState { MODE_SELECT, DIFFICULTY_SELECT, NAME_INPUT, PLAYING, GAME_OVER };
    enum GameMode { NONE, PVP, VS_BOT };
    enum GameDifficulty { EASY, MEDIUM, HARD };
    GameState gameState = MODE_SELECT;
    GameMode gameMode = NONE;
    GameDifficulty botDifficulty = MEDIUM;
    string winner = ""; // Nombre del ganador
    
    // Variables para entrada de nombres
    string player1Name = "";
    string player2Name = "";
    int currentPlayer = 1; // 1 o 2
    bool enterPressed = false;
    bool enterPressedGame = false;
    bool spacePressedGame = false;
    
    // Variables para IA del bot
    float botShootTimer = 0.0f;
    float BOT_SHOOT_INTERVAL = 1.5f; // Intervalo de disparo (se ajusta por dificultad)
    
    // Crear vaqueros (inicialmente con nombres vacíos)
    Cowboy* cowboy1 = nullptr;
    Cowboy* cowboy2 = nullptr;
    
    // Vector de balas
    vector<Bullet> bullets;
    
    // Vector de estructuras destructibles
    vector<DestructibleStructure> structures;
    
    // Reloj para el tiempo
    sf::Clock clock;
    
    // Cargar imagen de fondo
    sf::Texture backgroundTexture;
    bool backgroundLoaded = backgroundTexture.loadFromFile("./assets/images/Gemini_Generated_Image_l3zcj6l3zcj6l3zc.png");
    
    if (!backgroundLoaded) {
        cerr << "Advertencia: No se pudo cargar Gemini_Generated_Image_l3zcj6l3zcj6l3zc.png" << endl;
    }
    
    sf::Sprite backgroundSprite;
    if (backgroundLoaded) {
        backgroundSprite.setTexture(backgroundTexture);
        // Escalar el fondo para que cubra toda la ventana
        float scaleX = (float)WINDOW_WIDTH / backgroundTexture.getSize().x;
        float scaleY = (float)WINDOW_HEIGHT / backgroundTexture.getSize().y;
        backgroundSprite.setScale(scaleX, scaleY);
    }
    
    // Crear mapa aleatorio para el juego
    sf::RenderTexture gameMapTexture;
    gameMapTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
    gameMapTexture.clear(sf::Color(184, 134, 11)); // Color de arena base (dark goldenrod)
    
    // Generar elementos aleatorios del terreno
    srand(time(0));
    
    // Dibujar rocas grandes y medianas aleatorias
    for (int i = 0; i < 35; i++) {
        float x = rand() % WINDOW_WIDTH;
        float y = rand() % WINDOW_HEIGHT;
        float size = 25 + rand() % 40;
        
        // Roca principal con gradiente visual
        sf::CircleShape rock(size / 2);
        rock.setFillColor(sf::Color(139, 69, 19)); // Brown
        rock.setPosition(x, y);
        gameMapTexture.draw(rock);
        
        // Sombra oscura interior
        sf::CircleShape rockShadow(size / 3);
        rockShadow.setFillColor(sf::Color(101, 50, 15));
        rockShadow.setPosition(x + size / 4, y + size / 4);
        gameMapTexture.draw(rockShadow);
        
        // Punto de luz para efecto 3D
        sf::CircleShape rockLight(size / 6);
        rockLight.setFillColor(sf::Color(180, 100, 50));
        rockLight.setPosition(x - size / 6, y - size / 6);
        gameMapTexture.draw(rockLight);
    }
    
    // Dibujar cactus grandes y detallados
    for (int i = 0; i < 18; i++) {
        float x = rand() % WINDOW_WIDTH;
        float y = rand() % WINDOW_HEIGHT;
        
        // Tronco principal
        sf::RectangleShape trunk(sf::Vector2f(10, 50));
        trunk.setFillColor(sf::Color(34, 139, 34)); // Dark green
        trunk.setPosition(x, y);
        gameMapTexture.draw(trunk);
        
        // Líneas de textura en el tronco
        sf::RectangleShape trunkLine(sf::Vector2f(10, 2));
        trunkLine.setFillColor(sf::Color(20, 100, 20));
        for (int k = 0; k < 4; k++) {
            trunkLine.setPosition(x, y + 10 + (k * 10));
            gameMapTexture.draw(trunkLine);
        }
        
        // Brazos superiores
        for (int j = 0; j < 2; j++) {
            sf::RectangleShape arm(sf::Vector2f(28, 10));
            arm.setFillColor(sf::Color(34, 139, 34));
            arm.setPosition(x - 16, y + 8 + (j * 18));
            gameMapTexture.draw(arm);
            
            // Espinas del brazo
            sf::RectangleShape spine(sf::Vector2f(3, 8));
            spine.setFillColor(sf::Color(220, 220, 20));
            spine.setPosition(x - 18, y + 10 + (j * 18));
            gameMapTexture.draw(spine);
            spine.setPosition(x + 20, y + 10 + (j * 18));
            gameMapTexture.draw(spine);
        }
        
        // Flor en la punta (pequeño círculo rojo)
        sf::CircleShape flower(4);
        flower.setFillColor(sf::Color(255, 100, 100));
        flower.setPosition(x + 2, y - 8);
        gameMapTexture.draw(flower);
    }
    
    // Dibujar arbustos medianos
    for (int i = 0; i < 12; i++) {
        float x = rand() % WINDOW_WIDTH;
        float y = rand() % WINDOW_HEIGHT;
        float size = 15 + rand() % 25;
        
        // Arbusto de múltiples círculos
        for (int j = 0; j < 3; j++) {
            sf::CircleShape bush(size / 2);
            bush.setFillColor(sf::Color(85, 150, 85)); // Medium green
            bush.setPosition(x + (j * 10), y);
            gameMapTexture.draw(bush);
            
            // Punto oscuro en el centro para profundidad
            sf::CircleShape bushDark(size / 4);
            bushDark.setFillColor(sf::Color(50, 100, 50));
            bushDark.setPosition(x + (j * 10) + size / 6, y + size / 6);
            gameMapTexture.draw(bushDark);
        }
    }
    
    // Dibujar rocas pequeñas y piedras
    for (int i = 0; i < 40; i++) {
        float x = rand() % WINDOW_WIDTH;
        float y = rand() % WINDOW_HEIGHT;
        float size = 5 + rand() % 12;
        
        sf::CircleShape pebble(size / 2);
        pebble.setFillColor(sf::Color(160, 82, 45)); // Sienna
        pebble.setPosition(x, y);
        gameMapTexture.draw(pebble);
    }
    
    // Dibujar arena con manchas de diferentes tonos
    for (int i = 0; i < 60; i++) {
        float x = rand() % WINDOW_WIDTH;
        float y = rand() % WINDOW_HEIGHT;
        float size = 6 + rand() % 18;
        
        // Manchas claras
        sf::CircleShape sandSpot(size / 2);
        int colorVariation = rand() % 40;
        sandSpot.setFillColor(sf::Color(210 + colorVariation, 180 + colorVariation, 140 + colorVariation));
        sandSpot.setPosition(x, y);
        gameMapTexture.draw(sandSpot);
    }
    
    // Dibujar sombras de dunas (lineas oscuras)
    for (int i = 0; i < 10; i++) {
        float x = rand() % WINDOW_WIDTH;
        float y = rand() % (WINDOW_HEIGHT - 50) + 50;
        float length = 100 + rand() % 150;
        
        sf::RectangleShape duneShadow(sf::Vector2f(length, 3));
        duneShadow.setFillColor(sf::Color(150, 110, 50));
        duneShadow.setPosition(x, y);
        duneShadow.setRotation(rand() % 30 - 15);
        gameMapTexture.draw(duneShadow);
    }
    
    gameMapTexture.display();
    
    sf::Sprite gameMapSprite(gameMapTexture.getTexture());
    bool gameMapLoaded = true;
    
    // Función lambda para generar estructuras destructibles
    auto generateStructures = [&structures]() {
        structures.clear();
        
        // Generar cajas de madera (tipo 0) - destructibles en 1 disparo
        for (int i = 0; i < 6; i++) {
            float x = 80 + (rand() % (WINDOW_WIDTH - 160));
            float y = 100 + (rand() % (WINDOW_HEIGHT - 200));
            float width = 25 + rand() % 20;
            float height = 25 + rand() % 20;
            structures.emplace_back(sf::Vector2f(x, y), sf::Vector2f(width, height), 0);
        }
        
        // Generar cajas de piedra (tipo 1) - destructibles en 2 disparos
        for (int i = 0; i < 4; i++) {
            float x = 80 + (rand() % (WINDOW_WIDTH - 160));
            float y = 100 + (rand() % (WINDOW_HEIGHT - 200));
            float width = 30 + rand() % 25;
            float height = 30 + rand() % 25;
            structures.emplace_back(sf::Vector2f(x, y), sf::Vector2f(width, height), 1);
        }
        
        // Generar barriles (tipo 2) - destructibles en 1 disparo
        for (int i = 0; i < 4; i++) {
            float x = 80 + (rand() % (WINDOW_WIDTH - 160));
            float y = 100 + (rand() % (WINDOW_HEIGHT - 200));
            float size = 20 + rand() % 15;
            structures.emplace_back(sf::Vector2f(x, y), sf::Vector2f(size, size), 2);
        }
        
        // Generar torres/pilares (tipo 3) - destructibles en 3 disparos
        for (int i = 0; i < 2; i++) {
            float x = 80 + (rand() % (WINDOW_WIDTH - 160));
            float y = 100 + (rand() % (WINDOW_HEIGHT - 150));
            float width = 20 + rand() % 15;
            float height = 40 + rand() % 20;
            structures.emplace_back(sf::Vector2f(x, y), sf::Vector2f(width, height), 3);
        }
    };
    
    // Cargar imagen para modo PvP (JvsJ)
    sf::Texture pvpBackgroundTexture;
    bool pvpBackgroundLoaded = pvpBackgroundTexture.loadFromFile("./assets/images/nm2.png");
    
    if (!pvpBackgroundLoaded) {
        cerr << "Advertencia: No se pudo cargar nm2.png" << endl;
    }
    
    sf::Sprite pvpBackgroundSprite;
    if (pvpBackgroundLoaded) {
        pvpBackgroundSprite.setTexture(pvpBackgroundTexture);
        // Escalar el fondo para que cubra toda la ventana
        float scaleX = (float)WINDOW_WIDTH / pvpBackgroundTexture.getSize().x;
        float scaleY = (float)WINDOW_HEIGHT / pvpBackgroundTexture.getSize().y;
        pvpBackgroundSprite.setScale(scaleX, scaleY);
    }
    
    // Cargar imagen para modo vs Bot (dificultad)
    sf::Texture botBackgroundTexture;
    bool botBackgroundLoaded = botBackgroundTexture.loadFromFile("./assets/images/nm3.png");
    
    if (!botBackgroundLoaded) {
        cerr << "Advertencia: No se pudo cargar nm3.png" << endl;
    }
    
    sf::Sprite botBackgroundSprite;
    if (botBackgroundLoaded) {
        botBackgroundSprite.setTexture(botBackgroundTexture);
        // Escalar el fondo para que cubra toda la ventana
        float scaleX = (float)WINDOW_WIDTH / botBackgroundTexture.getSize().x;
        float scaleY = (float)WINDOW_HEIGHT / botBackgroundTexture.getSize().y;
        botBackgroundSprite.setScale(scaleX, scaleY);
    }
    
    // Cargar imágenes de dificultad
    sf::Texture easyBackgroundTexture;
    bool easyBackgroundLoaded = easyBackgroundTexture.loadFromFile("./assets/images/facil.png");
    
    sf::Sprite easyBackgroundSprite;
    if (easyBackgroundLoaded) {
        easyBackgroundSprite.setTexture(easyBackgroundTexture);
        float scaleX = (float)WINDOW_WIDTH / easyBackgroundTexture.getSize().x;
        float scaleY = (float)WINDOW_HEIGHT / easyBackgroundTexture.getSize().y;
        easyBackgroundSprite.setScale(scaleX, scaleY);
    }
    
    sf::Texture mediumBackgroundTexture;
    bool mediumBackgroundLoaded = mediumBackgroundTexture.loadFromFile("./assets/images/medio.png");
    
    sf::Sprite mediumBackgroundSprite;
    if (mediumBackgroundLoaded) {
        mediumBackgroundSprite.setTexture(mediumBackgroundTexture);
        float scaleX = (float)WINDOW_WIDTH / mediumBackgroundTexture.getSize().x;
        float scaleY = (float)WINDOW_HEIGHT / mediumBackgroundTexture.getSize().y;
        mediumBackgroundSprite.setScale(scaleX, scaleY);
    }
    
    sf::Texture hardBackgroundTexture;
    bool hardBackgroundLoaded = hardBackgroundTexture.loadFromFile("./assets/images/hard.png");
    
    sf::Sprite hardBackgroundSprite;
    if (hardBackgroundLoaded) {
        hardBackgroundSprite.setTexture(hardBackgroundTexture);
        float scaleX = (float)WINDOW_WIDTH / hardBackgroundTexture.getSize().x;
        float scaleY = (float)WINDOW_HEIGHT / hardBackgroundTexture.getSize().y;
        hardBackgroundSprite.setScale(scaleX, scaleY);
    }
    
    // Variable para rastrear la dificultad seleccionada en preview
    GameDifficulty selectedDifficulty = MEDIUM;
    
    // Cargar imágenes de victoria
    sf::Texture playerWinsTexture;
    bool playerWinsLoaded = playerWinsTexture.loadFromFile("./assets/images/vaquerowins.png");
    
    if (!playerWinsLoaded) {
        cerr << "Advertencia: No se pudo cargar vaquerowins.png" << endl;
    }
    
    sf::Sprite playerWinsSprite;
    if (playerWinsLoaded) {
        playerWinsSprite.setTexture(playerWinsTexture);
        float scaleX = (float)WINDOW_WIDTH / playerWinsTexture.getSize().x;
        float scaleY = (float)WINDOW_HEIGHT / playerWinsTexture.getSize().y;
        playerWinsSprite.setScale(scaleX, scaleY);
    }
    
    sf::Texture botWinsTexture;
    bool botWinsLoaded = botWinsTexture.loadFromFile("./assets/images/iawins.png");
    
    if (!botWinsLoaded) {
        cerr << "Advertencia: No se pudo cargar iawins.png" << endl;
    }
    
    sf::Sprite botWinsSprite;
    if (botWinsLoaded) {
        botWinsSprite.setTexture(botWinsTexture);
        float scaleX = (float)WINDOW_WIDTH / botWinsTexture.getSize().x;
        float scaleY = (float)WINDOW_HEIGHT / botWinsTexture.getSize().y;
        botWinsSprite.setScale(scaleX, scaleY);
    }
    
    // Cargar imagen de victoria para jugador 1 en modo PvP
    sf::Texture pvpPlayer1WinsTexture;
    bool pvpPlayer1WinsLoaded = pvpPlayer1WinsTexture.loadFromFile("./assets/images/gano1.png");
    
    if (!pvpPlayer1WinsLoaded) {
        cerr << "Advertencia: No se pudo cargar gano1.png" << endl;
    }
    
    sf::Sprite pvpPlayer1WinsSprite;
    if (pvpPlayer1WinsLoaded) {
        pvpPlayer1WinsSprite.setTexture(pvpPlayer1WinsTexture);
        float scaleX = (float)WINDOW_WIDTH / pvpPlayer1WinsTexture.getSize().x;
        float scaleY = (float)WINDOW_HEIGHT / pvpPlayer1WinsTexture.getSize().y;
        pvpPlayer1WinsSprite.setScale(scaleX, scaleY);
    }
    
    // Cargar imagen de victoria para jugador 2 en modo PvP
    sf::Texture pvpPlayer2WinsTexture;
    bool pvpPlayer2WinsLoaded = pvpPlayer2WinsTexture.loadFromFile("./assets/images/gano2.png");
    
    if (!pvpPlayer2WinsLoaded) {
        cerr << "Advertencia: No se pudo cargar gano2.png" << endl;
    }
    
    sf::Sprite pvpPlayer2WinsSprite;
    if (pvpPlayer2WinsLoaded) {
        pvpPlayer2WinsSprite.setTexture(pvpPlayer2WinsTexture);
        float scaleX = (float)WINDOW_WIDTH / pvpPlayer2WinsTexture.getSize().x;
        float scaleY = (float)WINDOW_HEIGHT / pvpPlayer2WinsTexture.getSize().y;
        pvpPlayer2WinsSprite.setScale(scaleX, scaleY);
    }
    
    // Cargar musicas
    sf::Music menuMusic;
    sf::Music gameMusic;
    bool menuMusicLoaded = menuMusic.openFromFile("./assets/music/cowboy-serenade_92401.ogg");
    bool gameMusicLoaded = gameMusic.openFromFile("./assets/music/musica.ogg");
    
    if (!menuMusicLoaded) {
        cerr << "Advertencia: No se cargó cowboy-serenade_92401.ogg. Asegúrate de que el archivo existe en assets/music/" << endl;
    }
    if (!gameMusicLoaded) {
        cerr << "Advertencia: No se cargó musica.ogg. Asegúrate de que el archivo existe en assets/music/" << endl;
    }
    
    menuMusic.setLoop(true);
    menuMusic.setVolume(75);
    gameMusic.setLoop(true);
    gameMusic.setVolume(75);
    
    // Cargar sonidos de efecto
    sf::SoundBuffer shootSoundBuffer;
    bool shootSoundLoaded = shootSoundBuffer.loadFromFile("./assets/music/pistol-12-gauge-self-loading-shoots-version-2-Trimmed-by-FlexClip.ogg");
    
    if (!shootSoundLoaded) {
        cerr << "Advertencia: No se cargó pistol-12-gauge-self-loading-shoots-version-2-Trimmed-by-FlexClip.ogg. Asegúrate de que el archivo existe en assets/music/" << endl;
    }
    
    // Crear sonidos de disparo (se reutilizan)
    sf::Sound shootSound1, shootSound2, shootSound3;
    shootSound1.setBuffer(shootSoundBuffer);
    shootSound2.setBuffer(shootSoundBuffer);
    shootSound3.setBuffer(shootSoundBuffer);
    shootSound1.setVolume(80);
    shootSound2.setVolume(80);
    shootSound3.setVolume(80);
    
    int lastShootSoundIndex = 0;
    
    // Cargar fuentes
    sf::Font ringFont;
    if (!ringFont.loadFromFile("./assets/fonts/Ring.ttf")) {
        cerr << "Error: No se pudo cargar Ring.ttf. Verifica que el archivo exista en assets/fonts/" << endl;
        // Continuar de todas formas para no bloquear la ejecución
    }
    sf::Text titleText;
    titleText.setFont(ringFont);
    titleText.setString("VAQUEROS");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setPosition(WINDOW_WIDTH / 2 - 180, 20);
    
    sf::Text subtitleText;
    subtitleText.setFont(ringFont);
    subtitleText.setString("Wild West Duel");
    subtitleText.setCharacterSize(24);
    subtitleText.setFillColor(sf::Color::Cyan);
    subtitleText.setPosition(WINDOW_WIDTH / 2 - 120, 90);
    
    sf::Text inputText;
    inputText.setFont(ringFont);
    inputText.setCharacterSize(15);
    inputText.setFillColor(sf::Color::White);
    
    sf::Text promptText;
    promptText.setFont(ringFont);
    promptText.setCharacterSize(20);
    promptText.setFillColor(sf::Color::White);
    
    sf::Text instructionsText;
    instructionsText.setFont(ringFont);
    instructionsText.setCharacterSize(14);
    instructionsText.setFillColor(sf::Color::Cyan);
    instructionsText.setString("Cowboy 1: A/D left/right, W/S up/down, SPACE shoot\nCowboy \n2: LEFT/RIGHT arrows, UP/DOWN arrows, ENTER shoot");
    instructionsText.setPosition(20, 450);
    
    // Puntuación y vida
    int score1 = 0, score2 = 0;
    
    sf::Text scoreText;
    scoreText.setFont(ringFont);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::Black);
    
    sf::Text nameText1;
    nameText1.setFont(ringFont);
    nameText1.setCharacterSize(16);
    nameText1.setFillColor(sf::Color::Red);
    nameText1.setPosition(20, 30);
    
    sf::Text nameText2;
    nameText2.setFont(ringFont);
    nameText2.setCharacterSize(16);
    nameText2.setFillColor(sf::Color::White);
    nameText2.setPosition(WINDOW_WIDTH - 200, 30);
    
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && gameState == MODE_SELECT) {
                // Seleccionar modo
                if (event.key.code == sf::Keyboard::Num1) {
                    gameMode = PVP;
                    gameState = NAME_INPUT;
                    currentPlayer = 1;
                    player1Name = "";
                    player2Name = "";
                } else if (event.key.code == sf::Keyboard::Num2) {
                    gameMode = VS_BOT;
                    gameState = DIFFICULTY_SELECT;
                } else if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            } else if (event.type == sf::Event::KeyPressed && gameState == DIFFICULTY_SELECT) {
                // Seleccionar dificultad del bot
                if (event.key.code == sf::Keyboard::Num1) {
                    selectedDifficulty = EASY;
                    botDifficulty = EASY;
                    BOT_SHOOT_INTERVAL = 1.8f;
                    gameState = NAME_INPUT;
                    currentPlayer = 1;
                    player1Name = "";
                    player2Name = "Bot (Easy)";
                } else if (event.key.code == sf::Keyboard::Num2) {
                    selectedDifficulty = MEDIUM;
                    botDifficulty = MEDIUM;
                    BOT_SHOOT_INTERVAL = 1.0f;
                    gameState = NAME_INPUT;
                    currentPlayer = 1;
                    player1Name = "";
                    player2Name = "Bot (Medium)";
                } else if (event.key.code == sf::Keyboard::Num3) {
                    selectedDifficulty = HARD;
                    botDifficulty = HARD;
                    BOT_SHOOT_INTERVAL = 0.5f;
                    gameState = NAME_INPUT;
                    currentPlayer = 1;
                    player1Name = "";
                    player2Name = "Bot (Hard)";
                }
            } else if (event.type == sf::Event::TextEntered && gameState == NAME_INPUT) {
                if (event.text.unicode < 128) {
                    char c = static_cast<char>(event.text.unicode);
                    if (c == '\b') { // Backspace
                        if (currentPlayer == 1) {
                            if (!player1Name.empty()) player1Name.pop_back();
                        }
                    } else if (c == '\r' || c == '\n') { // Enter
                        if (currentPlayer == 1) {
                            if (!player1Name.empty()) currentPlayer = 2;
                        } else {
                            if (!player2Name.empty() || gameMode == VS_BOT) {
                                gameState = PLAYING;
                                // Crear vaqueros con los nombres
                                cowboy1 = new Cowboy(1, 50, player1Name);
                                cowboy2 = new Cowboy(2, WINDOW_WIDTH - 50 - COWBOY_SIZE, player2Name, gameMode == VS_BOT);
                                // Generar estructuras destructibles para el nuevo mapa
                                generateStructures();
                            }
                        }
                    } else if (c >= 32 && c < 127) { // Caracteres imprimibles
                        if (currentPlayer == 1) {
                            if (player1Name.length() < 15) player1Name += c;
                        } else if (gameMode == PVP) {
                            if (player2Name.length() < 15) player2Name += c;
                        }
                    }
                }
            }
        }
        
        // ========== PANTALLA DE SELECCIÓN DE MODO ==========
        if (gameState == MODE_SELECT) {
            // Reproducir musica del menu si no está sonando
            if (menuMusicLoaded && menuMusic.getStatus() != sf::Music::Playing) {
                menuMusic.play();
            }
            
            window.clear(sf::Color::Black);
            if (backgroundLoaded) {
                window.draw(backgroundSprite);
            }
            window.draw(titleText);
            window.draw(subtitleText);
            
            sf::Text modeText;
            modeText.setFont(ringFont);
            modeText.setCharacterSize(24);
            modeText.setFillColor(sf::Color::Yellow);
            modeText.setString("SELECT GAME MODE");
            modeText.setPosition(WINDOW_WIDTH / 2 - 200, 150);
            window.draw(modeText);
            
            sf::Text pvpText;
            pvpText.setFont(ringFont);
            pvpText.setCharacterSize(20);
            pvpText.setFillColor(sf::Color::Green);
            pvpText.setString("1 - Player vs Player");
            pvpText.setPosition(WINDOW_WIDTH / 2 - 150, 250);
            window.draw(pvpText);
            
            sf::Text botText;
            botText.setFont(ringFont);
            botText.setCharacterSize(20);
            botText.setFillColor(sf::Color::Cyan);
            botText.setString("2 - Player vs Bot");
            botText.setPosition(WINDOW_WIDTH / 2 - 150, 320);
            window.draw(botText);
            
            sf::Text escText;
            escText.setFont(ringFont);
            escText.setCharacterSize(14);
            escText.setFillColor(sf::Color::Red);
            escText.setString("ESC - Exit");
            escText.setPosition(WINDOW_WIDTH / 2 - 50, 450);
            window.draw(escText);
            
            window.display();
        }
        
        // ========== PANTALLA DE SELECCIÓN DE DIFICULTAD ==========
        else if (gameState == DIFFICULTY_SELECT) {
            // Mantener musica del menu
            if (menuMusicLoaded && menuMusic.getStatus() != sf::Music::Playing) {
                menuMusic.play();
            }
            
            window.clear(sf::Color::Black);
            if (botBackgroundLoaded) {
                window.draw(botBackgroundSprite);
            }
            window.draw(titleText);
            window.draw(subtitleText);
            
            sf::Text diffText;
            diffText.setFont(ringFont);
            diffText.setCharacterSize(24);
            diffText.setFillColor(sf::Color::Yellow);
            diffText.setString("SELECT BOT DIFFICULTY");
            diffText.setPosition(WINDOW_WIDTH / 2 - 220, 150);
            window.draw(diffText);
            
            sf::Text easyText;
            easyText.setFont(ringFont);
            easyText.setCharacterSize(20);
            easyText.setFillColor(sf::Color::Green);
            easyText.setString("1 - EASY (Slow shooting)");
            easyText.setPosition(WINDOW_WIDTH / 2 - 180, 250);
            window.draw(easyText);
            
            sf::Text mediumText;
            mediumText.setFont(ringFont);
            mediumText.setCharacterSize(20);
            mediumText.setFillColor(sf::Color::Yellow);
            mediumText.setString("2 - MEDIUM (Normal)");
            mediumText.setPosition(WINDOW_WIDTH / 2 - 160, 320);
            window.draw(mediumText);
            
            sf::Text hardText;
            hardText.setFont(ringFont);
            hardText.setCharacterSize(20);
            hardText.setFillColor(sf::Color::Red);
            hardText.setString("3 - HARD (Fast & Aggressive)");
            hardText.setPosition(WINDOW_WIDTH / 2 - 210, 390);
            window.draw(hardText);
            
            window.display();
        }
        
        // ========== PANTALLA DE ENTRADA DE NOMBRES ==========
        else if (gameState == NAME_INPUT) {
            // Mantener musica del menu
            if (menuMusicLoaded && menuMusic.getStatus() != sf::Music::Playing) {
                menuMusic.play();
            }
            
            window.clear(sf::Color::Black);
            
            // Mostrar fondo según el modo
            if (gameMode == PVP && pvpBackgroundLoaded) {
                window.draw(pvpBackgroundSprite);
            } else if (gameMode == VS_BOT) {
                // Mostrar imagen de dificultad seleccionada
                if (botDifficulty == EASY && easyBackgroundLoaded) {
                    window.draw(easyBackgroundSprite);
                } else if (botDifficulty == MEDIUM && mediumBackgroundLoaded) {
                    window.draw(mediumBackgroundSprite);
                } else if (botDifficulty == HARD && hardBackgroundLoaded) {
                    window.draw(hardBackgroundSprite);
                }
            }
            
            window.draw(titleText);
            window.draw(subtitleText);
            
            promptText.setString(currentPlayer == 1 ? "Red Cowboy name:" : (gameMode == PVP ? "Blue Cowboy name:" : "Enter your name:"));
            promptText.setPosition(WINDOW_WIDTH / 2 - 200, 150);
            window.draw(promptText);
            
            inputText.setString(currentPlayer == 1 ? player1Name : player2Name);
            inputText.setPosition(WINDOW_WIDTH / 2 - 150, 250);
            window.draw(inputText);
            
            sf::Text hintText;
            hintText.setFont(ringFont);
            hintText.setCharacterSize(14);
            hintText.setFillColor(sf::Color::Green);
            hintText.setString("Press ENTER when done");
            hintText.setPosition(WINDOW_WIDTH / 2 - 120, 320);
            window.draw(hintText);
            
            if (currentPlayer == 2 && gameMode == PVP) {
                sf::Text player1Info;
                player1Info.setFont(ringFont);
                player1Info.setCharacterSize(16);
                player1Info.setFillColor(sf::Color::Red);
                player1Info.setString("Red: " + player1Name);
                player1Info.setPosition(50, 380);
                window.draw(player1Info);
            }
            
            window.display();
        }
        
        // ========== PANTALLA DE JUEGO ==========
        else if (gameState == PLAYING && cowboy1 && cowboy2) {
            // Cambiar a musica de juego si no está sonando
            if (gameMusicLoaded && gameMusic.getStatus() != sf::Music::Playing) {
                menuMusic.stop();
                gameMusic.play();
            }
            
            // CONTROLES VAQUERO 1
            cowboy1->velocity = {0, 0};
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                cowboy1->velocity.y = -COWBOY_SPEED;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                cowboy1->velocity.y = COWBOY_SPEED;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                cowboy1->velocity.x = -COWBOY_SPEED;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                cowboy1->velocity.x = COWBOY_SPEED;
            }
            // Disparo
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (!spacePressedGame) {
                    spacePressedGame = true;
                    if (cowboy1->canShoot()) {
                        sf::Vector2f spawnPos = cowboy1->getBulletSpawnPos();
                        bullets.emplace_back(spawnPos, sf::Vector2f(BULLET_SPEED, 0), 1);
                        cowboy1->startShootAnimation(); // Iniciar animación de disparo
                        cowboy1->shoot(); // Decrementar munición
                        if (shootSoundLoaded) {
                            // Reproducir solo el primer segundo del sonido
                            lastShootSoundIndex = (lastShootSoundIndex + 1) % 3;
                            sf::Sound* currentShoot = &shootSound1;
                            if (lastShootSoundIndex == 1) currentShoot = &shootSound2;
                            else if (lastShootSoundIndex == 2) currentShoot = &shootSound3;
                            currentShoot->play();
                        }
                    }
                }
            } else {
                spacePressedGame = false;
            }
            
            // Recarga Vaquero 1 (R)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                cowboy1->reload();
            }
            
            // CONTROLES VAQUERO 2
            if (gameMode == PVP) {
                // Controles humanos
                cowboy2->velocity = {0, 0};
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    cowboy2->velocity.y = -COWBOY_SPEED;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    cowboy2->velocity.y = COWBOY_SPEED;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    cowboy2->velocity.x = -COWBOY_SPEED;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    cowboy2->velocity.x = COWBOY_SPEED;
                }
                // Disparo
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                    if (!enterPressedGame) {
                        enterPressedGame = true;
                        if (cowboy2->canShoot()) {
                            sf::Vector2f spawnPos = cowboy2->getBulletSpawnPos();
                            bullets.emplace_back(spawnPos, sf::Vector2f(-BULLET_SPEED, 0), 2);
                            cowboy2->startShootAnimation(); // Iniciar animación de disparo
                            cowboy2->shoot(); // Decrementar munición
                            if (shootSoundLoaded) {
                                // Reproducir solo el primer segundo del sonido
                                lastShootSoundIndex = (lastShootSoundIndex + 1) % 3;
                                sf::Sound* currentShoot = &shootSound1;
                                if (lastShootSoundIndex == 1) currentShoot = &shootSound2;
                                else if (lastShootSoundIndex == 2) currentShoot = &shootSound3;
                                currentShoot->play();
                            }
                        }
                    }
                } else {
                    enterPressedGame = false;
                }
                
                // Recarga Vaquero 2 (P)
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    cowboy2->reload();
                }
            } else if (gameMode == VS_BOT) {
                // IA del Bot (Vaquero 2)
                cowboy2->velocity = {0, 0};
                
                // Perseguir al jugador
                float distX = cowboy1->position.x - cowboy2->position.x;
                float distY = cowboy1->position.y - cowboy2->position.y;
                
                // Comportamiento según dificultad
                if (botDifficulty == EASY) {
                    // Movimiento lento
                    if (distY > 50) {
                        cowboy2->velocity.y = COWBOY_SPEED * 0.4f;
                    } else if (distY < -50) {
                        cowboy2->velocity.y = -COWBOY_SPEED * 0.4f;
                    }
                    if (cowboy2->position.x < WINDOW_WIDTH / 2 + 150) {
                        cowboy2->velocity.x = COWBOY_SPEED * 0.3f;
                    }
                } else if (botDifficulty == MEDIUM) {
                    // Movimiento normal
                    if (distY > 30) {
                        cowboy2->velocity.y = COWBOY_SPEED * 0.8f;
                    } else if (distY < -30) {
                        cowboy2->velocity.y = -COWBOY_SPEED * 0.8f;
                    }
                    if (cowboy2->position.x < WINDOW_WIDTH / 2 + 100) {
                        cowboy2->velocity.x = COWBOY_SPEED * 0.6f;
                    }
                } else if (botDifficulty == HARD) {
                    // Movimiento rápido y agresivo
                    if (distY > 20) {
                        cowboy2->velocity.y = COWBOY_SPEED * 1.0f;
                    } else if (distY < -20) {
                        cowboy2->velocity.y = -COWBOY_SPEED * 1.0f;
                    }
                    if (cowboy2->position.x < WINDOW_WIDTH / 2 + 80) {
                        cowboy2->velocity.x = COWBOY_SPEED * 0.9f;
                    }
                }
                
                // Disparar al jugador (intervalo depende de dificultad)
                botShootTimer += dt;
                if (botShootTimer >= BOT_SHOOT_INTERVAL) {
                    botShootTimer = 0.0f;
                    // El bot recarga automáticamente si no tiene munición
                    if (!cowboy2->canShoot()) {
                        cowboy2->reload();
                    }
                    if (cowboy2->canShoot()) {
                        sf::Vector2f spawnPos = cowboy2->getBulletSpawnPos();
                        bullets.emplace_back(spawnPos, sf::Vector2f(-BULLET_SPEED, 0), 2);
                        cowboy2->startShootAnimation(); // Iniciar animación de disparo
                        cowboy2->shoot(); // Decrementar munición
                        if (shootSoundLoaded) {
                            // Reproducir solo el primer segundo del sonido
                            lastShootSoundIndex = (lastShootSoundIndex + 1) % 3;
                            sf::Sound* currentShoot = &shootSound1;
                            if (lastShootSoundIndex == 1) currentShoot = &shootSound2;
                            else if (lastShootSoundIndex == 2) currentShoot = &shootSound3;
                            currentShoot->play();
                        }
                    }
                }
            }
            
            // Actualizar vaqueros
            cowboy1->update(dt);
            cowboy2->update(dt);
            cowboy1->updateHealthBar();
            cowboy2->updateHealthBar();
            
            // Actualizar animaciones de disparo
            cowboy1->updateShootAnimation();
            cowboy2->updateShootAnimation();
            
            // Actualizar balas y detectar colisiones
            for (int i = bullets.size() - 1; i >= 0; --i) {
                bullets[i].shape.move(bullets[i].velocity * dt);
                
                // Eliminar balas fuera de pantalla
                if (bullets[i].shape.getPosition().x < 0 ||
                    bullets[i].shape.getPosition().x > WINDOW_WIDTH) {
                    bullets.erase(bullets.begin() + i);
                    continue;
                }
                
                // Detectar colisión con estructuras destructibles
                bool hitStructure = false;
                for (int j = structures.size() - 1; j >= 0; --j) {
                    if (structures[j].isHit(bullets[i].shape)) {
                        structures[j].takeDamage();
                        if (structures[j].isDestroyed()) {
                            structures.erase(structures.begin() + j);
                        }
                        hitStructure = true;
                        break;
                    }
                }
                
                if (hitStructure) {
                    bullets.erase(bullets.begin() + i);
                    continue;
                }
                
                // Detectar colisión con vaquero 1
                if (bullets[i].owner == 2 && 
                    bullets[i].shape.getGlobalBounds().intersects(cowboy1->getBounds())) {
                    cowboy1->health -= 20;
                    if (cowboy1->health < 0) cowboy1->health = 0;
                    if (cowboy1->health == 0) {
                        gameState = GAME_OVER;
                        winner = player2Name;
                    }
                    score2++;
                    bullets.erase(bullets.begin() + i);
                    continue;
                }
                
                // Detectar colisión con vaquero 2
                if (bullets[i].owner == 1 && 
                    bullets[i].shape.getGlobalBounds().intersects(cowboy2->getBounds())) {
                    cowboy2->health -= 20;
                    if (cowboy2->health < 0) cowboy2->health = 0;
                    if (cowboy2->health == 0) {
                        gameState = GAME_OVER;
                        winner = player1Name;
                    }
                    score1++;
                    bullets.erase(bullets.begin() + i);
                    continue;
                }
            }
            
            // Actualizar textos
            scoreText.setString("Red Hits: " + to_string(score1) + "  |  Blue Hits: " + to_string(score2));
            scoreText.setPosition(WINDOW_WIDTH / 2 - 150, 100);
            
            nameText1.setString(player1Name + " HP: " + to_string(cowboy1->health));
            nameText2.setString(player2Name + " HP: " + to_string(cowboy2->health));
            
            // Renderizar
            window.clear(sf::Color::Black);
            
            // Dibujar mapa estilo vaquero
            if (gameMapLoaded) {
                window.draw(gameMapSprite);
            }
            
            // Dibujar estructuras destructibles
            for (auto& structure : structures) {
                structure.draw(window);
            }
            
            // Dibujar línea central
            sf::RectangleShape centerLine(sf::Vector2f(2, WINDOW_HEIGHT));
            centerLine.setPosition(WINDOW_WIDTH / 2, 0);
            centerLine.setFillColor(sf::Color::White);
            window.draw(centerLine);
            
            // Dibujar barras de vida de fondo
            window.draw(cowboy1->healthBarBg);
            window.draw(cowboy2->healthBarBg);
            
            // Dibujar barras de vida actual
            window.draw(cowboy1->healthBar);
            window.draw(cowboy2->healthBar);
            
            // Dibujar munición
            cowboy1->drawAmmunition(window);
            cowboy2->drawAmmunition(window);
            
            // Dibujar vaqueros
            cowboy1->draw(window);
            cowboy2->draw(window);
            
            // Dibujar balas
            for (auto& bullet : bullets) {
                window.draw(bullet.shape);
            }
            
            // Dibujar UI
            window.draw(scoreText);
            window.draw(nameText1);
            window.draw(nameText2);
            
            // Actualizar instrucciones según el modo
            if (gameMode == PVP) {
                instructionsText.setString("P1: A/D LEFT/RIGHT, W/S UP/DOWN, SPACE shoot\nP2: ARROWS move, ENTER shoot");
            } else {
                instructionsText.setString("P1: A/D LEFT/RIGHT, W/S UP/DOWN, SPACE shoot\nBOT: Auto-targeting");
            }
            window.draw(instructionsText);
            
            window.display();
        }
        
        // ========== PANTALLA DE GAME OVER ==========
        else if (gameState == GAME_OVER) {
            // Detener musica de juego y volver a musica del menu
            if (gameMusic.getStatus() == sf::Music::Playing) {
                gameMusic.stop();
            }
            if (menuMusicLoaded && menuMusic.getStatus() != sf::Music::Playing) {
                menuMusic.play();
            }
            
            window.clear(sf::Color::Black);
            
            // Mostrar imagen de victoria según quién ganó y el modo
            bool playerWon = (winner == player1Name);
            
            if (gameMode == VS_BOT) {
                // En modo vs Bot, mostrar las imágenes de victoria
                if (playerWon && playerWinsLoaded) {
                    window.draw(playerWinsSprite);
                } else if (!playerWon && botWinsLoaded) {
                    window.draw(botWinsSprite);
                }
            } else if (gameMode == PVP) {
                // En modo PvP, mostrar gano1 si el jugador 1 gana, gano2 si el jugador 2 gana
                if (playerWon && pvpPlayer1WinsLoaded) {
                    window.draw(pvpPlayer1WinsSprite);
                } else if (!playerWon && pvpPlayer2WinsLoaded) {
                    window.draw(pvpPlayer2WinsSprite);
                }
            }
            
            sf::Text victoryText;
            victoryText.setFont(ringFont);
            victoryText.setString("VICTORY!");
            victoryText.setCharacterSize(80);
            victoryText.setFillColor(sf::Color::Yellow);
            victoryText.setPosition(WINDOW_WIDTH / 2 - 250, 80);
            window.draw(victoryText);
            
            sf::Text winnerText;
            winnerText.setFont(ringFont);
            winnerText.setString(winner);
            winnerText.setCharacterSize(60);
            winnerText.setFillColor(sf::Color::Green);
            winnerText.setPosition(WINDOW_WIDTH / 2 - 150, 200);
            window.draw(winnerText);
            
            sf::Text continueText;
            continueText.setFont(ringFont);
            continueText.setString("Press SPACE to return to menu");
            continueText.setCharacterSize(18);
            continueText.setFillColor(sf::Color::Cyan);
            continueText.setPosition(WINDOW_WIDTH / 2 - 200, 350);
            window.draw(continueText);
            
            // Volver al menú si presiona SPACE
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (!spacePressedGame) {
                    spacePressedGame = true;
                    gameState = MODE_SELECT;
                    gameMode = NONE;
                    player1Name = "";
                    player2Name = "";
                    currentPlayer = 1;
                    bullets.clear();
                    score1 = 0;
                    score2 = 0;
                    
                    // Liberar memoria de vaqueros
                    if (cowboy1) delete cowboy1;
                    if (cowboy2) delete cowboy2;
                    cowboy1 = nullptr;
                    cowboy2 = nullptr;
                }
            } else {
                spacePressedGame = false;
            }
            
            window.display();
        }
    }
    
    // Liberar memoria
    if (cowboy1) delete cowboy1;
    if (cowboy2) delete cowboy2;
    
    return 0;
}
