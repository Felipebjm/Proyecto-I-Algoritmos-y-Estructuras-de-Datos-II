#include <iostream>
#include <chrono>
#include <vector>
#include <cstring>

// Incluye lo necesario para correr dependiendo del el sistema operativo
#ifdef _WIN32
    #include <windows.h>
    #include <psapi.h>
    #pragma comment(lib, "psapi.lib")
    
#else
    #include <fstream>
    #include <string>
#endif

//Obtiene la RAM real usada por el proceso
long getRamMB() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    return pmc.WorkingSetSize / (1024 * 1024); //Convertir de bytes a MB
#else
    std::ifstream f("/proc/self/status");
    std::string linea;
    while (std::getline(f, linea)) {
        if (linea.find("VmRSS:") != std::string::npos) {
            long kb;
            sscanf(linea.c_str(), "VmRSS: %ld", &kb);
            return kb / 1024;
        }
    }
    return -1;
#endif
}

int main() {
    std::vector<void*> bloques; //Guarda los punteros 
    size_t tamano = 1000* 1024 * 1024; //Cantidad de mb por bloque

    for (int i = 0; i < 10000; i++) {
        auto inicio = std::chrono::high_resolution_clock::now(); //Inicio del contador de latencia (va desde que se pide el espacio hasta que se asgina fisicamente)
        void* bloque = malloc(tamano); //Direccion de memoria reservada y espacio reservada 
        memset(bloque, 0xAB, tamano); //Toca el espacio de memoria asignado y forza a que el sistema la mapee fisicamente
        auto fin = std::chrono::high_resolution_clock::now(); //Find el contador de latencia 

        if (!bloque) {
            std::cout << "malloc fallo en iteración " << i << std::endl;
            break;
        }
        bloques.push_back(bloque);

        auto latencia = std::chrono::duration_cast
                        <std::chrono::microseconds>(fin - inicio).count(); //Calcular la letencia

        //RAM real del proceso
        std::cout << "Iter " << i
                  << " | RAM real: "  << getRamMB()     << " MB"
                  << " | Latencia: "  << latencia       << " µs"
                  << std::endl;
    }
    //No se libera memoria
    return 0;
}