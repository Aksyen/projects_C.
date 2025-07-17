/**
 * @file tsp_nearest_neighbor.c
 * @brief Реализация алгоритма ближайшего соседа (Nearest Neighbor) для решения
 * задачи коммивояжера.
 *
 * @details
 * Алгоритм ближайшего соседа - это жадный эвристический алгоритм для
 * приближенного решения задачи коммивояжера.
 *
 * Особенности реализации:
 * - Работает как с симметричными, так и с асимметричными графами
 * - Временная сложность O(n^2)
 * - Пространственная сложность O(n)
 * - Не гарантирует оптимальное решение, но дает быстрое приближенное
 * - Начинает обход с начальной вершины и на каждом шаге выбирает ближайшую
 * непосещенную вершину
 *
 * @note Для небольших графов (n < 100) алгоритм работает практически мгновенно.
 * Для улучшения качества решения можно комбинировать с другими методами,
 * например 2-opt.
 *
 * @warning Качество решения может значительно отличаться от оптимального,
 * особенно для графов со специфической структурой весов.
 */

#include "../graph/graph.h"
#include "graph_algorithms.h"
#include "utils.h"

static int build_path(int size, int graph_matrix[size][size], TSM_RESULT* res);

/**
 * @brief Решает задачу коммивояжера (TSP) с помощью алгоритма
 * NN(Nearest Neighbor) (Приближенное решение).
 *
 * @param graph Указатель на граф.
 * @return TSM_RESULT*, если путь не найден NULL. Память для TSM_RESULT*
 * выделяется динамически, следует вызвать free_tsm_result() для освобождения
 * выделенной памяти при завершении работы с TSM_RESULT*.
 */
TSM_RESULT* solve_tsp_nearest_neighbor(const Graph* graph) {
  if (!graph || !graph->matrix || graph->size <= 1) return NULL;

  const int size = get_size_graph(graph);
  TSM_RESULT* res = create_tsm_result(size);
  if (!res) return NULL;

  // Матрица графа
  const int** matrix = get_matrix_graph(graph);
  int graph_matrix[size][size];
  matrix_zero_to_default(size, graph_matrix, matrix);

  if (build_path(size, graph_matrix, res) == -1) {
    fprintf(stderr, "Error: it is impossible to set a route (INF)\n");
    free_tsm_result(res);
    res = NULL;
  }
  return res;
}

/**
 * @brief Строит маршрут по алгоритму NN(Nearest Neighbor).
 *
 * @param size Количество вершин графа.
 * @param graph_matrix Матрица смежности графа.
 * @param res Указатель на TSM_RESULT*.
 * @return 0 при успешном нахождении пути, иначе -1.
 */
static int build_path(int size, int graph_matrix[size][size], TSM_RESULT* res) {
  // Массив для отслеживания посещенных вершин
  bool visited[size];
  for (int i = 0; i < size; i++) visited[i] = 0;

  // Начинаем с вершины 0
  int current_vertex = 0;
  res->vertices[0] = current_vertex;
  visited[current_vertex] = true;
  res->distance = 0;

  for (int i = 1; i < size; i++) {
    int nearest_vertex = -1;
    double min_distance = INF;

    // Поиск ближайшего непосещенного соседа
    for (int j = 0; j < size; j++) {
      if (!visited[j] && graph_matrix[current_vertex][j] != INF &&
          graph_matrix[current_vertex][j] < min_distance) {
        min_distance = graph_matrix[current_vertex][j];
        nearest_vertex = j;
      }
    }

    // Если не нашли следующую вершину (граф несвязный)
    if (nearest_vertex == -1) return -1;

    // Добавляем вершину в маршрут
    res->vertices[i] = nearest_vertex;
    res->distance += min_distance;
    visited[nearest_vertex] = true;
    current_vertex = nearest_vertex;
  }

  // Замыкаем цикл - возвращаемся в начальную вершину
  if (graph_matrix[current_vertex][res->vertices[0]] == INF) return -1;
  res->vertices[size] = res->vertices[0];
  res->distance += graph_matrix[current_vertex][res->vertices[0]];
  return 0;
}