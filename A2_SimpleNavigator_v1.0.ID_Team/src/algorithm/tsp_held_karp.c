/**
 * @file tsp_held_karp.c
 * @brief Реализация алгоритма Хелда-Карпа для решения задачи коммивояжера
 *
 * @details
 * Алгоритм Хелда-Карпа - это динамический алгоритм для точного решения задачи
 * коммивояжера. Особенности данной реализации:
 * - Работает с симметричными, неориентированными графами
 * - Использует динамическое программирование для нахождения оптимального
 * маршрута
 * - Временная сложность O(n^2 * 2^n)
 * - Пространственная сложность O(n * 2^n)
 *
 * @note Для больших графов (n > 20) рекомендуется использовать эвристические
 * методы, так как алгоритм требует значительных вычислительных ресурсов.
 */

#include "../graph/graph.h"
#include "graph_algorithms.h"
#include "utils.h"

static int get_result(int size, int **path, int graph_matrix[size][size],
                      int **dp, TSM_RESULT *res);
static void fill_dp(int size, int **path, int graph_matrix[size][size],
                    int **dp);

/**
 * @brief Решает задачу коммивояжера (TSP) с помощью алгоритма
 * Хелда-Карпа (Оптимальное решение).
 *
 * @param graph Указатель на граф.
 * @return TSM_RESULT* если путь не найден NULL. Память для TSM_RESULT*
 * выделяется динамически, следует вызвать free_tsm_result() для освобождения
 * выделенной памяти при завершении работы с TSM_RESULT*.
 * @note Данная реализация применима для семеричного, неориентированного графа.
 */
TSM_RESULT *solve_tsp_held_karp(const Graph *graph) {
  if (!graph || !graph->matrix || graph->size <= 1) return NULL;

  const int size = get_size_graph(graph);

  TSM_RESULT *res = create_tsm_result(size);
  if (!res) return NULL;

  // Общее количество подмножеств вершин (2^n)
  const int totalSubsets = 1 << size;
  const int **matrix = get_matrix_graph(graph);
  int graph_matrix[size][size];
  matrix_zero_to_default(size, graph_matrix, matrix);

  // Используем динамическое выделение памяти для больших массивов
  int **dp = create_matrix(totalSubsets, size);
  int **path = create_matrix(totalSubsets, size);
  if (!dp || !path) {
    remove_matrix(dp, totalSubsets);
    remove_matrix(path, totalSubsets);
    errno = ENOMEM;
    return NULL;
  }

  // Заполняем массивы дефолтными значеничми.
  for (int i = 0; i < totalSubsets; i++) {
    for (int j = 0; j < size; j++) {
      dp[i][j] = INF;
      path[i][j] = -1;
    }
  }

  fill_dp(size, path, graph_matrix, dp);

  // Проверка на наличие решения
  if (get_result(size, path, graph_matrix, dp, res)) {
    fprintf(stderr, "Error: it is impossible to set a route (INF)\n");
    free_tsm_result(res);
    res = NULL;
  }

  // Освобождаем память
  remove_matrix(dp, totalSubsets);
  remove_matrix(path, totalSubsets);

  return res;
}

/**
 * @brief Заплняет таблицу динамического программирования. Высчитывает
 * минимальную стоимость пути для каждого подмножества вершин. А также заполняет
 * таблицу порядка подмножества вершин.
 *
 * @param size Количество вершин графа.
 * @param path Таблица с путями для кажой комбинации вершин.
 * @param graph_matrix Матрица смежности графа.
 * @param dp Таблица с подмножеством вершин и минимальное расстояние для них.
 */
static void fill_dp(int size, int **path, int graph_matrix[size][size],
                    int **dp) {
  const int totalSubsets = 1 << size;
  // Базовый случай: начало из вершины 0
  dp[1][0] = 0;  // Стоимость маршрута 0

  // Основной алгоритм: перебираем все возможные подмножества вершин
  for (int mask = 1; mask < totalSubsets; mask++) {
    for (int u = 0; u < size; u++) {
      // Проверяем, что вершина u присутствует в текущем подмножестве и для него
      // посчитан путь, иначе пропустить итерацию.
      if (!(mask & (1 << u)) || dp[mask][u] == INF) continue;

      // Перебираем все вершины, которые еще не посещены
      for (int v = 0; v < size; v++) {
        // Пропускаем уже посещенные вершины или в которые нет пути.
        if (mask & (1 << v) || graph_matrix[u][v] == INF) continue;

        // Обновляем стоимость для нового подмножества
        int newMask = mask | (1 << v);
        int sum = dp[mask][u] + graph_matrix[u][v];
        if (sum < dp[newMask][v]) {
          dp[newMask][v] = sum;
          path[newMask][v] = u;
        }
      }
    }
  }
}

/**
 * @brief Получает минимальный путь и список посещенных вершин, заносит данные в
 * TSM_RESULT*.
 *
 * @param size Количество вершин графа.
 * @param path Таблица с путями для кажой комбинации вершин.
 * @param graph_matrix Матрица смежности графа.
 * @param dp Таблица с подмножеством вершин и минимальное расстояние для них.
 * @param res Указатель на TSM_RESULT.
 * @return 0 в случае успеха, иначе -1.
 */
static int get_result(int size, int **path, int graph_matrix[size][size],
                      int **dp, TSM_RESULT *res) {
  const int full_mask = (1 << size) - 1;
  int minCost = INF;
  int last_city = -1;

  // Находим вершину с минимальной стоимостью возврата в начальную точку
  for (int i = 1; i < size; i++) {
    if (dp[full_mask][i] != INF && graph_matrix[i][0] != INF) {
      int totalCost = dp[full_mask][i] + graph_matrix[i][0];
      if (totalCost < minCost) {
        minCost = totalCost;
        last_city = i;
      }
    }
  }

  if (minCost == INF || last_city == -1) return -1;

  res->distance = minCost;

  // Восстанавливаем маршрут в обратном порядке
  int current_mask = full_mask;
  int current_city = last_city;
  int route_length = size;

  // Начинаем с конца (предпоследняя вершина перед возвратом в 0)
  res->vertices[route_length--] = 0;  // Замыкаем цикл (возвращаемся в 0)
  res->vertices[route_length--] = current_city;

  // Продолжаем восстановление пути
  while (route_length >= 0) {
    int prev_city = path[current_mask][current_city];
    if (prev_city == -1) break;  // Достигли начала

    current_mask &= ~(1 << current_city);  // Удаляем текущую вершину из маски
    current_city = prev_city;
    res->vertices[route_length--] = current_city;
  }

  return 0;
}