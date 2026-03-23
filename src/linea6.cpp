#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main()
{
    srand(time(NULL));

    const int BLOQUES = 100;
    const int RONDAS = 100000;

    char* bloques[BLOQUES] = {NULL};
    int tamanos[BLOQUES];

    long long tiempoInicial = 0;
    long long tiempoPrimeraMitad = 0;
    long long tiempoSegundaMitad = 0;
    long long tiempoMayor = 0;

    int asignacionesIniciales = 0;
    int asignacionesPrimeraMitad = 0;
    int asignacionesSegundaMitad = 0;
    int fallos = 0;

    cout << "Primera reserva de bloques en el Heap" << endl;

    for (int i = 0; i < BLOQUES; i++)
    {
        tamanos[i] = 50 + rand() % 500;

        auto inicio = high_resolution_clock::now();
        bloques[i] = (char*)malloc(tamanos[i]);
        auto fin = high_resolution_clock::now();

        long long tiempo = duration_cast<nanoseconds>(fin - inicio).count();

        tiempoInicial += tiempo;
        asignacionesIniciales++;

        if (tiempo > tiempoMayor)
        {
            tiempoMayor = tiempo;
        }

        if (bloques[i] == NULL)
        {
            fallos++;
        }

        cout << "Bloque " << i
             << " | tamano " << tamanos[i]
             << " | direccion " << (void*)bloques[i]
             << " | tiempo " << tiempo << " ns" << endl;
    }

    cout << endl;
    cout << "Nuevos bloques asignados en algunas rondas" << endl;

    for (int ronda = 1; ronda <= RONDAS; ronda++)
    {
        int pos = rand() % BLOQUES;

        if (bloques[pos] != NULL)
        {
            free(bloques[pos]);
            bloques[pos] = NULL;
        }

        tamanos[pos] = 50 + rand() % 1000;

        auto inicio = high_resolution_clock::now();
        bloques[pos] = (char*)malloc(tamanos[pos]);
        auto fin = high_resolution_clock::now();

        long long tiempo = duration_cast<nanoseconds>(fin - inicio).count();

        if (ronda <= RONDAS / 2)
        {
            tiempoPrimeraMitad += tiempo;
            asignacionesPrimeraMitad++;
        }
        else
        {
            tiempoSegundaMitad += tiempo;
            asignacionesSegundaMitad++;
        }

        if (tiempo > tiempoMayor)
        {
            tiempoMayor = tiempo;
        }

        if (bloques[pos] == NULL)
        {
            fallos++;
        }

        if (ronda % 10000 == 0)
        {
            cout << "Ronda " << ronda
                 << " | bloque " << pos
                 << " | tamano " << tamanos[pos]
                 << " | direccion " << (void*)bloques[pos]
                 << " | tiempo " << tiempo << " ns" << endl;
        }
    }

    cout << endl;
    cout << "Direcciones finales en el Heap (al finalizar todas las rondas)" << endl;

    for (int i = 0; i < BLOQUES; i++)
    {
        cout << "Bloque " << i
             << " | tamano " << tamanos[i]
             << " | direccion " << (void*)bloques[i] << endl;
    }

    cout << endl;
    cout << "Comparacion entre bloques consecutivos" << endl;

    int contiguos = 0;
    int noContiguos = 0;

    for (int i = 0; i < BLOQUES - 1; i++)
    {
        if (bloques[i] != NULL && bloques[i + 1] != NULL)
        {
            char* finBloqueActual = bloques[i] + tamanos[i];

            cout << "Bloque " << i
                 << " termina en " << (void*)finBloqueActual
                 << " | Bloque " << i + 1
                 << " empieza en " << (void*)bloques[i + 1];

            if (finBloqueActual == bloques[i + 1])
            {
                cout << " | contiguos" << endl;
                contiguos++;
            }
            else
            {
                cout << " | no contiguos" << endl;
                noContiguos++;
            }
        }
    }

    cout << endl;
    cout << "Pares contiguos: " << contiguos << endl;
    cout << "Pares no contiguos: " << noContiguos << endl;

    cout << endl;
    cout << "Promedio de malloc en la primera mitad del experimento: "
         << (double)tiempoPrimeraMitad / asignacionesPrimeraMitad << " ns" << endl;

    cout << "Promedio de malloc en la segunda mitad del experimento: "
         << (double)tiempoSegundaMitad / asignacionesSegundaMitad << " ns" << endl;

    cout << "Mayor tiempo de malloc observado: "
         << tiempoMayor << " ns" << endl;

    cout << "Fallos de asignacion: " << fallos << endl;

    for (int i = 0; i < BLOQUES; i++)
    {
        free(bloques[i]);
        bloques[i] = NULL;
    }

    return 0;
}