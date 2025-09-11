

#include <SerieNavidad.hpp>
#include <Foco.hpp>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{

    SerieNavidad miSerieNavidad;
    miSerieNavidad.Encender();
    miSerieNavidad.Imprimirserie();
    miSerieNavidad.Apagar();
    miSerieNavidad.Imprimirserie();




   Foco foco;
   foco.Apagar();
   foco.Encender();


    cout <<"Foco :"<<foco.MostrarEstado()<<endl;
    return 0;
}


