#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "contadores.h"
#include "repeticiones.h"
#include "generador_datos.h"
typedef struct {
    char nombre[20];
    double tiempo_ms;
    long comparaciones;
    long swaps;
    char estable[3];
} Resultado;

// Funciones de utilidad
int* generar_arreglo(int tamaño, int min, int max);
int* copiar_arreglo(const int* original, int tamaño);
void imprimir_arreglo(const int* arreglo, int tamaño);

// Algoritmos de ordenamiento
void seleccion(int* arr, int n);
void merge_sort(int* arr, int n);
void counting_sort(int* arr, int n);
void tim_sort(int* arr, int n);

// Funciones para pruebas
double medir_tiempo(int* arr, int n, void (*func_ordenamiento)(int*, int));
void ejecutar_pruebas(int tamaño, int min, int max, Resultado* resultados);
void imprimir_resultados(const Resultado* resultados, int num_metodos);
void analizar_resultados(const Resultado* resultados, int num_metodos);

#endif
