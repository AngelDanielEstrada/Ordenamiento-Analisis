#!/usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt

# Leer datos
df = pd.read_csv('resultados.csv')

# Agrupar por algoritmo y tamaño (promedio)
grouped = df.groupby(['algoritmo', 'tamaño']).agg({
    'tiempo_ms': 'mean',
    'comparaciones': 'mean', 
    'swaps': 'mean'
}).reset_index()

algoritmos = df['algoritmo'].unique()

# 1. GRÁFICA DE TIEMPOS (Lineal)
plt.figure(figsize=(10, 6))
for algoritmo in algoritmos:
    datos = grouped[grouped['algoritmo'] == algoritmo]
    plt.plot(datos['tamaño'], datos['tiempo_ms'], marker='o', label=algoritmo)

plt.xlabel('Tamaño del arreglo')
plt.ylabel('Tiempo (ms)')
plt.title('Tiempos de Ejecución - Lineal')
plt.legend()
plt.grid(True)
plt.savefig('tiempos_lineal.png')
plt.close()

# 2. GRÁFICA DE TIEMPOS (Logarítmica)
plt.figure(figsize=(10, 6))
for algoritmo in algoritmos:
    datos = grouped[grouped['algoritmo'] == algoritmo]
    plt.plot(datos['tamaño'], datos['tiempo_ms'], marker='o', label=algoritmo)

plt.xlabel('Tamaño del arreglo')
plt.ylabel('Tiempo (ms)')
plt.title('Tiempos de Ejecución - Logarítmica')
plt.yscale('log')
plt.legend()
plt.grid(True)
plt.savefig('tiempos_log.png')
plt.close()

# 3. GRÁFICA DE COMPARACIONES
plt.figure(figsize=(10, 6))
for algoritmo in algoritmos:
    datos = grouped[grouped['algoritmo'] == algoritmo]
    plt.plot(datos['tamaño'], datos['comparaciones'], marker='s', label=algoritmo)

plt.xlabel('Tamaño del arreglo')
plt.ylabel('Comparaciones')
plt.title('Comparaciones por Algoritmo')
plt.legend()
plt.grid(True)
plt.savefig('comparaciones.png')
plt.close()

print("Gráficas generadas: tiempos_lineal.png, tiempos_log.png, comparaciones.png")
