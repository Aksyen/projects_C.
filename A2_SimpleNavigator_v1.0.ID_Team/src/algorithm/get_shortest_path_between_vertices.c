#include "graph_algorithms.h"

/*
Алгоритм Дейкстры — кратко и понятно
Алгоритм Дейкстры предназначен для поиска кратчайших путей от одной вершины до
всех остальных в графе с неотрицательными весами рёбер.

Ключевые свойства:
Работает как с ориентированными, так и с неориентированными графами.

Не работает правильно, если в графе есть отрицательные веса.

Подходит, когда нужно найти одно или несколько кратчайших расстояний, но не сам
путь (хотя можно модифицировать)
*/

/**
 * @brief Поиск кратчайшего пути между двумя вершинами с использованием
 * алгоритма Дейкстры.
 *
 * @param graph Указатель на граф.
 * @param vertex1 Индекс начальной вершины.
 * @param vertex2 Индекс конечной вершины.
 * @return Наименьшее расстояние между двумя вершинами, либо -1, если путь
 * отсутствует.
 */
int get_shortest_path_between_vertices(const Graph* graph, int vertex1,
                                       int vertex2) {
  if (!graph) return -1;

  int size = get_size_graph(graph);
  if (vertex1 < 0 || vertex2 < 0 || vertex1 >= size || vertex2 >= size)
    return -1;

  const int** matrix = get_matrix_graph(graph);

  int* dist = calloc(size, sizeof(int));
  int* visited = calloc(size, sizeof(int));
  if (!dist || !visited) {
    free(dist);
    free(visited);
    return -1;
  }

  for (int i = 0; i < size; ++i) {
    dist[i] = INF;
  }
  dist[vertex1] = 0;

  for (int i = 0; i < size; ++i) {
    // Найти непосещённую вершину с минимальной дистанцией
    int min_dist = INF;
    int u = -1;
    for (int j = 0; j < size; ++j) {
      if (!visited[j] && dist[j] < min_dist) {
        min_dist = dist[j];
        u = j;
      }
    }

    if (u == -1) break;  // все оставшиеся вершины недостижимы
    visited[u] = 1;

    for (int v = 0; v < size; ++v) {
      if (matrix[u][v] > 0 && !visited[v]) {
        int alt = dist[u] + matrix[u][v];
        if (alt < dist[v]) {
          dist[v] = alt;
        }
      }
    }
  }

  int result = (dist[vertex2] == INF) ? -1 : dist[vertex2];

  free(dist);
  free(visited);
  return result;
}
