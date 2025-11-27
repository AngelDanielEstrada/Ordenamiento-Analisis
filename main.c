#include "util.h"

void menu_principal();
void menu_pruebas_individuales();
void probar_estabilidad();

int main() {
    srand(time(NULL));
    menu_principal();
    return 0;
}

void menu_principal() {
    int opcion;
    
    do {
        printf("\n=== COMPARADOR DE METODOS DE ORDENAMIENTO ===\n");
        printf("1. Pruebas de rendimiento\n");
        printf("2. Pruebas de estabilidad\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                menu_pruebas_individuales();
                break;
            case 2:
                probar_estabilidad();
                break;
            case 3:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while(opcion != 3);
}

void menu_pruebas_individuales() {
    int tamaño, min, max;
    
    printf("\n=== PRUEBAS DE RENDIMIENTO ===\n");
    
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

void probar_estabilidad() {
    printf("\n=== PRUEBAS DE ESTABILIDAD ===\n");
    probar_estabilidad_todos();
    
    printf("\nPresione Enter para continuar...");
    getchar();
    getchar();
}
