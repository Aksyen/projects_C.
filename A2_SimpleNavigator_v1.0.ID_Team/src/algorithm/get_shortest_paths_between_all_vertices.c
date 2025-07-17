#include "graph_algorithms.h"

/*
Что делает алгоритм Флойда–Уоршелла
Принимает взвешенный граф с неотрицательными весами (может быть
ориентированным).

Возвращает матрицу расстояний dist[i][j] — кратчайшее расстояние от i до j.

Работает за O(n³).
*/

/**
 * @brief Поиск кратчайших путей между всеми парами вершин
 *        с использованием алгоритма Флойда–Уоршелла.
 *
 * @param graph Указатель на граф.
 * @return Указатель на квадратную матрицу (int**),
 *         содержащую кратчайшие расстояния между вершинами.
 *         В случае ошибки возвращает NULL.
 *
 * @note Значения INF (2147483647) означают, что путь не существует.
 *       Память выделяется динамически, необходимо вызвать remove_matrix() после
 * использования.
 */
int** get_shortest_paths_between_all_vertices(const Graph* graph) {
  if (!graph) return NULL;

  int size = get_size_graph(graph);
  const int** matrix = get_matrix_graph(graph);

  // Выделяем и инициализируем матрицу расстояний
  int** dist = create_matrix(size, size);
  if (!dist) return NULL;

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (i == j)
        dist[i][j] = 0;
      else if (matrix[i][j] > 0)
        dist[i][j] = matrix[i][j];
      else
        dist[i][j] = INF;
    }
  }

  // Основной цикл Флойда–Уоршелла
  for (int k = 0; k < size; ++k) {
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        if (dist[i][k] != INF && dist[k][j] != INF) {
          if (dist[i][j] > dist[i][k] + dist[k][j]) {
            dist[i][j] = dist[i][k] + dist[k][j];
          }
        }
      }
    }
  }

  return dist;
}
