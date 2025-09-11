#pragma once
#include <EstadoFoco.hpp>

class Foco
{
private:
    EstadoFoco estado;

public:
//constructor
    Foco() {
        estado = false;
    }

    //destructor
    ~Foco() {
    }

    //codigo en orientada a objetos
    void Encender(){
        //codigo en paradigma estructurado
        estado = true;
    }
    //codigo en orientada a objetos
    void Apagar(){
         //codigo en paradigma estructurado
        estado = false;

    }
    EstadoFoco MostrarEstado(){
        return estado;
        
    }

};