#include "util.h"
#include <limits.h>
#include <math.h>

// Función para generar un arreglo de números aleatorios
int *generar_arreglo(int tamaño, int min, int max)
{
    int *arr = (int *)malloc(tamaño * sizeof(int));
    if (!arr)
    {
        perror("Error de memoria");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < tamaño; i++)
    {
        arr[i] = rand() % (max - min + 1) + min;
    }
    return arr;
}

// Función para crear una copia de un arreglo
int *copiar_arreglo(const int *original, int tamaño)
{
    int *copia = (int *)malloc(tamaño * sizeof(int));
    if (!copia)
    {
        perror("Error de memoria");
        exit(EXIT_FAILURE);
    }
    memcpy(copia, original, tamaño * sizeof(int));
    return copia;
}

// Algoritmo de ordenamiento por Selección (versión base)
void seleccion(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// Funciones auxiliares para Merge Sort (versión base)
void merge(int *arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort_helper(int *arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        merge_sort_helper(arr, l, m);
        merge_sort_helper(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge_sort(int *arr, int n)
{
    merge_sort_helper(arr, 0, n - 1);
}

// Implementación de Counting Sort (versión base)
void counting_sort(int *arr, int n)
{
    if (n <= 0)
        return;

    int max = arr[0], min = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }

    int range = max - min + 1;
    int *count = (int *)calloc(range, sizeof(int));
    int *output = (int *)malloc(n * sizeof(int));

    // Contar ocurrencias
    for (int i = 0; i < n; i++)
    {
        count[arr[i] - min]++;
    }

    // Acumular contadores
    for (int i = 1; i < range; i++)
    {
        count[i] += count[i - 1];
    }

    // Construir el arreglo de salida
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    // Copiar al arreglo original
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}

// Implementación básica de Tim Sort
const int RUN = 32;

void insertion_sort_tim(int *arr, int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void tim_sort(int *arr, int n)
{
    // Ordenar subarreglos individuales de tamaño RUN
    for (int i = 0; i < n; i += RUN)
    {
        insertion_sort_tim(arr, i, (i + RUN - 1 < n - 1) ? (i + RUN - 1) : (n - 1));
    }

    // Comenzar a fusionar desde tamaño RUN
    for (int size = RUN; size < n; size = 2 * size)
    {
        for (int left = 0; left < n; left += 2 * size)
        {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ? (left + 2 * size - 1) : (n - 1);

            if (mid < right)
            {
                merge(arr, left, mid, right);
            }
        }
    }
}

// Función para medir el tiempo de ejecución (sin cambios)
double medir_tiempo(int *arr, int n, void (*func_ordenamiento)(int *, int))
{
    clock_t inicio = clock();
    func_ordenamiento(arr, n);
    clock_t fin = clock();
    return ((double)(fin - inicio)) / CLOCKS_PER_SEC * 1000; // Convertir a milisegundos
}

// Función para ejecutar todas las pruebas (modificada para 4 métodos)
void ejecutar_pruebas(int tamaño, int min, int max, Resultado *resultados)
{
    printf("\nGenerando arreglo de prueba\n");
    int *original = generar_arreglo(tamaño, min, max);

    void (*metodos[])(int *, int) = {
        seleccion, merge_sort, counting_sort, tim_sort};

    const char *nombres[] = {
        "Seleccion", "Merge Sort", "Counting Sort", "Tim Sort"};

    printf("Ejecutando pruebas de ordenamiento\n");
    for (int i = 0; i < 4; i++)
    {
        printf("Probando %s\n", nombres[i]);
        int *copia = copiar_arreglo(original, tamaño);
        resultados[i].tiempo = medir_tiempo(copia, tamaño, metodos[i]);
        strcpy(resultados[i].nombre, nombres[i]);
        free(copia);
    }

    free(original);
    printf("Pruebas completadas.\n");
}

// Función para imprimir los resultados (sin cambios)
void imprimir_resultados(const Resultado *resultados, int num_metodos)
{
    printf("\n┌──────────────────────┬──────────────────┐\n");
    printf("│ %-20s │ %-16s │\n", "Método", "Tiempo (ms)");
    printf("├──────────────────────┼──────────────────┤\n");

    for (int i = 0; i < num_metodos; i++)
    {
        printf("│ %-20s │ %-16.2f │\n", resultados[i].nombre, resultados[i].tiempo);
    }
    printf("└──────────────────────┴──────────────────┘\n");

    // Llamar al análisis de resultados
    analizar_resultados(resultados, num_metodos);
}

// Función para analizar resultados (sin cambios)
void analizar_resultados(const Resultado *resultados, int num_metodos)
{
    if (num_metodos <= 0)
        return;

    double suma = 0;
    double mejor = resultados[0].tiempo;
    double peor = resultados[0].tiempo;
    const char *nombre_mejor = resultados[0].nombre;
    const char *nombre_peor = resultados[0].nombre;

    for (int i = 0; i < num_metodos; i++)
    {
        suma += resultados[i].tiempo;

        if (resultados[i].tiempo < mejor)
        {
            mejor = resultados[i].tiempo;
            nombre_mejor = resultados[i].nombre;
        }

        if (resultados[i].tiempo > peor)
        {
            peor = resultados[i].tiempo;
            nombre_peor = resultados[i].nombre;
        }
    }

    double promedio = suma / num_metodos;

    printf("\n┌──────────────────────┬──────────────────┐\n");
    printf("│ %-20s │ %-16s │\n", "Análisis", "Tiempo (ms)");
    printf("├──────────────────────┼──────────────────┤\n");
    printf("│ %-20s │ %-16.2f │\n", "Mejor método", mejor);
    printf("│ %-20s │ %-20s │\n", "  (Nombre)", nombre_mejor);
    printf("├──────────────────────┼──────────────────┤\n");
    printf("│ %-20s │ %-16.2f │\n", "Peor método", peor);
    printf("│ %-20s │ %-20s │\n", "  (Nombre)", nombre_peor);
    printf("├──────────────────────┼──────────────────┤\n");
    printf("│ %-20s │ %-16.2f │\n", "Tiempo promedio", promedio);
    printf("└──────────────────────┴──────────────────┘\n");
}