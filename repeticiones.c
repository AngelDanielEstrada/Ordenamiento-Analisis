#include "repeticiones.h"
#include <time.h>

void ejecutar_prueba_con_repeticiones(void (*algoritmo)(int*, int), 
                                     const char* nombre_algoritmo,
                                     int* arreglo, 
                                     int tamaño,
                                     int num_repeticiones,
                                     ResultadoCompleto* resultado) {
    
    double tiempo_total = 0;
    double comparaciones_total = 0;
    double swaps_total = 0;
    
    strcpy(resultado->algoritmo, nombre_algoritmo);
    resultado->tamaño = tamaño;
    resultado->repeticion = num_repeticiones;
    
    for (int i = 0; i < num_repeticiones; i++) {
        // Crear copia del arreglo para cada repetición
        int* copia = (int*)malloc(tamaño * sizeof(int));
        for (int j = 0; j < tamaño; j++) {
            copia[j] = arreglo[j];
        }
        
        // Resetear contadores
        resetear_contadores(&contadores_global);
        
        // Medir tiempo
        clock_t inicio = clock();
        algoritmo(copia, tamaño);
        clock_t fin = clock();
        
        double tiempo_ms = ((double)(fin - inicio) * 1000.0) / CLOCKS_PER_SEC;
        
        tiempo_total += tiempo_ms;
        comparaciones_total += contadores_global.comparaciones;
        swaps_total += contadores_global.swaps;
        
        free(copia);
    }
    
    // Calcular promedios
    resultado->tiempo_promedio = tiempo_total / num_repeticiones;
    resultado->comparaciones_promedio = comparaciones_total / num_repeticiones;
    resultado->swaps_promedio = swaps_total / num_repeticiones;
    
    // Determinar estabilidad (basado en el algoritmo)
    if (strcmp(nombre_algoritmo, "Selection Sort") == 0) {
        strcpy(resultado->estable, "NO");
    } else {
        strcpy(resultado->estable, "SI");
    }
}

void generar_csv_completo(const char* filename) {
    FILE* archivo = fopen(filename, "w");
    if (!archivo) return;
    
    fprintf(archivo, "algoritmo,tamaño,distribucion,repeticion,tiempo_ms,comparaciones,swaps,estable\n");
    fclose(archivo);
}

void agregar_resultado_csv(const char* filename, const ResultadoCompleto* resultado, const char* distribucion) {
    FILE* archivo = fopen(filename, "a");
    if (!archivo) return;
    
    fprintf(archivo, "%s,%d,%s,%d,%.3f,%.0f,%.0f,%s\n",
            resultado->algoritmo,
            resultado->tamaño,
            distribucion,
            resultado->repeticion,
            resultado->tiempo_promedio,
            resultado->comparaciones_promedio,
            resultado->swaps_promedio,
            resultado->estable);
    
    fclose(archivo);
}
