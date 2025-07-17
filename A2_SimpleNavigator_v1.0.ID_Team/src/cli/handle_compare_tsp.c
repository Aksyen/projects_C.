/**
 * @file handle_compare_tsp.c
 * @brief Обработцик сравнения работы алгоритмов tsp.
 *
 * @details
 * Для каждого алгоритма создается независимый процесс.
 * Преимущества:
 * - Параллельное выполнение ускоряет работу обработчика
 * - Процессы независимы, если один из алгоритмов завершится с ошибкой это не
 *   повлияет на работу остальных(за некоторым исключением)
 *
 * Недостатки:
 * - Так как выполнение происходит параллельно, то может возникнуть ситуация при
 * которой один из алгоритмов исчерпает доступную память что может сказаться на
 * работе остальных алгоритмов.
 * Например алгоритм Хелда-Карпа потребляет память експоненциально для графа в
 * 20 вершин менее 100 МБ для 25 уже более 2 ГБ
 *
 */

#include "cli.h"

/**
 * @brief Указатель для функций TSP.
 */
typedef TSM_RESULT* (*TSP_Solver)(const Graph*);

/**
 * @brief Структура для хранения времени выполнения алгоритма и найденого им
 * минимильного пути.
 */
typedef struct {
  double time;
  double distance;
} RES_COMPARE;

static int get_iterations();
static RES_COMPARE run_algorithm(int iterations, const Graph* graph,
                                 TSP_Solver solver);
static void benchmark_tsp_algorithms(int iteranions, const Graph* graph,
                                     TSP_Solver solvers[],
                                     RES_COMPARE results[], int num_algorithms);
static void print_res_compare(int count, const char* name_algorithms[],
                              RES_COMPARE results[]);

/**
 * @brief Вычисляет время выполнения каждой функции для заданного количества
 * раз.
 * @param graph Указатель на граф.
 */
void handle_tsp_compare(const Graph* graph) {
  const char* name_algorithms[] = {"Ant Colony Optimization (ACO)",
                                   "Held-Karp algorithm",
                                   "Nearest neighbour algorithm (NN)"};
  TSP_Solver algorithms[] = {solve_traveling_salesman_problem,
                             solve_tsp_held_karp, solve_tsp_nearest_neighbor};
  int count_algorithms = sizeof(algorithms) / sizeof(algorithms[0]);
  RES_COMPARE results[count_algorithms];

  int size = get_size_graph(graph);
  if (!confirm_large_graph_processing(size)) return;

  int iterations = get_iterations();

  benchmark_tsp_algorithms(iterations, graph, algorithms, results,
                           count_algorithms);

  print_res_compare(count_algorithms, name_algorithms, results);
}

/**
 * @brief Получает пользовательский ввод количества итераций.
 * @return Количество итераций.
 */
static int get_iterations() {
  int iterations = 0;
  const char* title =
      "Comparison of methods for solving the traveling salesman problem";
  while (1) {
    clear();

    // Вывод заголовка
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(2, (COLS - strlen(title)) / 2, "%s", title);
    attroff(COLOR_PAIR(1) | A_BOLD);

    mvprintw(4, 5, "Number of iterations (must be > 0) or ESC to cancel:");

    int ch = getch();
    if (ch == ESCAPE) return ESCAPE;
    ungetch(ch);  // Вернуть символ обратно в stdin

    echo();
    scanw("%d", &iterations);
    noecho();

    // Если ввод коректен завершить цикл
    if (iterations > 0) {
      break;
    }

    // Ошибка ввода
    attron(COLOR_PAIR(3));
    mvprintw(6, 5, "Error: Number of iterations (must be > 0)!");
    attroff(COLOR_PAIR(3));
    mvprintw(8, 5, "Press any key to try again...");
    refresh();
    getch();
  }
  return iterations;
}

/**
 * @brief Выполняет переданную функцию заданное количество раз.
 * @param iterations Количество итераций.
 * @param graph Указатель на граф.
 * @param solver Функция решения TSP задаци.
 * @return Время выполнения функции в цикле.
 */
static RES_COMPARE run_algorithm(int iterations, const Graph* graph,
                                 TSP_Solver solver) {
  RES_COMPARE res_comp = {-1, -1};
  clock_t start = clock();
  for (int i = 0; i < iterations; i++) {
    TSM_RESULT* res = solver(graph);
    if (!res) break;
    res_comp.distance = res->distance;
    free_tsm_result(res);
  }
  res_comp.time = (double)(clock() - start) / CLOCKS_PER_SEC;
  return res_comp;
}

/**
 * @brief Замеряет время работы переданых на выполнение функций для заданного
 * количества итераций.
 * @param iteranions Количество итераций.
 * @param graph Указатель на граф.
 * @param solvers Массив с функциями.
 * @param results Массив для записи времени выполнения и дистанции.
 * @param num_algorithms Количество алгоритмов.
 * @return Количество итераций.
 */
static void benchmark_tsp_algorithms(int iterations, const Graph* graph,
                                     TSP_Solver solvers[],
                                     RES_COMPARE results[],
                                     int num_algorithms) {
  int pipes[num_algorithms][2];
  pid_t pids[num_algorithms];

  // Создаём pipe'ы и процессы
  for (int i = 0; i < num_algorithms; i++) {
    if (pipe(pipes[i]) == -1) {
      perror("pipe failed");
      exit(EXIT_FAILURE);
    }

    pids[i] = fork();
    if (pids[i] == -1) {
      perror("fork failed");
      exit(EXIT_FAILURE);
    }

    if (pids[i] == 0) {    // Дочерний процесс
      close(pipes[i][0]);  // Закрываем чтение
      RES_COMPARE res_comp = run_algorithm(iterations, graph, solvers[i]);
      write(pipes[i][1], &res_comp, sizeof(RES_COMPARE));
      close(pipes[i][1]);
      exit(EXIT_SUCCESS);
    } else {               // Родительский процесс
      close(pipes[i][1]);  // Закрываем запись
    }
  }

  // Читаем результаты из pipe'ов
  for (int i = 0; i < num_algorithms; i++) {
    ssize_t bytes_read = read(pipes[i][0], &results[i], sizeof(RES_COMPARE));
    if (bytes_read != sizeof(RES_COMPARE)) {
      // Ошибка чтения или дочерний процесс завершился аварийно
      results[i].time = -1.0;  // Помечаем как ошибочный результат
      results[i].distance = -1.0;
    }
    close(pipes[i][0]);

    int status;
    waitpid(pids[i], &status, 0);

    if (WIFSIGNALED(status)) {
      fprintf(stderr, "Child process %d terminated by signal %d\n", pids[i],
              WTERMSIG(status));
    } else if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
      fprintf(stderr, "Child process %d exited abnormally\n", pids[i]);
    }
  }
}

/**
 * @brief Вывод в консоль временя работы алгоритмов для заданного количества
 * итераций.
 * @param count Количество алгоритмов.
 * @param name_algorithms Названия алгоритмов.
 * @param results Массив с временем выполнения каждого алгоритма.
 */
static void print_res_compare(int count, const char* name_algorithms[],
                              RES_COMPARE results[]) {
  int num_line = 2;
  int num_col = 6;
  clear();
  const char* title = "Algorithms execution time";
  const char* hint = "If the distance is -1, then the path has not been found.";

  attron(COLOR_PAIR(1) | A_BOLD);
  mvprintw(num_line, (COLS - strlen(title)) / 2, "%s", title);
  mvprintw(num_line + 1, (COLS - strlen(hint)) / 2, "%s", hint);
  attroff(COLOR_PAIR(1) | A_BOLD);

  attron(COLOR_PAIR(2) | A_BOLD);
  for (int i = 0; i < count; i++) {
    mvprintw(num_line + 3 + (2 * i), num_col,
             "%-40s: %.4f seconds, distance: %.d", name_algorithms[i],
             results[i].time, (int)results[i].distance);
    refresh();

    usleep(100000);
  }
  attroff(COLOR_PAIR(2) | A_BOLD);

  mvprintw(LINES - 2, (COLS - 20) / 2, "Press any key to continue...");
  getch();
}