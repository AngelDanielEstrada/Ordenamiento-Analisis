#ifndef GENERADOR_DATOS_H
#define GENERADOR_DATOS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Función para generar datos de benchmark completos
void generar_benchmark_completo();

// Función para generar CSV compatible con graficas.py
void generar_csv_graficas();

// Función para prueba rápida con un tamaño específico
void prueba_rapida_benchmark(int tamaño);

#endif
