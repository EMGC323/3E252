#include <iostream>
#include <string>
#include <ftxui/screen/screen.hpp>
#include <thread>
#include <chrono>
#include <dibujo.hpp>
using namespace std;
using namespace ftxui;

int main() {
    Screen pantalla = Screen::Create(
        Dimension::Full(),
        Dimension::Fixed(30)
    );

    Dibujo camion(
        Color::White,
        Color::Black,
        {
            string("    _____________"),
            string("  _/_|[][][][][] | - -"),
            string(" (Autobús urbano | - -"),
            string(" =--OO-------OO--=dwb")
        });

    Dibujo carro(
        Color::Yellow,
        Color::Black,
        {
            string("  ______"),
            string(" /|_||_\\`.__"),
            string("(   _    _ _\\"),
            string("=`-(_)--(_)-'")
        });

    carro.x = 0;
    carro.y = 10;
    camion.x = 60;
    camion.y = 10;

    for (int i = 0; i < 100; ++i) {
        pantalla.Clear();

        carro.moverDerecha();
        camion.moverIzquierda();

        carro.imprimir(pantalla);
        camion.imprimir(pantalla);
        pantalla.Print();
        if (carro.x + 15 >= camion.x) {
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(100));
    }
    pantalla.Clear();
    std::string mensaje = "💥 ¡CHOQUE! 💥";
    int x_centro = 30;
    int y_centro = 15;

    for (size_t i = 0; i < mensaje.size(); ++i) {
        Pixel& pixel = pantalla.PixelAt(x_centro + i, y_centro);
        pixel.character = mensaje[i];
        pixel.foreground_color = Color::Red;
    }

    pantalla.Print();

    this_thread::sleep_for(chrono::seconds(3));
    pantalla.Clear();

    return 0;
}