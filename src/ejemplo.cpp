#include <iostream>
#include <ftxui/screen/screen.hpp>
#include <thread>
#include <chrono>

using namespace std;
using namespace ftxui;
string vaca[] ={
 string("  ^__^ ")     
 string("  (oo)\_______ ");      
 string("  (__)\       )\/\ ");     
 string("       ||----w |");         
 string("       ||     || ");           
};    
int main(int argc, const char* argv[]) {
    int x=0;
    Screen pantalla = Screen::Create(
        Dimension::Full(), 
        Dimension::Fixed(10)
    );

    while(true){
        int x =0;
        int y =0;
        int fila =0;

    int fila =0;
    for (auto &&linea : vaca)
    {
        Pixel &pixel = pantalla.PixelAt(x,

    }   
    cout << pantalla.ResetPosition(true);
    

    Pixel& pixel = pantalla.PixelAt(x, 5);
    pixel.character = 'A';
    pixel.background_color = Color::Blue;
    pixel.foreground_color = Color::Red;

    pantalla.Print();
    this_thread::sleep_for(chrono::seconds(1));
    x++;
    if(x==10) break;

    }


    return 0;
}