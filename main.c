#include "util.h"

int main() {
    srand(time(NULL)); // Inicializar semilla para números aleatorios
    
    int tamaño, min, max;
    
    printf("\n=== COMPARADOR DE MÉTODOS DE ORDENAMIENTO ===\n\n");
    
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
    
    Resultado resultados[10];
    ejecutar_pruebas(tamaño, min, max, resultados);
    imprimir_resultados(resultados, 10);
    
    printf("\nPresione Enter para salir...");
    getchar(); // Limpiar el buffer
    getchar(); // Esperar entrada del usuario
    
    return 0;
}