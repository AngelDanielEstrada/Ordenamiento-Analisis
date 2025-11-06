#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char nombre[20];
    double tiempo;
} Resultado;

// Funciones de utilidad
int* generar_arreglo(int tamaño, int min, int max);
int* copiar_arreglo(const int* original, int tamaño);
void imprimir_arreglo(const int* arreglo, int tamaño);

// Algoritmos de ordenamiento
void burbuja(int* arr, int n);
void insercion(int* arr, int n);
void seleccion(int* arr, int n);
void merge_sort(int* arr, int n);
void heap_sort(int* arr, int n);
void quick_sort(int* arr, int n);
void bucket_sort(int* arr, int n);
void counting_sort(int* arr, int n);
void radix_sort(int* arr, int n);
void bogus_sort(int* arr, int n);

// Funciones para pruebas
double medir_tiempo(int* arr, int n, void (*func_ordenamiento)(int*, int));
void ejecutar_pruebas(int tamaño, int min, int max, Resultado* resultados);
void imprimir_resultados(const Resultado* resultados, int num_metodos);
void analizar_resultados(const Resultado* resultados, int num_metodos);

#endif