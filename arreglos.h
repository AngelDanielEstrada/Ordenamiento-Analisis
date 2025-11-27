#ifndef ARREGLOS_H
#define ARREGLOS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Funciones para generación de arreglos de prueba
int* generar_arreglo_aleatorio(int tamaño, int min, int max);
int* generar_arreglo_ordenado(int tamaño);
int* generar_arreglo_reverso(int tamaño);
int* generar_arreglo_casi_ordenado(int tamaño);
int* generar_arreglo_con_duplicados(int tamaño, int min, int max);

// Función para crear copia de arreglo
int* copiar_arreglo(const int* original, int tamaño);

// Función para imprimir arreglo (para debugging)
void imprimir_arreglo(const int* arreglo, int tamaño);

#endif
