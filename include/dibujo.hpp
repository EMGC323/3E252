#include <vector>
#include <string>
#include <list>
#include <ftxui/screen/screen.hpp>
#pragma once

using std::list;
using std::string;
using ftxui::Color;
using ftxui::Screen;
using ftxui::Pixel;

class Dibujo
{
public:
    list<string> dibujo; 
    int x = 0;
    int y = 0;
    Color fondo;
    Color color;
public:
 Dibujo(Color color, Color fondo, list<string> dibujo)
: dibujo(dibujo), x(0), y(0), fondo(fondo), color(color){}
    
void imprimir(Screen& pantalla) {
  int fila = 0;
  for (const auto& linea : dibujo) 
  {
int columna = 0;
for (char caracter : linea) 
      {
 Pixel& pixel = pantalla.PixelAt(x + columna, y + fila);
 

 pixel.background_color = fondo; 
 pixel.foreground_color = color;
 pixel.character = caracter; 
 
          columna++;
      }
      fila++;
  }
    }
    void moverDerecha() {
        x++;
    } 
    void moverIzquierda() {
        x--;
    } 
    void moverAbajo() {
        y++;
    } 
    void moverArriba() { 
        y--;
    } 
};