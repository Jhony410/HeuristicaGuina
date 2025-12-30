# Análisis de la Heurística de Costo, Balance e Importancia (HCBE)

## 👤 Autores
- **Mildward Erik Condori Nina**
- **Diane Coraima Cabana Otazu**
- **Franco Rojas Luque**
- **Jhon Aguilar Aguilar Anccori**


Este documento presenta un análisis detallado de la heurística implementada para resolver problemas de transporte, evaluando su desempeño a través de tres casos de prueba representativos.

## 1. Fundamentos de la Heurística HCBE

La heurística selecciona la celda de asignación basándose en un índice de prioridad calculado como:

$$HCBE = Costo_{ij} \times Equilibrio \times PrioridadDemanda$$

Donde:
- **Equilibrio**: $1.0 + \frac{|Oferta_i - Demanda_j|}{\max(Oferta_i, Demanda_j)}$. Favorece asignaciones donde la oferta y demanda están balanceadas.
- **Prioridad de Demanda**: $\frac{Demanda_j}{\max(Demanda)}$. Prioriza destinos con mayor urgencia de suministro.

## 2. ¿Por qué es importante esta Heurística?

A diferencia de los métodos clásicos como la **Esquina Noroeste** (que ignora costos) o el **Costo Mínimo** (que ignora el balance del sistema), la heurística **HCBE** propone un enfoque de optimización multicriterio:

1.  **Optimización Global vs. Local**: Al incluir el factor de **Equilibrio**, el algoritmo evita saturar rutas baratas que agotan rápidamente a un solo proveedor, manteniendo opciones abiertas para el resto de la red de distribución.
2.  **Reducción de Riesgos Logísticos**: El factor **Prioridad de Demanda** asegura que los puntos críticos (destinos con mayor demanda) sean atendidos primero, minimizando el riesgo de desabastecimiento en nodos vitales.
3.  **Eficiencia Computacional**: Proporciona una solución inicial de alta calidad (cercana a la óptima) con un esfuerzo computacional mínimo, lo cual es vital en problemas de transporte a gran escala en tiempo real.
4.  **Adaptabilidad**: El índice $HCBE$ permite ajustar pesos si se deseara dar más importancia al costo o al equilibrio, convirtiéndolo en un modelo flexible para distintos escenarios empresariales.


## 3. Resumen de Pruebas Realizadas

A continuación se detallan los resultados obtenidos en las pruebas ejecutadas:

| Caso de Prueba | Dimensiones (MxN) | Costo Total (Z) | Observaciones |
| :--- | :---: | :---: | :--- |
| **Prueba 1** | 3 x 3 | **605** | Problema estándar de baja escala. |
| **Prueba 2** | 3 x 4 | **2850** | Escala media con demandas variadas. |
| **Prueba 3** | 4 x 6 | **510** | Problema complejo con múltiples destinos. |

## 4. Análisis Detallado por Caso

### Prueba 1 (BTP-1)
- **Configuración**: 3 orígenes, 3 destinos.
- **Resultado Z**: 605.
- **Análisis**: La heurística logró una distribución eficiente, concentrando las mayores asignaciones en las rutas de menor costo relativo considerando el balance de stock.

### Prueba 2 (BTP-4)
- **Configuración**: 3 orígenes, 4 destinos.
- **Resultado Z**: 2850.
- **Análisis**: A pesar del incremento en la complejidad, el factor de "Prioridad de Demanda" permitió satisfacer rápidamente los destinos más grandes, minimizando penalizaciones implícitas.

### Prueba 3 (BTP-10)
- **Configuración**: 4 orígenes, 6 destinos.
- **Resultado Z**: 510.
- **Análisis**: Este caso demuestra la robustez del algoritmo en matrices más grandes, manteniendo un costo competitivo a pesar del aumento de variables.

## 5. Conclusiones
La heurística **HCBE** demuestra ser una herramienta eficaz para encontrar soluciones factibles de alta calidad de manera rápida. La integración del factor de equilibrio evita agotamientos prematuros de oferta en rutas críticas, mientras que la prioridad de demanda asegura un flujo lógico de materiales.

Este análisis valida que la heurística es apta para ser presentada en el informe final de competencia.
