#include "../stack/stack.h"
#include "graph_algorithms.h"

/*
Используешь DFS, когда нужно:

  Проверить достижимость.

  Найти все компоненты связности.

  Найти все возможные пути / варианты.

  Топологическая сортировка.

  Проверка на циклы.
*/

/**
 * @brief Нерекурсивный обход графа в глубину (DFS), начиная с указанной
 * вершины.
 *
 * @param graph Указатель на граф.
 * @param start_vertex Индекс начальной вершины (от 0 до size - 1).
 * @return Указатель на массив, содержащий вершины в порядке обхода.
 *         Размер массива равен количеству вершин графа.
 *         В случае ошибки возвращает NULL.
 *
 * @note Память под возвращаемый массив выделяется динамически.
 *       После использования её необходимо освободить вручную.
 */
int* depth_first_search(const Graph* graph, int start_vertex) {
  if (!graph) return NULL;

  int size_graph = get_size_graph(graph);

  if (start_vertex < 0 || start_vertex >= size_graph) return NULL;

  int* visited = calloc(size_graph, sizeof(int));
  int* result = calloc(size_graph, sizeof(int));
  if (!visited || !result) {
    free(visited);
    free(result);
    return NULL;
  }

  // Заполняем результат -1
  for (int i = 0; i < size_graph; i++) result[i] = -1;

  Stack* s = stack_create();
  push_stack(s, start_vertex);
  int index = 0;

  const int** matrix = get_matrix_graph(graph);

  while (!empty_stack(s)) {
    int v = pop_stack(s);

    if (!visited[v]) {
      visited[v] = 1;
      result[index++] = v;

      // Добавляем соседей в стек в обратном порядке
      for (int i = size_graph - 1; i >= 0; i--) {
        if (matrix[v][i] > 0 && !visited[i]) {
          push_stack(s, i);
        }
      }
    }
  }

  destroy_stack(s);
  free(visited);

  return result;  // result содержит size_graph элементов
}
