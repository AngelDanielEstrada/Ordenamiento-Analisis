#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "arreglos.h"
#include "estabilidad.h"
typedef struct {
    char nombre[20];
    double tiempo;
} Resultado;



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
