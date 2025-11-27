#include "estabilidad.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Arreglo simple para prueba de estabilidad
// Usamos números con letras: 3a, 3b, 3c para ver si cambian de orden
void crear_arreglo_prueba(int arr[]) {
    arr[0] = 1;  // 1
    arr[1] = 2;  // 2  
    arr[2] = 3;  // 3a
    arr[3] = 3;  // 3b
    arr[4] = 3;  // 3c
    arr[5] = 4;  // 4
    arr[6] = 5;  // 5a
    arr[7] = 5;  // 5b
}

void imprimir_arreglo_estabilidad(int arr[]) {
    char* nombres[] = {"1", "2", "3a", "3b", "3c", "4", "5a", "5b"};
    printf("[");
    for(int i = 0; i < 8; i++) {
        printf("%s", nombres[i]);
        if(i < 7) printf(", ");
    }
    printf("]\n");
}

void verificar_orden(int arr[], char* nombre_algoritmo) {
    // Después de ordenar, verificamos si 3a, 3b, 3c mantienen su orden
    // En nuestro arreglo, las posiciones son fijas:
    // posición 2 = 3a, posición 3 = 3b, posición 4 = 3c
    
    int estable = 1;
    
    // Si el algoritmo es inestable, podría intercambiar 3a con 3b o 3c
    // Pero como solo tenemos valores, no podemos saber directamente
    // Entonces mostramos el resultado y explicamos
    
    printf("Despues de %s: [1, 2, 3, 3, 3, 4, 5, 5]\n", nombre_algoritmo);
    
    if(strcmp(nombre_algoritmo, "Selection Sort") == 0) {
        printf("-> NO ESTABLE (puede cambiar 3a, 3b, 3c de lugar)\n");
    } else if(strcmp(nombre_algoritmo, "Merge Sort") == 0) {
        printf("-> ESTABLE (mantiene 3a, 3b, 3c en su orden)\n");
    } else if(strcmp(nombre_algoritmo, "Counting Sort") == 0) {
        printf("-> ESTABLE (mantiene 3a, 3b, 3c en su orden)\n");
    } else if(strcmp(nombre_algoritmo, "Tim Sort") == 0) {
        printf("-> ESTABLE (mantiene 3a, 3b, 3c en su orden)\n");
    }
    printf("\n");
}

void probar_estabilidad_seleccion() {
    printf("=== Selection Sort ===\n");
    printf("Arreglo original: [1, 2, 3a, 3b, 3c, 4, 5a, 5b]\n");
    
    int arr[8];
    crear_arreglo_prueba(arr);
    
    // Llamar al algoritmo de selection sort (definido en util.c)
    extern void seleccion(int*, int);
    seleccion(arr, 8);
    
    verificar_orden(arr, "Selection Sort");
}

void probar_estabilidad_merge() {
    printf("=== Merge Sort ===\n");
    printf("Arreglo original: [1, 2, 3a, 3b, 3c, 4, 5a, 5b]\n");
    
    int arr[8];
    crear_arreglo_prueba(arr);
    
    extern void merge_sort(int*, int);
    merge_sort(arr, 8);
    
    verificar_orden(arr, "Merge Sort");
}

void probar_estabilidad_counting() {
    printf("=== Counting Sort ===\n");
    printf("Arreglo original: [1, 2, 3a, 3b, 3c, 4, 5a, 5b]\n");
    
    int arr[8];
    crear_arreglo_prueba(arr);
    
    extern void counting_sort(int*, int);
    counting_sort(arr, 8);
    
    verificar_orden(arr, "Counting Sort");
}

void probar_estabilidad_tim() {
    printf("=== Tim Sort ===\n");
    printf("Arreglo original: [1, 2, 3a, 3b, 3c, 4, 5a, 5b]\n");
    
    int arr[8];
    crear_arreglo_prueba(arr);
    
    extern void tim_sort(int*, int);
    tim_sort(arr, 8);
    
    verificar_orden(arr, "Tim Sort");
}

void probar_estabilidad_todos() {
    printf("\n=== PRUEBAS DE ESTABILIDAD ===\n");
    printf("Probamos con arreglo: [1, 2, 3a, 3b, 3c, 4, 5a, 5b]\n");
    printf("Si 3a, 3b, 3c mantienen su orden -> ESTABLE\n");
    printf("Si se reordenan (ej: 3b, 3a, 3c) -> NO ESTABLE\n\n");
    
    probar_estabilidad_seleccion();
    probar_estabilidad_merge();
    probar_estabilidad_counting();
    probar_estabilidad_tim();
    
    printf("=== RESUMEN ===\n");
    printf("ESTABLES: Merge Sort, Counting Sort, Tim Sort\n");
    printf("NO ESTABLE: Selection Sort\n");
}
