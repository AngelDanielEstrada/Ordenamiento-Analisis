#include "contadores.h"

// Contador global accesible desde los algoritmos
Contadores contadores_global;

void resetear_contadores(Contadores* cnt) {
    cnt->comparaciones = 0;
    cnt->swaps = 0;
}

void incrementar_comparacion(Contadores* cnt) {
    cnt->comparaciones++;
}

void incrementar_swap(Contadores* cnt) {
    cnt->swaps++;
}

void imprimir_contadores(const Contadores* cnt, const char* nombre_algoritmo) {
    printf("%s - Comparaciones: %ld, Swaps: %ld\n", 
           nombre_algoritmo, cnt->comparaciones, cnt->swaps);
}
