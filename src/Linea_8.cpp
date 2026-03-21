#include <iostream>
#include <cstdio>

using namespace std;

int VariableGlobal = 1; //debe de guardarse en .data

int globalSinInicializar; //Debe de guardarse en .bss

int numero = 5; //Es global se guarda en .data

void funcion()
{
    static int estatica = 5; // estatica inicializada debe de guardarse en .data

    int contadorLocal = 0; // variable local debe de guardarse en stack

    int numero = 10; //Sobreescribe a la variable global numero

    contadorLocal++; //Su valor se reinicia en cada llamada
    estatica++; //Su valor se guarda
    VariableGlobal++;

    printf("\n--- Dentro de funcion() ---\n");

    printf("estatica valor: %d\n", estatica);
    printf("estatica direccion: %p\n", (void*)&estatica);

    printf("contadorLocal valor: %d\n", contadorLocal);
    printf("contadorLocal direccion: %p\n", (void*)&contadorLocal);

    printf("Local numero: %d, direccion: %p\n", numero, (void*)&numero);
    printf("Variable global: %d, direccion: %p\n", VariableGlobal, (void*)&VariableGlobal);

}

int main()
{
    printf("--- Variables globales ---\n");

    printf("numeroGlobal (.data)\n");
    printf("valor: %d\n", VariableGlobal);
    printf("direccion: %p\n", (void*)&VariableGlobal);

    printf("\nglobalBSS (.bss)\n");
    printf("valor: %d\n", globalSinInicializar);
    printf("direccion: %p\n", (void*)&globalSinInicializar);

    printf("Global numero: %d, direccion: %p\n", numero, (void*)&numero);

    
    printf("\n--- Llamadas a funcion() ---\n");
    for (size_t i = 0; i < 3; i++) //LLama la funcion 5 veces
    {
        funcion();
    }
    return 0;
}