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

// Algoritmo de ordenamiento Burbuja
void burbuja(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Algoritmo de ordenamiento por Inserción
void insercion(int *arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Algoritmo de ordenamiento por Selección
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

// Funciones auxiliares para Merge Sort
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

// Funciones auxiliares para Heap Sort
void heapify(int *arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heap_sort(int *arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// Funciones auxiliares para Quick Sort
int partition(int *arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quick_sort_helper(int *arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quick_sort_helper(arr, low, pi - 1);
        quick_sort_helper(arr, pi + 1, high);
    }
}

void quick_sort(int *arr, int n)
{
    quick_sort_helper(arr, 0, n - 1);
}

// Implementación de Bucket Sort mejorada
void bucket_sort(int *arr, int n)
{
    if (n <= 0)
        return;

    // Encontrar valores máximo y mínimo
    int max_val = arr[0], min_val = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max_val)
            max_val = arr[i];
        if (arr[i] < min_val)
            min_val = arr[i];
    }

    // Caso especial: todos los valores son iguales
    if (max_val == min_val)
        return;

    // Crear buckets
    int bucket_count = 10;
    int **buckets = (int **)malloc(bucket_count * sizeof(int *));
    int *sizes = (int *)calloc(bucket_count, sizeof(int));

    // Inicializar buckets
    for (int i = 0; i < bucket_count; i++)
    {
        buckets[i] = (int *)malloc(n * sizeof(int));
    }

    // Distribuir elementos en los buckets
    float range = (float)(max_val - min_val + 1) / bucket_count;
    for (int i = 0; i < n; i++)
    {
        int bucket_idx = (int)((arr[i] - min_val) / range);
        if (bucket_idx >= bucket_count)
            bucket_idx = bucket_count - 1; // Prevención de overflow
        buckets[bucket_idx][sizes[bucket_idx]++] = arr[i];
    }

    // Ordenar cada bucket e insertar de vuelta al arreglo
    int index = 0;
    for (int i = 0; i < bucket_count; i++)
    {
        if (sizes[i] > 0)
        {
            // Usamos insertion sort para cada bucket
            insercion(buckets[i], sizes[i]);

            // Copiar elementos ordenados al arreglo original
            for (int j = 0; j < sizes[i]; j++)
            {
                arr[index++] = buckets[i][j];
            }
        }
        free(buckets[i]);
    }

    free(buckets);
    free(sizes);
}

// Implementación de Counting Sort
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

// Implementación de Radix Sort
void counting_sort_radix(int *arr, int n, int exp)
{
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};

    // Contar ocurrencias de cada dígito
    for (int i = 0; i < n; i++)
    {
        count[(arr[i] / exp) % 10]++;
    }

    // Acumular contadores
    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    // Construir el arreglo de salida
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copiar al arreglo original
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }

    free(output);
}

void radix_sort(int *arr, int n)
{
    if (n <= 0)
        return;

    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }

    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        counting_sort_radix(arr, n, exp);
    }
}

// Función para medir el tiempo de ejecución
double medir_tiempo(int *arr, int n, void (*func_ordenamiento)(int *, int))
{
    clock_t inicio = clock();
    func_ordenamiento(arr, n);
    clock_t fin = clock();
    return ((double)(fin - inicio)) / CLOCKS_PER_SEC * 1000; // Convertir a milisegundos
}

// Función para ejecutar todas las pruebas
void ejecutar_pruebas(int tamaño, int min, int max, Resultado *resultados)
{
    printf("\nGenerando arreglo de prueba\n");
    int *original = generar_arreglo(tamaño, min, max);

    void (*metodos[])(int *, int) = {
        burbuja, insercion, seleccion, merge_sort,
        heap_sort, quick_sort, bucket_sort,
        counting_sort, radix_sort};

    const char *nombres[] = {
        "Burbuja", "Insercion", "Seleccion", "Merge Sort",
        "Heap Sort", "Quick Sort", "Bucket Sort",
        "Counting Sort", "Radix Sort"};

    printf("Ejecutando pruebas de ordenamiento\n");
    for (int i = 0; i < 9; i++)
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

// Función para imprimir los resultados
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