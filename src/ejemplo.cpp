#include <iostream>
#include <ftxui/screen/screen.hpp>
#include <thread>
#include <chrono>


using namespace std;
using namespace ftxui;
#include <dibujo.hpp>


int main(int argc, const char* argv[]) 
{
        Dimension::Full(), 
        Dimension::Fixed(10)
);
    
    Dibujo vaca({
        string("  ^__^ "), 
        string("  (oo)\\_______ "),      
        string("  (__)\\       \\/\\ "),    
        string("       ||----w |"),         
        string("       ||     || ") 
    });

    Dibujo dueño({
        string("  mmmmmm  "), 
        string("  (oo)\\_______ "),      
        string("  (__)\\       \\/\\ "),    
        string("       ||----w |"),         
        string("       ||     || ") 
    });
    
    while(true){
        dueño.MoverDerecha();
        vaca.imprimir(pantalla);
        dueño.imprimir(pantalla); 
        pantalla.Print();
        this_thread::sleep_for(chrono::seconds(100));
        pantalla.Clear();
        cout << pantalla.ResetPotition();


    }
    return 0;
}