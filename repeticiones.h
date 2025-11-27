#ifndef REPETICIONES_H
#define REPETICIONES_H

#include "contadores.h"

// Estructura para resultados con múltiples repeticiones
typedef struct {
    char algoritmo[20];
    int tamaño;
    char distribucion[20];
    int repeticion;
    double tiempo_promedio;
    double comparaciones_promedio;
    double swaps_promedio;
    char estable[3];
} ResultadoCompleto;

// Funciones para manejar repeticiones
void ejecutar_prueba_con_repeticiones(void (*algoritmo)(int*, int), 
                                     const char* nombre_algoritmo,
                                     int* arreglo, 
                                     int tamaño,
                                     int num_repeticiones,
                                     ResultadoCompleto* resultado);

void generar_csv_completo(const char* filename);

#endif
