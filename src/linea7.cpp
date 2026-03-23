#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct Datos
{
    int arreglo[50000];
};

int porValor(Datos datos)
{
    return datos.arreglo[0];
}

int porReferencia(Datos& datos)
{
    return datos.arreglo[0];
}

int main()
{
    const int REPETICIONES = 5000;

    Datos datos;

    for (int i = 0; i < 50000; i++)
    {
        datos.arreglo[i] = i;
    }

    cout << "En main, la estructura original esta " << &datos << endl;
    cout << "La estructura mide " << sizeof(datos) << " bytes" << endl;
    cout << endl;

    Datos copia = datos;

    cout << "Al hacer una copia, la nueva estructura queda en " << &copia << endl;
    cout << "Aqui se esta pasando por valor (copia), por eso queda en otra direccion" << endl;
    cout << endl;

    cout << "Por referencia, se trabaja con la estructura original en " << &datos << endl;
    cout << "No se crea una copia" << endl;
    cout << endl;

    long long sumaValor = 0;
    long long sumaReferencia = 0;

    auto inicioValor = high_resolution_clock::now();

    for (int i = 0; i < REPETICIONES; i++)
    {
        sumaValor += porValor(datos);
    }

    auto finValor = high_resolution_clock::now();

    auto inicioReferencia = high_resolution_clock::now();

    for (int i = 0; i < REPETICIONES; i++)
    {
        sumaReferencia += porReferencia(datos);
    }

    auto finReferencia = high_resolution_clock::now();

    long long tiempoValor = duration_cast<nanoseconds>(finValor - inicioValor).count();
    long long tiempoReferencia = duration_cast<nanoseconds>(finReferencia - inicioReferencia).count();

    cout << "Tiempo de ejecucion por valor: " << tiempoValor << " ns" << endl;
    cout << "Tiempo de ejecucion por referencia: " << tiempoReferencia << " ns" << endl;
    cout << endl;

    cout << "Tiempo promedio por valor: " << (double)tiempoValor / REPETICIONES << " ns" << endl;
    cout << "Tiempo promedio por referencia: " << (double)tiempoReferencia / REPETICIONES << " ns" << endl;
    cout << endl;

    cout << "Cuando se pasa por valor, en cada llamada se copia una estructura de "
         << sizeof(datos) << " bytes (en el Stack)" << endl;

    cout << "En " << REPETICIONES << " llamadas por valor, se copian aproximadamente "
         << (unsigned long long)sizeof(datos) * REPETICIONES << " bytes" << endl;

    cout << "Por referencia, no se copia toda la estructura en cada llamada porque se trabaja con la estructura original que ya existia" << endl;
    cout << endl;

    return 0;
}