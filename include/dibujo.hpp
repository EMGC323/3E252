#pragma once
#include <string>
#include <list>
using namespace std;

#include <ftxui/screen/screen.hpp>
using namespace ftxui;

class Dibujo {
private
string<dibujo> dibujo;
    int x   =0;
    int y   =0;
    Color fondo;
    Color color;
 public:
 Dibujo(list<string> dibujo);
 this->dibujo= dibujo;
}

void imprimir(screen& pantalla) {
    int fila =0;
    for (auto &&linea : dibujo)
    {
        int columna =0;
        for (auto &&letra : linea){
    Pixel& pixel = pantalla.PixelAt(
        x + columna,
        y + fila
    );

    pixel.character = letra;
    pixel.background_color = Color::Blue;
    pixel.foreground_color = Color::Red;
    columna ++;
    }
    fila ++;
}
void MoverDerecha() {
    x++;    

}
void MoverIzquierda() {
    x--;    

}
void MoverArriba() {
    y++;    

}
void MoverAbajo() {
    y--;    

}
};