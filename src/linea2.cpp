#include <iostream>


void recursividadSinLimite(int contador, int array[], int size)
{
    void* direccionActual = (void*)&contador;
    static void* primeraDir = nullptr;
    if (contador == 1) 
        primeraDir = direccionActual;

    std::cout << "Profundidad: " << contador << '\n';
    contador++;
    size += 5;
    int newarray[size];
    for (int i = 0; i < size; i++)
    {
        newarray[i] = i;
    }
    
    
    if (contador > 1)
    {
        long long diferencia = (char*)primeraDir - (char*)direccionActual;
        std::cout << "  --> Memoria usada desde inicio: " << diferencia << " bytes\n";
    }
    recursividadSinLimite(contador, newarray, size);
    return;
}

int main ()
{
    int size = 5;
    int array[size] = {1,2,3,4,5};
    recursividadSinLimite(1, array, size);
    return 0;
}
