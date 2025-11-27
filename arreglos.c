#include "arreglos.h"

// Generar arreglo con números aleatorios uniformes
int* generar_arreglo_aleatorio(int tamaño, int min, int max) {
    int *arr = (int *)malloc(tamaño * sizeof(int));
    if (!arr) {
        perror("Error de memoria");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < tamaño; i++) {
        arr[i] = rand() % (max - min + 1) + min;
    }
    return arr;
}

// Generar arreglo ya ordenado
int* generar_arreglo_ordenado(int tamaño) {
    int *arr = (int *)malloc(tamaño * sizeof(int));
    if (!arr) {
        perror("Error de memoria");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < tamaño; i++) {
        arr[i] = i;
    }
    return arr;
}

// Generar arreglo ordenado en reverso
int* generar_arreglo_reverso(int tamaño) {
    int *arr = (int *)malloc(tamaño * sizeof(int));
    if (!arr) {
        perror("Error de memoria");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < tamaño; i++) {
        arr[i] = tamaño - i - 1;
    }
    return arr;
}

// Generar arreglo casi ordenado (90% ordenado, 10% desordenado)
int* generar_arreglo_casi_ordenado(int tamaño) {
    int *arr = (int *)malloc(tamaño * sizeof(int));
    if (!arr) {
        perror("Error de memoria");
        exit(EXIT_FAILURE);
    }
    
    // Primero generar arreglo ordenado
    for (int i = 0; i < tamaño; i++) {
        arr[i] = i;
    }
    
    // Intercambiar algunos elementos (10% del arreglo)
    int num_intercambios = tamaño / 10;
    for (int i = 0; i < num_intercambios; i++) {
        int idx1 = rand() % tamaño;
        int idx2 = rand() % tamaño;
        int temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }
    
    return arr;
}

// Generar arreglo con muchos valores duplicados
int* generar_arreglo_con_duplicados(int tamaño, int min, int max) {
    int *arr = (int *)malloc(tamaño * sizeof(int));
    if (!arr) {
        perror("Error de memoria");
        exit(EXIT_FAILURE);
    }
    
    // Usar solo 5 valores posibles para forzar duplicados
    int valores_posibles = 5;
    if ((max - min + 1) < valores_posibles) {
        valores_posibles = max - min + 1;
    }
    
    for (int i = 0; i < tamaño; i++) {
        arr[i] = min + (rand() % valores_posibles);
    }
    
    return arr;
}

// Imprimir arreglo (útil para debugging)
void imprimir_arreglo(const int* arreglo, int tamaño) {
    printf("[");
    for (int i = 0; i < (tamaño < 10 ? tamaño : 10); i++) {
        printf("%d", arreglo[i]);
        if (i < tamaño - 1 && i < 9) printf(", ");
    }
    if (tamaño > 10) printf(", ...");
    printf("]\n");
}