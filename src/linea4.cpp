#include <iostream>
#include <chrono>
#include <ctime>

const int MILLONES = 1000000;

struct Resultado {
    double tiempoMs;
    double cpuMs;
};

Resultado benchmarkStack() {
    auto   t0  = std::chrono::steady_clock::now();
    clock_t c0 = clock();

    for (int i = 0; i < MILLONES; i++) {
        int a = i;
        int b = a * 2;
        (void)b;
    }

    clock_t c1 = clock();
    auto   t1  = std::chrono::steady_clock::now();
    return { std::chrono::duration<double, std::milli>(t1 - t0).count(),
             (double)(c1 - c0) / CLOCKS_PER_SEC * 1000.0 };
}

Resultado benchmarkHeap() {
    auto   t0  = std::chrono::steady_clock::now();
    clock_t c0 = clock();

    for (int i = 0; i < MILLONES; i++) {
        int* a = new int(i);
        int* b = new int(*a * 2);
        delete a;
        delete b;
    }

    clock_t c1 = clock();
    auto   t1  = std::chrono::steady_clock::now();
    return { std::chrono::duration<double, std::milli>(t1 - t0).count(),
             (double)(c1 - c0) / CLOCKS_PER_SEC * 1000.0 };
}

int main() {
    std::cout << "Operaciones: " << MILLONES << " por prueba\n\n";

    std::cout << "Ejecutando Stack...\n";
    Resultado resStack = benchmarkStack();

    std::cout << "Ejecutando Heap...\n";
    Resultado resHeap = benchmarkHeap();

    double tiempoPorOpStack = (resStack.tiempoMs / MILLONES) * 1e6;
    double tiempoPorOpHeap  = (resHeap.tiempoMs  / MILLONES) * 1e6;

    std::cout << "\n--- Resultados ---\n";
    std::cout << "Stack - tiempo total:      " << resStack.tiempoMs << " ms\n";
    std::cout << "Stack - tiempo/operacion:  " << tiempoPorOpStack << " ns\n";
    std::cout << "Stack - uso CPU:           " << resStack.cpuMs << " ms\n";

    std::cout << "\n";

    std::cout << "Heap  - tiempo total:      " << resHeap.tiempoMs << " ms\n";
    std::cout << "Heap  - tiempo/operacion:  " << tiempoPorOpHeap << " ns\n";
    std::cout << "Heap  - uso CPU:           " << resHeap.cpuMs << " ms\n";

    std::cout << "\n--- Comparacion ---\n";
    std::cout << "Heap es " << (resHeap.tiempoMs / resStack.tiempoMs) << "x mas lento que Stack\n";
    std::cout << "Sobrecarga por operacion:  " << (tiempoPorOpHeap - tiempoPorOpStack) << " ns\n";
    std::cout << "CPU extra del Heap:        " << (resHeap.cpuMs - resStack.cpuMs) << " ms\n";

    return 0;
}
