#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "011_AudioVaq - Musica Vaquera");
    window.setFramerateLimit(60);
    
    // Cargar fuentes
    sf::Font ringFont;
    if (!ringFont.loadFromFile("./assets/fonts/Ring.ttf")) {
        cerr << "Error cargando fuente Ring.ttf" << endl;
        // Continuar de todas formas
    }
    
    // Cargar musicas
    sf::Music menuMusic;
    sf::Music gameMusic;
    
    bool menuMusicLoaded = menuMusic.openFromFile("./assets/music/menu_theme.ogg");
    bool gameMusicLoaded = gameMusic.openFromFile("./assets/music/game_theme.ogg");
    
    if (!menuMusicLoaded) {
        cerr << "Advertencia: No se pudo cargar menu_theme.ogg\n";
        cerr << "Coloca un archivo OGG en: assets/music/menu_theme.ogg\n";
    }
    if (!gameMusicLoaded) {
        cerr << "Advertencia: No se pudo cargar game_theme.ogg\n";
        cerr << "Coloca un archivo OGG en: assets/music/game_theme.ogg\n";
    }
    
    // Configurar musica
    menuMusic.setLoop(true);
    menuMusic.setVolume(80);
    gameMusic.setLoop(true);
    gameMusic.setVolume(80);
    
    // Estados
    enum GameState { MENU, PLAYING, GAME_OVER };
    GameState gameState = MENU;
    bool musicStarted = false;
    
    // Textos
    sf::Text titleText;
    titleText.setFont(ringFont);
    titleText.setString("VAQUEROS MUSIC");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setPosition(WINDOW_WIDTH / 2 - 250, 50);
    
    sf::Text subtitleText;
    subtitleText.setFont(ringFont);
    subtitleText.setString("Presiona SPACE para comenzar");
    subtitleText.setCharacterSize(18);
    subtitleText.setFillColor(sf::Color::Cyan);
    subtitleText.setPosition(WINDOW_WIDTH / 2 - 150, 130);
    
    sf::Text instructionText;
    instructionText.setFont(ringFont);
    instructionText.setCharacterSize(16);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(50, 180);
    instructionText.setString("Musica Menu:\n(Se reproduce en bucle)\n\n\n"
                             "Presiona:\n"
                             "SPACE - Comenzar juego\n"
                             "ESC - Salir");
    
    sf::Text statusText;
    statusText.setFont(ringFont);
    statusText.setCharacterSize(14);
    statusText.setFillColor(sf::Color::Green);
    statusText.setPosition(50, 450);
    
    // Reproducir musica del menu
    if (menuMusicLoaded) {
        menuMusic.play();
    }
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else if (event.key.code == sf::Keyboard::Space) {
                    if (gameState == MENU) {
                        gameState = PLAYING;
                        menuMusic.stop();
                        if (gameMusicLoaded) {
                            gameMusic.play();
                        }
                    } else if (gameState == GAME_OVER) {
                        gameState = MENU;
                        gameMusic.stop();
                        if (menuMusicLoaded) {
                            menuMusic.play();
                        }
                    }
                }
            }
        }
        
        window.clear(sf::Color::Black);
        
        if (gameState == MENU) {
            window.draw(titleText);
            window.draw(subtitleText);
            window.draw(instructionText);
            
            string statusStr = "Estado: ";
            statusStr += menuMusicLoaded ? (menuMusic.getStatus() == sf::Music::Playing ? "Reproduciendo Menu" : "Pausado") : "Musica no cargada";
            statusText.setString(statusStr);
            window.draw(statusText);
        }
        else if (gameState == PLAYING) {
            // Pantalla de juego
            sf::Text gameTitle;
            gameTitle.setFont(ringFont);
            gameTitle.setString("EN JUEGO");
            gameTitle.setCharacterSize(60);
            gameTitle.setFillColor(sf::Color::Yellow);
            gameTitle.setPosition(WINDOW_WIDTH / 2 - 150, 50);
            window.draw(gameTitle);
            
            sf::Text gameText;
            gameText.setFont(ringFont);
            gameText.setCharacterSize(24);
            gameText.setFillColor(sf::Color::Cyan);
            gameText.setPosition(WINDOW_WIDTH / 2 - 200, 150);
            gameText.setString("Sonando musica de juego...\n\nPresiona SPACE para terminar");
            window.draw(gameText);
            
            string statusStr = "Estado: ";
            statusStr += gameMusicLoaded ? (gameMusic.getStatus() == sf::Music::Playing ? "Reproduciendo Juego" : "Pausado") : "Musica no cargada";
            statusText.setString(statusStr);
            statusText.setPosition(WINDOW_WIDTH / 2 - 150, 450);
            window.draw(statusText);
            
            // Cambiar de estado al presionar espacio nuevamente
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                // Esperar a que se suelte la tecla
                sf::sleep(sf::milliseconds(200));
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    gameState = GAME_OVER;
                    gameMusic.stop();
                }
            }
        }
        else if (gameState == GAME_OVER) {
            sf::Text gameOverText;
            gameOverText.setFont(ringFont);
            gameOverText.setString("FIN DEL JUEGO");
            gameOverText.setCharacterSize(60);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(WINDOW_WIDTH / 2 - 200, 100);
            window.draw(gameOverText);
            
            sf::Text continueText;
            continueText.setFont(ringFont);
            continueText.setCharacterSize(24);
            continueText.setFillColor(sf::Color::Cyan);
            continueText.setPosition(WINDOW_WIDTH / 2 - 180, 250);
            continueText.setString("Presiona SPACE para volver al menu");
            window.draw(continueText);
            
            // Volver al menu
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                sf::sleep(sf::milliseconds(200));
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    gameState = MENU;
                    if (menuMusicLoaded) {
                        menuMusic.play();
                    }
                }
            }
        }
        
        window.display();
    }
    
    return 0;
}
