#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>

#ifdef __linux__
#include <fstream>
#include <sstream>
#endif

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#endif

long obtenerUsoRAM() {
#ifdef __linux__
    std::ifstream status("/proc/self/status");
    std::string linea;
    while (std::getline(status, linea)) {
        if (linea.find("VmRSS:") != std::string::npos) {
            std::istringstream ss(linea);
            std::string clave;
            long valor;
            ss >> clave >> valor;
            return valor;
        }
    }
    return -1;
#elif defined(_WIN32)
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
        return (long)(pmc.WorkingSetSize / 1024);
    return -1;
#else
    return -1;
#endif
}

void simularFugaDeMemoria(int iteracion, size_t tamanoBloque) {
    char* bloque = new char[tamanoBloque];
    std::memset(bloque, 'A' + (iteracion % 26), tamanoBloque);
}

int main() {
    const int    NUM_ITERACIONES = 200;
    const size_t BLOQUE_KB       = 512;
    const size_t TAMANO_BLOQUE   = BLOQUE_KB * 1024;
    const int    PAUSA_MS        = 150;

    const int MUESTRAS = 5;

    long   ramInicial    = obtenerUsoRAM();
    size_t heapAcumulado = 0;
    auto   tiempoInicio  = std::chrono::steady_clock::now();

    double tiemposPrimeras[MUESTRAS];
    double tiemposUltimas[MUESTRAS];

    std::cout << "iter | RAM (KB)\n";
    std::cout << "-----|----------\n";

    for (int i = 1; i <= NUM_ITERACIONES; i++) {
        auto t0 = std::chrono::steady_clock::now();
        simularFugaDeMemoria(i, TAMANO_BLOQUE);
        auto t1 = std::chrono::steady_clock::now();
        double duracion = std::chrono::duration<double, std::micro>(t1 - t0).count();

        heapAcumulado += TAMANO_BLOQUE;

        if (i <= MUESTRAS)
            tiemposPrimeras[i - 1] = duracion;
        if (i > NUM_ITERACIONES - MUESTRAS)
            tiemposUltimas[i - (NUM_ITERACIONES - MUESTRAS) - 1] = duracion;

        long ramActual = obtenerUsoRAM();

        if (i <= 5 || i % 10 == 0) {
            std::cout << i
                      << " | " << (ramActual >= 0 ? ramActual : -1)
                      << "\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(PAUSA_MS));
    }

    auto   tiempoFin = std::chrono::steady_clock::now();
    double segundos  = std::chrono::duration<double>(tiempoFin - tiempoInicio).count();
    long   ramFinal  = obtenerUsoRAM();

    double promPrimeras = 0, promUltimas = 0;
    for (int i = 0; i < MUESTRAS; i++) {
        promPrimeras += tiemposPrimeras[i];
        promUltimas  += tiemposUltimas[i];
    }
    promPrimeras /= MUESTRAS;
    promUltimas  /= MUESTRAS;

    std::cout << "\nTiempo total: " << segundos << " s\n";
    if (ramInicial >= 0 && ramFinal >= 0) {
        std::cout << "RAM inicial: " << ramInicial << " KB\n";
        std::cout << "RAM final:   " << ramFinal   << " KB\n";
        std::cout << "Incremento:  " << (ramFinal - ramInicial) << " KB\n";
    }
    std::cout << "\nVelocidad de asignacion (primeras " << MUESTRAS << " iters): " << promPrimeras << " us\n";
    std::cout << "Velocidad de asignacion (ultimas  " << MUESTRAS << " iters): " << promUltimas  << " us\n";
    std::cout << "Diferencia: " << (promUltimas - promPrimeras) << " us\n";

    return 0;
}
