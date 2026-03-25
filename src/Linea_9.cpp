#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdio>
using namespace std;

//El programa retorna la profundida de cada funcion,tiempo y ademas cuenta aproximadamente cuanta memoria uso
//Para calcular la memoria toma como referencia la direccion de una variable y despues la utliza para sacar la diferencia

long long stackBase;

//Version iterativa
bool buscarIterativo(const vector<string>& lista, const string& nombre, int &profundidadIteracion, long long &stackUso)
{
    int referenciaIterativa;
    profundidadIteracion = 0;
    stackUso = llabs(stackBase - (long long)&referenciaIterativa);

    for(int i = 0; i < lista.size(); i++)
    {
        profundidadIteracion++;
        if(lista[i] == nombre)
            return true;
    }
    return false;
}

// Versión recursiva
bool buscarRecursivo(const vector<string>& lista, const string& nombre, int index, int &profundidad, long long &stackMax)
{
    int referenciaRecursiva;
    long long usoActual = llabs(stackBase - (long long)&referenciaRecursiva);
    if(usoActual > stackMax)
        stackMax = usoActual;

    profundidad++;

    if(index >= lista.size())
        return false;

    if(lista[index] == nombre)
        return true;

    return buscarRecursivo(lista, nombre, index + 1, profundidad, stackMax);
}

int main()
{
    vector<string> lista;
    for(int i = 0; i < 100000; i++)
        lista.push_back("Persona" + to_string(i));

    string nombreBuscado = "Persona9999";

    int baseVariable;
    stackBase = (long long)&baseVariable;

    const int REPETICIONES = 100000;

    // Iterativo
    int pasosIter = 0;
    long long stackIter = 0;
    auto inicioIter = chrono::high_resolution_clock::now();
    for(int i = 0; i < REPETICIONES; i++)
        buscarIterativo(lista, nombreBuscado, pasosIter, stackIter);
    auto finIter = chrono::high_resolution_clock::now();
    auto tiempoIter = chrono::duration_cast<chrono::milliseconds>(finIter - inicioIter);

    // Recursivo
    long long stackRec = 0;
    int profundidadMaxima = 0;
    auto inicioRec = chrono::high_resolution_clock::now();
    for(int i = 0; i < REPETICIONES; i++) {
        int profundidad = 0; // reiniciar cada vez
        buscarRecursivo(lista, nombreBuscado, 0, profundidad, stackRec);

        if (profundidad > profundidadMaxima)
            profundidadMaxima = profundidad;
    }
    auto finRec = chrono::high_resolution_clock::now();
    auto tiempoRec = chrono::duration_cast<chrono::milliseconds>(finRec - inicioRec);

    // Resultados con printf
    printf("\n--- RESULTADOS ---\n");

    printf("\nIterativo\n");
    printf("Profundidad iterativa: %d\n", pasosIter);
    printf("Tiempo acumulado (iterativo): %lld ms\n", (long long)tiempoIter.count());
    printf("Uso de stack (iterativo): %lld bytes\n", stackIter);

    printf("\nRecursivo\n");
    printf("Profundidad recursiva: %d\n", profundidadMaxima);
    printf("Tiempo acumulado (recursivo): %lld ms\n", (long long)tiempoRec.count());
    printf("Uso de stack (recursivo): %lld bytes\n", stackRec);
    return 0;
}