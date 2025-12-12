#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Crear ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "012 - Animacion Vaquero Disparo");
    window.setFramerateLimit(60);

    // Cargar spritesheet de vaquero disparando
    sf::Texture spritesheet;
    if (!spritesheet.loadFromFile("./assets/images/vaquerodispara.png")) {
        std::cerr << "Error: No se pudo cargar vaquerodispara.png" << std::endl;
        return -1;
    }

    // Crear sprite para la animación
    sf::Sprite vaqueroSprite(spritesheet);
    
    // Configurar posición inicial (centrada aproximadamente)
    vaqueroSprite.setPosition(200.0f, 150.0f);
    
    // Agrandar el sprite para que se vea mejor
    vaqueroSprite.setScale(3.0f, 3.0f);
    
    // Variables de animación
    int currentFrame = 0;
    float frameTimer = 0.0f;
    const float FRAME_DURATION = 0.15f;  // Duración de cada frame en segundos
    const int FRAMES_COUNT = 4;           // Total de frames en el spritesheet
    const int FRAME_WIDTH = 100;          // Ancho de cada frame
    const int FRAME_HEIGHT = 100;         // Alto de cada frame

    // Loop principal
    while (window.isOpen()) {
        float dt = 1.0f / 60.0f;  // Delta time
        
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        // Actualizar animación
        frameTimer += dt;
        if (frameTimer >= FRAME_DURATION) {
            frameTimer = 0.0f;
            currentFrame = (currentFrame + 1) % FRAMES_COUNT;
        }

        // Establecer el área del spritesheet a mostrar (texCoords)
        vaqueroSprite.setTextureRect(sf::IntRect(
            currentFrame * FRAME_WIDTH,  // x
            0,                           // y
            FRAME_WIDTH,                 // ancho
            FRAME_HEIGHT                 // alto
        ));

        // Limpiar pantalla con color azul claro
        window.clear(sf::Color(100, 150, 200));

        // Dibujar sprite
        window.draw(vaqueroSprite);

        // Mostrar instrucciones
        sf::Font font;
        // Si no hay fuente disponible, solo dibujar el sprite sin texto

        // Mostrar frame actual en consola (opcional)
        static int lastFrame = -1;
        if (currentFrame != lastFrame) {
            std::cout << "Frame: " << currentFrame << std::endl;
            lastFrame = currentFrame;
        }

        // Mostrar ventana
        window.display();
    }

    return 0;
}
