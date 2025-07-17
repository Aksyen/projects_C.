#include "graph_algorithms.h"

/*
Что такое алгоритм Прима
Алгоритм Прима — жадный алгоритм, который строит MST, начиная с одной вершины и
постепенно добавляя ближайшую вершину, которая соединена с уже построенным
деревом.

Требования:
Граф должен быть неориентированным и связным.

Вес всех рёбер должен быть неотрицательным.

Результат — матрица смежности дерева минимального веса.
*/

/**
 * @brief Поиск минимального остовного дерева (MST) с помощью алгоритма Прима.
 *
 * @param graph Указатель на граф (неориентированный, связный).
 * @return Матрица смежности MST (int**), или NULL при ошибке.
 *         Память необходимо освободить с помощью remove_matrix().
 */
int** get_least_spanning_tree(const Graph* graph) {
  if (!graph) return NULL;

  int size = get_size_graph(graph);
  const int** matrix = get_matrix_graph(graph);

  int* key = malloc(size * sizeof(int));     // веса ребер
  int* parent = malloc(size * sizeof(int));  // вершины-предки
  int* in_mst = calloc(size, sizeof(int));   // включены ли в MST

  if (!key || !parent || !in_mst) {
    free(key);
    free(parent);
    free(in_mst);
    return NULL;
  }

  for (int i = 0; i < size; ++i) {
    key[i] = INF;
    parent[i] = -1;
  }

  key[0] = 0;

  for (int count = 0; count < size - 1; ++count) {
    int min = INF, u = -1;

    for (int v = 0; v < size; ++v)
      if (!in_mst[v] && key[v] < min) {
        min = key[v];
        u = v;
      }

    if (u == -1) break;
    in_mst[u] = 1;

    for (int v = 0; v < size; ++v) {
      if (matrix[u][v] > 0 && !in_mst[v] && matrix[u][v] < key[v]) {
        key[v] = matrix[u][v];
        parent[v] = u;
      }
    }
  }

  // Создаём матрицу MST
  int** mst = create_matrix(size, size);
  if (!mst) {
    free(key);
    free(parent);
    free(in_mst);
    return NULL;
  }

  for (int v = 1; v < size; ++v) {
    int u = parent[v];
    if (u != -1) {
      mst[u][v] = matrix[u][v];
      mst[v][u] = matrix[u][v];  // неориентированный
    }
  }

  free(key);
  free(parent);
  free(in_mst);
  return mst;
}