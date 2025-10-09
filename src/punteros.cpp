#include <iostream>
#include <cstdint>
int main()
{
    int *pNum = NULL;

    pNum = new int;
    
    *pNum = 25;

    std::cout << "direccion: " << pNum << '\n';
    std::cout << "valor: " << pNum << '\n';
    std::cout << "direccion del puntero: " << &pNum << '\n';
    
    std::cout << "Tipos de dato: " << '\n';

    std::cout << "tamaño int: " << sizeof(int) << '\n';

    std::cout << "Tamaño long: " << sizeof(long) << '\n';
    std::cout << "Tamaño float: " << sizeof(float) << '\n';
    std::cout << "Tamaño double: " << sizeof(double) << '\n';
    std::cout << "Tamaño char: " << sizeof(char) << '\n';
    std::cout << "Tamaño bool: " << sizeof(bool) << '\n';
    std::cout << "Tamaño byte: " << sizeof(std::byte) << '\n';


    return 0;
}
