#include "util.h"
#include "arreglos.h"

void menu_principal();
void menu_pruebas_individuales();
void probar_estabilidad();
void modo_distribucion_especifica();
void modo_pruebas_completas();

int main() {
    srand(time(NULL));
    menu_principal();
    return 0;
}

void menu_principal() {
    int opcion;
    
    do {
        printf("\n=== COMPARADOR DE METODOS DE ORDENAMIENTO ===\n");
        printf("1. Pruebas de rendimiento individuales\n");
        printf("2. Pruebas con distribuciones específicas\n");
        printf("3. Pruebas completas automáticas\n");
        printf("4. Pruebas de estabilidad\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                menu_pruebas_individuales();
                break;
            case 2:
                modo_distribucion_especifica();
                break;
            case 3:
                modo_pruebas_completas();
                break;
            case 4:
                probar_estabilidad();
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while(opcion != 5);
}

void menu_pruebas_individuales() {
    int tamaño, min, max;
    
    printf("\n=== PRUEBAS DE RENDIMIENTO INDIVIDUALES ===\n");
    
    // Validación del tamaño del arreglo
    do {
        printf("Tamaño del arreglo (1-100000): ");
        scanf("%d", &tamaño);
        if (tamaño <= 0) printf("El tamaño debe ser positivo.\n");
        if (tamaño > 100000) printf("El tamaño máximo es 100000.\n");
    } while (tamaño <= 0 || tamaño > 100000);
    
    // Validación del rango de valores
    do {
        printf("Valor mínimo: ");
        scanf("%d", &min);
        printf("Valor máximo: ");
        scanf("%d", &max);
        
        if (min > max) {
            printf("El valor mínimo no puede ser mayor que el máximo.\n");
        }
    } while (min > max);
    
    Resultado resultados[4];
    ejecutar_pruebas(tamaño, min, max, resultados);
    imprimir_resultados(resultados, 4);
    
    printf("\nPresione Enter para continuar...");
    getchar();
    getchar();
}

// Distribuciones específicas
void modo_distribucion_especifica() {
    int tamaño, min, max;
    char distribucion[20];
    
    printf("\n=== PRUEBAS CON DISTRIBUCIONES ESPECÍFICAS ===\n");
    
    // Elegir tamaño
    do {
        printf("Tamaño del arreglo (1-100000): ");
        scanf("%d", &tamaño);
        if (tamaño <= 0) printf("El tamaño debe ser positivo.\n");
        if (tamaño > 100000) printf("El tamaño máximo es 100000.\n");
    } while (tamaño <= 0 || tamaño > 100000);
    
    // Elegir distribución
    printf("\nDistribuciones disponibles:\n");
    printf("1. aleatorio   - Valores aleatorios uniformemente distribuidos\n");
    printf("2. ordenado    - Arreglo ya ordenado\n");
    printf("3. reverso     - Arreglo ordenado en reverso\n");
    printf("4. casi        - Arreglo casi ordenado (90%% ordenado)\n");
    printf("5. duplicados  - Muchos valores duplicados\n");
    
    int opcion_dist;
    do {
        printf("Seleccione distribución (1-5): ");
        scanf("%d", &opcion_dist);
    } while (opcion_dist < 1 || opcion_dist > 5);
    
    // Mapear opción a nombre de distribución
    const char* distribuciones[] = {"aleatorio", "ordenado", "reverso", "casi", "duplicados"};
    strcpy(distribucion, distribuciones[opcion_dist - 1]);
    
    // Para distribuciones que necesitan min y max
    if (strcmp(distribucion, "aleatorio") == 0 || strcmp(distribucion, "duplicados") == 0) {
        do {
            printf("Valor mínimo: ");
            scanf("%d", &min);
            printf("Valor máximo: ");
            scanf("%d", &max);
            
            if (min > max) {
                printf("El valor mínimo no puede ser mayor que el máximo.\n");
            }
        } while (min > max);
    } else {
        min = 0;
        max = tamaño - 1;
    }
    
    printf("\nGenerando arreglo %s de tamaño %d...\n", distribucion, tamaño);
    
    // Generar arreglo según la distribución seleccionada
    int* original;
    if (strcmp(distribucion, "aleatorio") == 0) {
        original = generar_arreglo_aleatorio(tamaño, min, max);
    } else if (strcmp(distribucion, "ordenado") == 0) {
        original = generar_arreglo_ordenado(tamaño);
    } else if (strcmp(distribucion, "reverso") == 0) {
        original = generar_arreglo_reverso(tamaño);
    } else if (strcmp(distribucion, "casi") == 0) {
        original = generar_arreglo_casi_ordenado(tamaño);
    } else if (strcmp(distribucion, "duplicados") == 0) {
        original = generar_arreglo_con_duplicados(tamaño, min, max);
    } else {
        original = generar_arreglo_aleatorio(tamaño, min, max);
    }
    
    // Mostrar primeros 10 elementos del arreglo generado
    printf("Arreglo generado: ");
    imprimir_arreglo(original, tamaño);
    
    // Ejecutar pruebas
    Resultado resultados[4];
    void (*metodos[])(int *, int) = {seleccion, merge_sort, counting_sort, tim_sort};
    const char *nombres[] = {"Seleccion", "Merge Sort", "Counting Sort", "Tim Sort"};
    
    printf("\nEjecutando pruebas de ordenamiento...\n");
    for (int i = 0; i < 4; i++) {
        printf("Probando %s... ", nombres[i]);
        int *copia = copiar_arreglo(original, tamaño);
        resultados[i].tiempo = medir_tiempo(copia, tamaño, metodos[i]);
        strcpy(resultados[i].nombre, nombres[i]);
        free(copia);
        printf("✓ (%.2f ms)\n", resultados[i].tiempo);
    }
    
    free(original);
    imprimir_resultados(resultados, 4);
    
    printf("\nPresione Enter para continuar...");
    getchar();
    getchar();
}

//  Pruebas completas
void modo_pruebas_completas() {
    printf("\n=== PRUEBAS COMPLETAS AUTOMÁTICAS ===\n");
    
    int tamanos[] = {100, 200, 300, 400, 500, 1000, 2500, 5000, 7500};
    int num_tamanos = 9;
    const char *distribuciones[] = {"aleatorio", "ordenado", "reverso", "casi", "duplicados"};
    int num_distribuciones = 5;
    int repeticiones = 3;
    int min = 0, max = 1000;
    
    printf("Configuración de pruebas:\n");
    printf("- Tamaños: ");
    for (int i = 0; i < num_tamanos; i++) {
        printf("%d%s", tamanos[i], (i < num_tamanos - 1) ? ", " : "");
    }
    printf("\n- Distribuciones: ");
    for (int i = 0; i < num_distribuciones; i++) {
        printf("%s%s", distribuciones[i], (i < num_distribuciones - 1) ? ", " : "");
    }
    printf("\n- Repeticiones: %d\n", repeticiones);
    printf("- Rango de valores: %d - %d\n", min, max);
    
    int total_pruebas = num_tamanos * num_distribuciones * 4 * repeticiones;
    printf("- Total de pruebas: %d\n", total_pruebas);
    printf("\nEsto puede tomar varios minutos...\n");
    printf("¿Continuar? (s/n): ");
    
    char respuesta;
    scanf(" %c", &respuesta);
    
    if (respuesta != 's' && respuesta != 'S') {
        printf("Pruebas canceladas.\n");
        return;
    }
    
    // Ejecutar pruebas completas
    printf("\nEjecutando pruebas completas...\n");
    
    FILE* archivo = fopen("resultados_completos.csv", "w");
    if (!archivo) {
        printf("Error al crear archivo de resultados.\n");
        return;
    }
    
    // Escribir cabecera del CSV
    fprintf(archivo, "algoritmo,distribucion,tamaño,repeticion,tiempo_ms\n");
    
    void (*metodos[])(int *, int) = {seleccion, merge_sort, counting_sort, tim_sort};
    const char *nombres[] = {"Seleccion", "MergeSort", "CountingSort", "TimSort"};
    
    int prueba_actual = 0;
    
    for (int t = 0; t < num_tamanos; t++) {
        int tamaño = tamanos[t];
        
        for (int d = 0; d < num_distribuciones; d++) {
            const char* distribucion = distribuciones[d];
            
            for (int a = 0; a < 4; a++) {
                const char* algoritmo = nombres[a];
                
                for (int r = 0; r < repeticiones; r++) {
                    // Generar arreglo según la distribución
                    int* original;
                    if (strcmp(distribucion, "aleatorio") == 0) {
                        original = generar_arreglo_aleatorio(tamaño, min, max);
                    } else if (strcmp(distribucion, "ordenado") == 0) {
                        original = generar_arreglo_ordenado(tamaño);
                    } else if (strcmp(distribucion, "reverso") == 0) {
                        original = generar_arreglo_reverso(tamaño);
                    } else if (strcmp(distribucion, "casi") == 0) {
                        original = generar_arreglo_casi_ordenado(tamaño);
                    } else if (strcmp(distribucion, "duplicados") == 0) {
                        original = generar_arreglo_con_duplicados(tamaño, min, max);
                    } else {
                        original = generar_arreglo_aleatorio(tamaño, min, max);
                    }
                    
                    int* copia = copiar_arreglo(original, tamaño);
                    
                    // Medir tiempo
                    double tiempo = medir_tiempo(copia, tamaño, metodos[a]);
                    
                    // Guardar en CSV
                    fprintf(archivo, "%s,%s,%d,%d,%.6f\n", 
                           algoritmo, distribucion, tamaño, r + 1, tiempo);
                    
                    prueba_actual++;
                    
                    // Mostrar progreso cada 10 pruebas
                    if (prueba_actual % 10 == 0) {
                        printf("Completadas: %d/%d pruebas\n", prueba_actual, total_pruebas);
                    }
                    
                    free(original);
                    free(copia);
                }
            }
        }
    }
    
    fclose(archivo);
    printf("\n¡Pruebas completadas! Resultados guardados en 'resultados_completos.csv'\n");
    printf("Total de pruebas ejecutadas: %d\n", prueba_actual);
    
    printf("\nPresione Enter para continuar...");
    getchar();
    getchar();
}


void probar_estabilidad() {
    printf("\n=== PRUEBAS DE ESTABILIDAD ===\n");
    printf("Funcionalidad de estabilidad en desarrollo...\n");
    
    printf("\nPresione Enter para continuar...");
    getchar();
    getchar();
}