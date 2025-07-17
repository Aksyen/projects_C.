/**
 * @file solve_traveling_salesman_problem.c
 * @brief Реализация муравьиного алгоритма (ACO) для решения задачи коммивояжёра
 * (TSP)
 *
 * @details
 * ### Основные особенности алгоритма:
 * - Метод оптимизации, вдохновлённый поведением муравьёв в природе
 * - Использует "феромоны" для маркировки удачных путей
 * - Комбинирует жадный выбор с вероятностным исследованием пространства решений
 * - Итеративный процесс с постепенным улучшением решения
 *
 * - Изменяя параметры можно оптимизировать время и точность работы алгоритма.
 */

#include <float.h>
#include <math.h>
#include <time.h>

#include "../graph/graph.h"
#include "graph_algorithms.h"
#include "utils.h"

// Параметры алгоритма
#define ALPHA 1.0  // Влияние феромонов.
#define BETA 2.0  // Влияние эвристической информации (обычно 1/distance).
#define RHO 0.5  // Коэффициент испарения феромонов.
#define Q 100.0  // Количество феромона, оставляемого муравьем.
#define ANT_COUNT 50  // Количество муравьев в колонии.
#define MAX_ITER 100  // Максимальное количество итераций.

/**
 * @brief Структура для представления муравья.
 */
typedef struct {
  int* path;             // Пройденный путь
  int path_length;       // Длина текущего пути
  double path_distance;  // Общая длина пути
  int* visited;  // Массив посещенных вершин (0 - не посещена, 1 - посещена)
} Ant;

static int main_loop(int size, int best_path[], double* best_distance,
                     double** pheromone, Ant** ants,
                     int graph_matrix[size][size]);
static Ant** init_ant_colony(int size);
static void free_ant_colony(Ant** ant_colony);
static void reset_ants(int size, Ant** ants);
static double** init_pheromone(int size, int graph_matrix[size][size]);
static void free_pheromone(double** mat, int size);
static int has_available_city(int size, int current_vertex,
                              int graph_matrix[size][size], const Ant* ant);
static void get_probabilities(int size, int current_vertex,
                              double probabilities[], double** pheromone,
                              int graph_matrix[size][size], const Ant* ant);
static void chose_next_vertex(int size, int current_vertex,
                              const double probabilities[],
                              int graph_matrix[size][size], Ant* ant);
static void pheromone_process(int size, double** pheromone, Ant** ants,
                              int graph_matrix[size][size]);
static void update_best_path(int size, double* best_distance, int best_path[],
                             const Ant* ant);
static void conect_last_first_vertex(int size, int graph_matrix[size][size],
                                     Ant* ant);

/**
 * @brief Решает задачу коммивояжера с помощью муравьиного алгоритма (ACO)
 * (Приближенное решение).
 *
 * @param graph Указатель на граф (матрица смежности).
 * @return TSM_RESULT*, если путь не найден NULL. Память для TSM_RESULT*
 * выделяется динамически, следует вызвать free_tsm_result() для освобождения
 * выделенной памяти при завершении работы с TSM_RESULT*.
 */
TSM_RESULT* solve_traveling_salesman_problem(const Graph* graph) {
  if (!graph || !graph->matrix || graph->size <= 1) return NULL;

  const int size = get_size_graph(graph);
  double best_distance = DBL_MAX;
  int best_path[size + 1];
  const int** matrix = get_matrix_graph(graph);
  int graph_matrix[size][size];
  matrix_zero_to_default(size, graph_matrix, matrix);

  // Создание таблицы феромонов.
  double** pheromone = init_pheromone(size, graph_matrix);
  if (!pheromone) return NULL;

  // Создание колонии муравьев
  Ant** ants = init_ant_colony(size);
  if (!ants) {
    free_pheromone(pheromone, size);
    return NULL;
  }

  int status =
      main_loop(size, best_path, &best_distance, pheromone, ants, graph_matrix);

  free_pheromone(pheromone, size);
  free_ant_colony(ants);

  // Создаем и возвращаем результат
  if (status) return NULL;
  TSM_RESULT* result = create_tsm_result(size);
  if (result) {
    best_path[size] = best_path[0];
    for (int i = 0; i < size + 1; i++) result->vertices[i] = best_path[i];
    result->distance = best_distance;
  }

  return result;
}

/**
 * @brief Главный цикл вычисления пути.
 *
 * @param size Размер графа.
 * @param best_path Массив с цершинами наикратчайшего пути.
 * @param best_distance Указатель на минимальное растояние.
 * @param pheromone Таблица феромонов.
 * @param ants Указатель на колонию муравьёв.
 * @param graph Указатель на граф.
 */
static int main_loop(int size, int best_path[], double* best_distance,
                     double** pheromone, Ant** ants,
                     int graph_matrix[size][size]) {
  int status = 0;

  for (int iter = 0; iter < MAX_ITER && !status; iter++) {
    reset_ants(size, ants);

    // Построение путей для каждого муравья
    for (int ant_idx = 0; ant_idx < ANT_COUNT && !status; ant_idx++) {
      Ant* ant = ants[ant_idx];

      // Пока муравей не посетил все вершины.
      while (ant->path_length < size && !status) {
        int current_vertex = ant->path[ant->path_length - 1];
        double probabilities[size];

        // Если существуют непосещенные вуршины, но пути к ним нет.
        if (!has_available_city(size, current_vertex, graph_matrix, ant)) {
          status = -1;
          break;
        }

        get_probabilities(size, current_vertex, probabilities, pheromone,
                          graph_matrix, ant);
        chose_next_vertex(size, current_vertex, probabilities, graph_matrix,
                          ant);
      }

      // Если существуют доступные вершины.
      if (!status) {
        conect_last_first_vertex(size, graph_matrix, ant);
        update_best_path(size, best_distance, best_path, ant);
      }
    }

    // Если существуют доступные вершины.
    if (!status) pheromone_process(size, pheromone, ants, graph_matrix);
  }
  return status;
}

/**
 * @brief Обновление феромоновых троп.
 *
 * @param size Размер графа.
 * @param best_distance Указатель на минимальное растояние.
 * @param best_path Массив с цершинами наикратчайшего пути.
 * @param ant Указатель на муравья.
 */
static void update_best_path(int size, double* best_distance, int best_path[],
                             const Ant* ant) {
  // Обновляем лучший найденный путь
  if (ant->path_distance < *best_distance) {
    *best_distance = ant->path_distance;
    memcpy(best_path, ant->path, (size) * sizeof(int));
  }
}

/**
 * @brief Обновление феромоновых троп.
 *
 * @param size Размер графа.
 * @param graph_matrix Таблица смежности графа.
 * @param ant Указатель на муравья.
 */
static void conect_last_first_vertex(int size, int graph_matrix[size][size],
                                     Ant* ant) {
  // Добавляем путь из последней вершины в первую.
  int last_vertex = ant->path[size - 1];
  int first_vertex = ant->path[0];
  if (graph_matrix[last_vertex][first_vertex] != INF) {
    ant->path_distance += graph_matrix[last_vertex][first_vertex];
  } else {
    // Если нет пути обратно, делаем путь недопустимым
    ant->path_distance = DBL_MAX;
  }
}

/**
 * @brief Инициализирует таблицу феромонов.
 *
 * @param size Размер графа.
 * @return Указатель на матрицу, иначе NULL.
 */
static double** init_pheromone(int size, int graph_matrix[size][size]) {
  if (size < 1) return NULL;

  double** pheromone = (double**)malloc(size * sizeof(double*));
  if (pheromone == NULL) return NULL;

  for (int i = 0; i < size; i++) {
    pheromone[i] = (double*)calloc(size, sizeof(double));
    // Если не удалось выделить память.
    if (pheromone[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(pheromone[j]);
      }
      free(pheromone);
      pheromone = NULL;
      return NULL;
    }
    // Инициализация феромонов (начальное значение минимальное).
    for (int j = 0; j < size; j++)
      pheromone[i][j] = (graph_matrix[i][j] != INF) ? 0.1 : 0.0;
  }
  return pheromone;
}

/**
 * @brief Инициализирует колонию муравьев для графа заданного размераю.
 * Кония это массив муравьев.
 *
 * @param size Размер графа.
 * @return Указатель на колонию (Ant**), иначе NULL.
 */
static Ant** init_ant_colony(int size) {
  if (size < 1) return NULL;

  Ant** ants = (Ant**)malloc(ANT_COUNT * sizeof(Ant*));
  if (!ants) return NULL;

  for (int i = 0; i < ANT_COUNT; i++) {
    ants[i] = (Ant*)malloc(sizeof(Ant));
    // Если не удалось выделить память.
    if (ants[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(ants[j]);
      }
      free(ants);
      ants = NULL;
      return NULL;
    }
    ants[i]->path = (int*)malloc(size * sizeof(int));
    ants[i]->visited = (int*)calloc(size, sizeof(int));
    ants[i]->path_length = 0;
    ants[i]->path_distance = 0.0;
  }

  return ants;
}

/**
 * @brief Освобождает память, занятую колонией.
 *
 * @param ant_colony Указатель на колонию.
 */
static void free_ant_colony(Ant** ant_colony) {
  if (ant_colony != NULL) {
    for (int i = 0; i < ANT_COUNT; i++) {
      free(ant_colony[i]->path);
      free(ant_colony[i]->visited);
      free(ant_colony[i]);
    }
    free(ant_colony);
  }
}

/**
 * @brief Освобождает матрицу.
 *
 * @param mat Указатель на матрицу.
 * @param size Размер матрицы.
 */
static void free_pheromone(double** mat, int size) {
  if (mat != NULL) {
    for (int i = 0; i < size; i++) {
      free(mat[i]);
    }
    free(mat);
  }
}

/**
 * @brief Выполняет сброс состояния муравьёв, устанавливает случайную стартовую
 * вершину.
 *
 * @param size Количество вершин.
 * @param ants Указатель на колонию муравьёв.
 */
static void reset_ants(int size, Ant** ants) {
  // Очищаем пути муравьев перед новой итерацией
  for (int i = 0; i < ANT_COUNT; i++) {
    memset(ants[i]->visited, 0, size * sizeof(int));
    ants[i]->path_length = 0;
    ants[i]->path_distance = 0.0;

    // Начинаем путь со случайной вершины
    int start_vertex = rand() % size;
    ants[i]->path[0] = start_vertex;
    ants[i]->visited[start_vertex] = 1;
    ants[i]->path_length = 1;
  }
}

/**
 * @brief Проверяет существуют ли доступные вершины среди непосещенных из
 * текущей.
 *
 * @param size Размер графа.
 * @param current_vertex Номер текущей вершины.
 * @param graph_matrix Матрица смежности графа.
 * @param ant Указатель на муравья.
 * @return Число больше нуля если существуют доступные вершины, иначе 0.
 */
static int has_available_city(int size, int current_vertex,
                              int graph_matrix[size][size], const Ant* ant) {
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (!ant->visited[i] && graph_matrix[current_vertex][i] != INF) {
      count = 1;
      break;
    }
  }

  return count;
}

/**
 * @brief Вычисляет вероятность выбора слудующего ворода.
 *
 * @param size Размер графа.
 * @param current_vertex Номер текущей вершины.
 * @param probabilities Список вероятностей для каждой вершины.
 * @param pheromone Таблица феромонов.
 * @param graph_matrix Матрица смежности графа.
 * @param ant Указатель на муравья.
 */
static void get_probabilities(int size, int current_vertex,
                              double probabilities[], double** pheromone,
                              int graph_matrix[size][size], const Ant* ant) {
  double probability_sum = 0.0;
  // Вычисляем вероятности перехода в каждую вершину.
  for (int i = 0; i < size; i++) {
    if (ant->visited[i] || graph_matrix[current_vertex][i] == 0) {
      probabilities[i] = 0.0;
    } else {
      probabilities[i] = pow(pheromone[current_vertex][i], ALPHA) *
                         pow(1.0 / graph_matrix[current_vertex][i], BETA);
      probability_sum += probabilities[i];
    }
  }

  // Нормализуем вероятности
  if (probability_sum > 0.0) {
    for (int i = 0; i < size; i++) {
      probabilities[i] /= probability_sum;
    }
  }
}

/**
 * @brief Выбирает следующую вершину для муровья.
 *
 * @param size Размер графа.
 * @param current_vertex Номер текущей вершины.
 * @param probabilities Список вероятностей для каждой вершины.
 * @param graph_matrix Матрица смежности графа.
 * @param ant Указатель на муравья.
 */
static void chose_next_vertex(int size, int current_vertex,
                              const double probabilities[],
                              int graph_matrix[size][size], Ant* ant) {
  // Выбираем следующую вершину на основе вероятностей.
  double r = (double)rand() / RAND_MAX;
  double sum = 0.0;
  int next_vertex = -1;
  int i;
  for (i = 0; i < size; i++) {
    sum += probabilities[i];
    if (sum >= r && !ant->visited[i] &&
        graph_matrix[current_vertex][i] != INF) {
      next_vertex = i;
      break;
    }
  }

  // Если не удалось выбрать вершину (из-за округления), выбираем первую
  // доступную.
  if (i == size) {
    for (i = 0; i < size; i++) {
      if (!ant->visited[i] && graph_matrix[current_vertex][i] != INF) {
        next_vertex = i;
        break;
      }
    }
  }

  // Добавляем вершину в путь.
  ant->path[ant->path_length++] = next_vertex;
  ant->visited[next_vertex] = 1;
  ant->path_distance += graph_matrix[current_vertex][next_vertex];
}

/**
 * @brief Обновление феромоновых троп.
 *
 * @param size Размер графа.
 * @param pheromone Таблица феромонов.
 * @param antы Указатель на колонию муравльёв.
 */
static void pheromone_process(int size, double** pheromone, Ant** ants,
                              int graph_matrix[size][size]) {
  // Испарение феромонов
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      pheromone[i][j] *= (1.0 - RHO);
    }
  }

  // Обновление феромонов на путях муравьев
  for (int ant_idx = 0; ant_idx < ANT_COUNT; ant_idx++) {
    Ant* ant = ants[ant_idx];
    double added_pheromone = Q / ant->path_distance;

    for (int i = 0; i < size - 1; i++) {
      int vertex1 = ant->path[i];
      int vertex2 = ant->path[i + 1];
      if (graph_matrix[vertex1][vertex2] != INF) {
        pheromone[vertex1][vertex2] += added_pheromone;
      }
    }

    // Добавляем феромон на путь от последней вершины к первой
    int last_vertex = ant->path[size - 1];
    int first_vertex = ant->path[0];
    if (graph_matrix[last_vertex][first_vertex] != INF) {
      pheromone[last_vertex][first_vertex] += added_pheromone;
    }
  }
}