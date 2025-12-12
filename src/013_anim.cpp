#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Crear ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "013 - Animacion Disparo Vaquero 1");
    window.setFramerateLimit(60);

    // Cargar primera imagen de animación
    sf::Texture frame1Texture;
    if (!frame1Texture.loadFromFile("./assets/images/pixil-frame-0.png")) {
        std::cerr << "Error: No se pudo cargar pixil-frame-0.png" << std::endl;
        return -1;
    }

    // Cargar segunda imagen de animación
    sf::Texture frame2Texture;
    if (!frame2Texture.loadFromFile("./assets/images/pixil-frame-0 (1).png")) {
        std::cerr << "Error: No se pudo cargar pixil-frame-0 (1).png" << std::endl;
        return -1;
    }

    // Crear sprite para la animación
    sf::Sprite animSprite;
    animSprite.setPosition(350.0f, 250.0f);
    animSprite.setScale(2.0f, 2.0f); // Escalar 2x para mejor visualización
    
    // Variables de animación
    int currentFrame = 0;
    float frameTimer = 0.0f;
    const float FRAME_DURATION = 0.2f; // Duración de cada frame en segundos

    // Loop principal
    while (window.isOpen()) {
        float dt = 1.0f / 60.0f; // Delta time
        
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
            currentFrame = (currentFrame + 1) % 2; // Alternar entre 2 frames
        }

        // Establecer la textura y rotación según el frame actual
        if (currentFrame == 0) {
            animSprite.setTexture(frame1Texture);
            animSprite.setRotation(90); // Rotada 90 grados a la derecha
        } else {
            animSprite.setTexture(frame2Texture);
            animSprite.setRotation(90); // Rotada 90 grados a la derecha
        }

        // Mostrar frame actual en consola
        static int lastFrame = -1;
        if (currentFrame != lastFrame) {
            std::cout << "Frame: " << currentFrame << " | Rotacion: " << animSprite.getRotation() << " grados" << std::endl;
            lastFrame = currentFrame;
        }

        // Limpiar pantalla con color azul claro
        window.clear(sf::Color(100, 150, 200));

        // Dibujar sprite
        window.draw(animSprite);

        // Mostrar instrucciones en pantalla
        sf::Font font;
        if (font.loadFromFile("./assets/fonts/Ring.ttf")) {
            sf::Text instructionsText;
            instructionsText.setFont(font);
            instructionsText.setString("Animacion de Disparo - Vaquero 1\n\nFrame 0: Rotada 90 grados\nFrame 1: Rotada 90 grados\n\nESC para salir");
            instructionsText.setCharacterSize(16);
            instructionsText.setFillColor(sf::Color::White);
            instructionsText.setPosition(20, 20);
            window.draw(instructionsText);
        }

        // Mostrar ventana
        window.display();
    }

    return 0;
}
