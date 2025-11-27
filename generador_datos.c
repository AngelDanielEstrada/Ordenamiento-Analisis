#include "generador_datos.h"
#include "arreglos.h"
#include "contadores.h"

// Función auxiliar para medir algoritmo con contadores
double medir_algoritmo_con_contadores(void (*algoritmo)(int*, int), 
                                     int* arreglo, int tamaño,
                                     long* comparaciones, long* swaps) {
    // Crear copia para no modificar el original
    int* copia = copiar_arreglo(arreglo, tamaño);
    
    // Resetear contadores
    resetear_contadores(&contadores_global);
    
    // Medir tiempo
    clock_t inicio = clock();
    algoritmo(copia, tamaño);
    clock_t fin = clock();
    
    // Obtener métricas
    *comparaciones = contadores_global.comparaciones;
    *swaps = contadores_global.swaps;
    
    free(copia);
    return ((double)(fin - inicio) * 1000.0) / CLOCKS_PER_SEC;
}

void generar_csv_graficas() {
    printf("\n=== GENERANDO DATOS PARA GRÁFICAS ===\n");
    
    FILE *archivo = fopen("resultados.csv", "w");
    if (!archivo) {
        printf("Error: No se pudo crear resultados.csv\n");
        return;
    }
    
    // Cabecera compatible con graficas.py
    fprintf(archivo, "algoritmo,tamaño,distribucion,tiempo_ms,comparaciones,swaps,estable\n");
    
    int tamaños[] = {100, 200, 300, 400, 500, 1000, 2500, 5000};
    int num_tamaños = sizeof(tamaños) / sizeof(tamaños[0]);
    
    // Declarar algoritmos
    extern void seleccion(int*, int);
    extern void merge_sort(int*, int);
    extern void counting_sort(int*, int);
    extern void tim_sort(int*, int);
    
    void (*algoritmos[])(int*, int) = {seleccion, merge_sort, counting_sort, tim_sort};
    char* nombres[] = {"Selection", "Merge Sort", "Counting Sort", "Tim Sort"};
    char* estabilidad[] = {"NO", "SI", "SI", "SI"};
    
    printf("Generando datos para %d tamaños...\n", num_tamaños);
    
    for (int i = 0; i < num_tamaños; i++) {
        int tamaño = tamaños[i];
        printf("Procesando tamaño: %d\n", tamaño);
        
        // Generar diferentes distribuciones
        char* distribuciones[] = {"aleatorio", "ordenado", "reverso", "casi_ordenado", "duplicados"};
        
        for (int d = 0; d < 5; d++) {
            int* arreglo;
            
            switch(d) {
                case 0: arreglo = generar_arreglo_aleatorio(tamaño, 0, 1000); break;
                case 1: arreglo = generar_arreglo_ordenado(tamaño); break;
                case 2: arreglo = generar_arreglo_reverso(tamaño); break;
                case 3: arreglo = generar_arreglo_casi_ordenado(tamaño); break;
                case 4: arreglo = generar_arreglo_con_duplicados(tamaño, 0, 100); break;
            }
            
            // Probar cada algoritmo
            for (int a = 0; a < 4; a++) {
                long comparaciones, swaps;
                double tiempo = medir_algoritmo_con_contadores(algoritmos[a], arreglo, tamaño, &comparaciones, &swaps);
                
                fprintf(archivo, "%s,%d,%s,%.3f,%ld,%ld,%s\n",
                        nombres[a], tamaño, distribuciones[d], tiempo, comparaciones, swaps, estabilidad[a]);
            }
            
            free(arreglo);
        }
    }
    
    fclose(archivo);
    printf("✓ Datos guardados en: resultados.csv\n");
    printf("✓ Ejecuta: python3 graficas.py\n");
}

void prueba_rapida_benchmark(int tamaño) {
    printf("\n=== PRUEBA RÁPIDA - Tamaño %d ===\n", tamaño);
    
    int* arreglo = generar_arreglo_aleatorio(tamaño, 0, 1000);
    
    // Declarar algoritmos
    extern void seleccion(int*, int);
    extern void merge_sort(int*, int);
    extern void counting_sort(int*, int);
    extern void tim_sort(int*, int);
    
    void (*algoritmos[])(int*, int) = {seleccion, merge_sort, counting_sort, tim_sort};
    char* nombres[] = {"Selection", "Merge Sort", "Counting Sort", "Tim Sort"};
    
    printf("Algoritmo        | Tiempo(ms) | Comparaciones | Swaps\n");
    printf("-----------------|------------|---------------|-------\n");
    
    for (int i = 0; i < 4; i++) {
        long comparaciones, swaps;
        double tiempo = medir_algoritmo_con_contadores(algoritmos[i], arreglo, tamaño, &comparaciones, &swaps);
        
        printf("%-16s | %9.2f | %13ld | %ld\n", 
               nombres[i], tiempo, comparaciones, swaps);
    }
    
    free(arreglo);
}

void generar_benchmark_completo() {
    printf("\n=== BENCHMARK COMPLETO ===\n");
    printf("Este proceso puede tomar varios minutos...\n");
    
    generar_csv_graficas();
    
    printf("\n=== BENCHMARK COMPLETADO ===\n");
    printf("Se generaron datos para:\n");
    printf("- 5 tamaños diferentes\n");
    printf("- 5 tipos de distribuciones\n");
    printf("- 4 algoritmos de ordenamiento\n");
    printf("- Métricas completas (tiempo, comparaciones, swaps)\n");
    printf("\nArchivo: resultados.csv\n");
}
