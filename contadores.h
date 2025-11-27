#ifndef CONTADORES_H
#define CONTADORES_H

#include <stdio.h>

// Estructura para contar comparaciones y swaps
typedef struct {
    long comparaciones;
    long swaps;
} Contadores;

// Funciones para manejar contadores
void resetear_contadores(Contadores* cnt);
void incrementar_comparacion(Contadores* cnt);
void incrementar_swap(Contadores* cnt);
void imprimir_contadores(const Contadores* cnt, const char* nombre_algoritmo);

// Contadores globales (para uso en algoritmos)
extern Contadores contadores_global;

#endif
