#pragma once
#include <Foco.hpp>
using namespace std;

class SerieNavidad
{
private:
    Foco focos[10];
public:
    SerieNavidad() {}
    ~SerieNavidad() {}

    void Encender(){
        for (int numFoco = 0; numFoco < 10; numFoco++) 
        {
    focos[numFoco].Encender();

        }
        
    }

    void Apagar(){
        for (int numFoco = 0; numFoco < 10; numFoco++) 
        {
    focos[numFoco].Apagar();
    
        }
        
    }

    void Imprimirserie(){
        for (int numFoco = 0; numFoco < 10; numFoco++) 
        {
    cout <<focos[numFoco].MostrarEstado();<<endl
    
        }
        
    }
};