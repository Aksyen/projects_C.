#include "../queue/queue.h"
#include "graph_algorithms.h"

/*
Используешь BFS, когда нужно:

  Найти кратчайший путь в невзвешенном графе.

  Пройти граф по уровням.

  Найти минимальное количество шагов, касаний, пересечений.
*/

/**
 * @brief Нерекурсивный обход графа в ширину (BFS), начиная с указанной вершины.
 *
 * @param graph Указатель на граф, представленный в виде матрицы смежности.
 *              Допустимы как ориентированные, так и неориентированные графы.
 * @param start_vertex Индекс начальной вершины (от 0 до size - 1).
 * @return Указатель на массив, содержащий вершины в порядке обхода.
 *         Размер массива равен количеству вершин графа.
 *         В случае ошибки возвращает NULL.
 *
 * @note Память под возвращаемый массив выделяется динамически.
 *       После использования её необходимо освободить вручную с помощью free().
 */
int* breadth_first_search(const Graph* graph, int start_vertex) {
  if (!graph) return NULL;

  int size = get_size_graph(graph);
  if (start_vertex < 0 || start_vertex >= size) return NULL;

  int* visited = calloc(size, sizeof(int));
  int* result = calloc(size, sizeof(int));
  if (!visited || !result) {
    free(visited);
    free(result);
    return NULL;
  }

  // Заполняем результат -1
  for (int i = 0; i < size; i++) result[i] = -1;

  Queue* q = queue_create();
  push_queue(q, start_vertex);
  visited[start_vertex] = 1;

  int index = 0;
  const int** matrix = get_matrix_graph(graph);

  while (!empty_queue(q)) {
    int v = pop_queue(q);
    result[index++] = v;

    for (int i = 0; i < size; ++i) {
      if (matrix[v][i] > 0 && !visited[i]) {
        push_queue(q, i);
        visited[i] = 1;
      }
    }
  }

  destroy_queue(q);
  free(visited);
  return result;
}
