#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    // Crear una ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "010_Textovaq - Wild West Typography");
    window.setFramerateLimit(60);

    // Cargar fuentes
    sf::Font ringFont;
    if (!ringFont.loadFromFile("./assets/fonts/Ring.ttf"))
    {
        cerr << "Error cargando fuente Ring.ttf" << endl;
        return -1;
    }

    sf::Font minecraftFont;
    if (!minecraftFont.loadFromFile("./assets/fonts/Minecraft.ttf"))
    {
        cerr << "Error cargando fuente Minecraft.ttf" << endl;
        return -1;
    }

    // Título principal con fuente Ring (más western)
    sf::Text titleText;
    titleText.setFont(ringFont);
    titleText.setString("WILD WEST");
    titleText.setCharacterSize(80);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setPosition(150, 50);
    
    // Subtítulo
    sf::Text subtitleText;
    subtitleText.setFont(minecraftFont);
    subtitleText.setString("Text & Typography Example");
    subtitleText.setCharacterSize(20);
    subtitleText.setFillColor(sf::Color::Cyan);
    subtitleText.setPosition(200, 140);

    // Texto animado de vaquero
    sf::Text cowboyText;
    cowboyText.setFont(ringFont);
    cowboyText.setString("VAQUEROS");
    cowboyText.setCharacterSize(50);
    cowboyText.setFillColor(sf::Color::Red);
    cowboyText.setPosition(220, 220);

    // Textos descriptivos
    sf::Text descText1;
    descText1.setFont(minecraftFont);
    descText1.setString("Font 1: Ring - Western Style");
    descText1.setCharacterSize(14);
    descText1.setFillColor(sf::Color::White);
    descText1.setPosition(50, 310);

    sf::Text descText2;
    descText2.setFont(minecraftFont);
    descText2.setString("Font 2: Minecraft - Blocky Style");
    descText2.setCharacterSize(14);
    descText2.setFillColor(sf::Color::White);
    descText2.setPosition(50, 370);

    // Información
    sf::Text infoText;
    infoText.setFont(minecraftFont);
    infoText.setString("Press any key to change colors\nPress ESC to exit");
    infoText.setCharacterSize(12);
    infoText.setFillColor(sf::Color::Green);
    infoText.setPosition(200, 480);

    // Colores para el ciclo
    sf::Color colors[] = {
        sf::Color::Yellow,
        sf::Color::Red,
        sf::Color::Magenta,
        sf::Color::Green,
        sf::Color::Cyan,
        sf::Color::White
    };
    int colorIndex = 0;
    int colorCount = 6;

    // Reloj para animación
    sf::Clock clock;
    bool keyPressed = false;

    while (window.isOpen())
    {
        float elapsed = clock.getElapsedTime().asSeconds();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                else if (!keyPressed)
                {
                    keyPressed = true;
                    colorIndex = (colorIndex + 1) % colorCount;
                    cowboyText.setFillColor(colors[colorIndex]);
                }
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                keyPressed = false;
            }
        }

        // Animación de escala para el título
        float scale = 1.0f + 0.1f * sin(elapsed * 2.0f);
        titleText.setScale(scale, scale);

        // Animación de rotación para VAQUEROS
        cowboyText.setRotation(5.0f * sin(elapsed * 1.5f));

        // Cambiar color dinámico del subtítulo
        int colorValue = static_cast<int>(128 + 127 * sin(elapsed));
        subtitleText.setFillColor(sf::Color(colorValue, 255, 100));

        // Renderizar
        window.clear(sf::Color::Black);

        // Dibujar fondo degradado
        sf::RectangleShape background(sf::Vector2f(800, 600));
        background.setFillColor(sf::Color(30, 20, 10)); // Color marrón oscuro (western)
        window.draw(background);

        // Dibujar decoración (líneas)
        sf::RectangleShape topLine(sf::Vector2f(800, 3));
        topLine.setPosition(0, 40);
        topLine.setFillColor(sf::Color::Yellow);
        window.draw(topLine);

        sf::RectangleShape bottomLine(sf::Vector2f(800, 3));
        bottomLine.setPosition(0, 160);
        bottomLine.setFillColor(sf::Color::Yellow);
        window.draw(bottomLine);

        // Dibujar textos
        window.draw(titleText);
        window.draw(subtitleText);
        window.draw(cowboyText);
        window.draw(descText1);
        window.draw(descText2);
        window.draw(infoText);

        // Estadísticas
        sf::Text statsText;
        statsText.setFont(minecraftFont);
        statsText.setCharacterSize(10);
        statsText.setFillColor(sf::Color::White);
        statsText.setString("FPS: 60 | Fonts Loaded: 2");
        statsText.setPosition(600, 570);
        window.draw(statsText);

        window.display();
    }

    return 0;
}
