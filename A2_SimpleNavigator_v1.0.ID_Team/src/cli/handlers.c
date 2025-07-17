#include "cli.h"

static int get_vertex(int count, const char* title);
static void print_order(int count, int order[], int mode);
static void print_res_num(int res, const char* res_title);
static void file_prompt(char filepath[]);
static void print_res_matrix(int count, int** matrix, const char* title);
static void print_res_tsm(int count, const TSM_RESULT* res,
                          const char* result_title);

/**
 * @brief Загрузить graph из файла.
 * @param graph Указатель на указатель графа.
 */
void handle_load_graph(Graph** graph) {
  char file_name[FILENAME_MAX] = {0};
  int status = get_file_path(file_name, MODE_F);
  if (!status) {
    if (*graph) free_graph(*graph);
    *graph = load_graph_from_file(file_name);
  }

  if (!*graph) {
    clear();
    refresh();
    show_error("Couldn't get the gpaph");
  }
}

/**
 * @brief Поиск bfs или dfs.
 * @param graph Указатель на граф.
 * @param mode Определяет используемый алгоритм MODE_BFS или MODE_DFS.
 */
void handle_bfs_dfs(const Graph* graph, int mode) {
  int size = get_size_graph(graph);
  const char* title = (mode == MODE_DFS)
                          ? "DFS Traversal - Select start vertex"
                          : "BFS Traversal - Select start vertex";

  int start_vertex = get_vertex(size, title);
  if (start_vertex == ESCAPE) return;

  int* order = (mode == MODE_DFS) ? depth_first_search(graph, start_vertex)
                                  : breadth_first_search(graph, start_vertex);

  if (!order) {
    show_error(
        "Algorithm execution failed - graph may be too large or invalid");
    return;
  }

  print_order(size, order, mode);

  free(order);
}

/**
 * @brief Вывести список посещенных вершин в двух вариантах: числовом и
 * буквенном.
 * @param count Количество вершин графа.
 * @param order Список почещенных вершин.
 * @param mode Определяет используемый алгоритм MODE_BFS или MODE_DFS.
 */
static void print_order(int count, int order[], int mode) {
  char name1[NAME_SIZE + 1] = {0};
  clear();
  const char* result_title =
      (mode == MODE_DFS) ? "DFS Traversal Result" : "BFS Traversal Result";

  attron(COLOR_PAIR(1) | A_BOLD);
  mvprintw(2, (COLS - strlen(result_title)) / 2, "%s", result_title);
  attroff(COLOR_PAIR(1) | A_BOLD);

  attron(COLOR_PAIR(2) | A_BOLD);
  for (int i = 0; i < count; i++) {
    if (order[i] == -1) break;

    mvprintw(6, 6 + i * 4, "%d", order[i]);
    if (i < count - 1) printw(" > ");
    // Буквенное представление.
    get_name_vertex(name1, order[i]);
    mvprintw(8, 6 + i * 4, "%s", name1);
    if (i < count - 1) printw(" > ");

    refresh();
    usleep(300000);
  }
  attroff(COLOR_PAIR(2) | A_BOLD);
  mvprintw(LINES - 2, (COLS - 20) / 2, "Press any key to continue...");
  getch();
}

/**
 * @brief Указать номер вершины графа.
 * @param count Количество вершин графа.
 * @param title Строка заголовка.
 */
static int get_vertex(int count, const char* title) {
  int start_vertex = -1;
  while (1) {
    clear();

    // Вывод заголовка
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(2, (COLS - strlen(title)) / 2, "%s", title);
    attroff(COLOR_PAIR(1) | A_BOLD);

    mvprintw(4, 5, "Enter vertex [0-%d] or ESC to cancel:", count - 1);

    int ch = getch();
    if (ch == ESCAPE) return ESCAPE;
    ungetch(ch);  // Вернуть символ обратно в stdin

    echo();
    scanw("%d", &start_vertex);
    noecho();

    // Если ввод коректен завершить цикл
    if (start_vertex >= 0 && start_vertex < count) {
      break;
    }

    // Ошибка ввода
    attron(COLOR_PAIR(3));
    mvprintw(6, 5, "Error: Vertex must be between 0 and %d!", count - 1);
    attroff(COLOR_PAIR(3));
    mvprintw(8, 5, "Press any key to try again...");
    refresh();
    getch();
  }
  return start_vertex;
}

/**
 * @brief Сохраняет граф в файл формата .dot.
 * @param graph Указатель на граф.
 */
void handle_export_to_dot(const Graph* graph) {
  char file_name[FILENAME_MAX] = {0};
  char file_path[FILENAME_MAX] = {0};
  file_prompt(file_name);
  /* Если в имени файла присутствует символ ESCAPE, операция отменяется.  */
  int status = strchr(file_name, ESCAPE) ? ESCAPE : 0;
  if (!status) status = get_file_path(file_path, MODE_D);
  if (strlen(file_path) + strlen(file_name) + 2 > FILENAME_MAX) status = ESCAPE;

  if (!status) {
    strcat(file_path, "/");
    strcat(file_path, file_name);
    status = export_graph_to_dot(file_path, graph);
  }
  clear();
  if (!status) {
    key_prompt("\nGraph has been saved to format .dot, Press any key");
  } else {
    show_error("The save failed.");
  }
}

/**
 * @brief Получить путь к файлу.
 * @param filepath строка для хранения пути к файлу.
 */
static void file_prompt(char filepath[]) {
  clear();
  refresh();
  printw("Enter the name of the file:");
  getnstr(filepath, FILENAME_MAX - 1);
}

/**
 * @brief Нахождение кратчайшего пути.
 * @param graph Указатель на граф.
 */
void handle_shortest_path(const Graph* graph) {
  int size = get_size_graph(graph);
  const char* title1 =
      "Dijkstra's Algorithm - Find shortest path between two vertices - Select "
      "first vertex";
  const char* title2 =
      "Dijkstra's Algorithm - Find shortest path between two vertices - Select "
      "second vertex";
  int vertex1 = get_vertex(size, title1);
  int vertex2 = get_vertex(size, title2);
  int res = get_shortest_path_between_vertices(graph, vertex1, vertex2);
  if (res == -1) {
    print_res_num(res, "Dijkstra's Algorithm: Path not found");
  } else
    print_res_num(res, "Dijkstra's Algorithm Traversal Result");
}

/**
 * @brief Вывести в консоль заголовок алгоритма и чесловой результат его работы.
 * @param res Результат.
 * @param res_title Строка заголовка.
 */
static void print_res_num(int res, const char* res_title) {
  clear();

  attron(COLOR_PAIR(1) | A_BOLD);
  mvprintw(2, (COLS - strlen(res_title)) / 2, "%s", res_title);
  attroff(COLOR_PAIR(1) | A_BOLD);

  attron(COLOR_PAIR(2) | A_BOLD);
  mvprintw(6, 6, "distance: %d", res);
  refresh();
  attroff(COLOR_PAIR(2) | A_BOLD);
  mvprintw(LINES - 2, (COLS - 20) / 2, "Press any key to continue...");
  getch();
}

/**
 * @brief Нахождение кратчайшего пути для всех вершин.
 * @param graph Указатель на граф.
 */
void handle_all_pairs_shortest_path(const Graph* graph) {
  int** res_matrix = get_shortest_paths_between_all_vertices(graph);
  if (!res_matrix) {
    clear();
    refresh();
    show_error("Couldn't get result");
  } else {
    int size = get_size_graph(graph);
    const char* res_title = "Floyd-Warshall Algorithm Traversal Result";
    print_res_matrix(size, res_matrix, res_title);
    remove_matrix(res_matrix, size);
  }
}

/**
 * @brief Вывести в консоль заголовок алгоритма и матричный результат его
 * работы.
 * @param size Размер матрицы.
 * @param res Результат.
 * @param res_title Строка заголовка.
 */
static void print_res_matrix(int count, int** matrix, const char* res_title) {
  clear();

  attron(COLOR_PAIR(1) | A_BOLD);
  mvprintw(2, (COLS - strlen(res_title)) / 2, "%s", res_title);
  attroff(COLOR_PAIR(1) | A_BOLD);

  attron(COLOR_PAIR(2) | A_BOLD);
  for (int i = 0; i < count; i++) {
    for (int j = 0; j < count; j++) {
      mvprintw(6 + i, 6 + j * 4, "%d", matrix[i][j] == INF ? -1 : matrix[i][j]);

      refresh();
      usleep(50000);
    }
  }
  attroff(COLOR_PAIR(2) | A_BOLD);
  mvprintw(LINES - 2, (COLS - 20) / 2, "Press any key to continue...");
  getch();
}

/**
 * @brief (minimum spanning tree) Нахождение кратчайшего пути для всех вершин.
 * @param graph Указатель на граф.
 */
void handle_mst(const Graph* graph) {
  int** res_matrix = get_least_spanning_tree(graph);
  if (!res_matrix) {
    clear();
    refresh();
    show_error("Couldn't get result");
  } else {
    int size = get_size_graph(graph);
    const char* res_title = "Prim's Algorithm - Minimum Spanning Tree";
    print_res_matrix(size, res_matrix, res_title);
    remove_matrix(res_matrix, size);
  }
}

/**
 * @brief Обработцик представления задачи комивояжёра.
 * @param graph Указатель на граф.
 * @return Количество итераций.
 */
void handle_tsp(const Graph* graph) {
  TSM_RESULT* res = NULL;
  int size = get_size_graph(graph);
  const char* prompt = "\nUse arrow keys to choose, enter to select\n\n";
  const char* options[] = {"0. Ant Colony Optimization",
                           "1. Held-Karp Algorithm", "2. Nearest Neighbor",
                           "9. Exit"};

  int count_opt = sizeof(options) / sizeof(*options);
  int current_option = 0;

  /* Программа активна пока не будет выбран последний пункт меню (Exit).  */
  while (current_option != count_opt - 1) {
    current_option = option_select(prompt, count_opt, options);

    if (current_option == 0) res = solve_traveling_salesman_problem(graph);
    if (current_option == 1) {
      if (!confirm_large_graph_processing(size)) continue;
      res = solve_tsp_held_karp(graph);
    }
    if (current_option == 2) res = solve_tsp_nearest_neighbor(graph);
    if (current_option == count_opt - 1) break;

    if (!res) {
      clear();
      refresh();
      show_error("Couldn't get result");
    } else {
      print_res_tsm(size, res, options[current_option]);
      free_tsm_result(res);
      res = NULL;
    }
  }
}

/**
 * @brief Вывести список посещенных вершин в двух вариантах: числовом и
 * буквенном. Вывести дистанцию пути.
 * @param count Количество вершин графа.
 * @param res Результат содержащий длинну всего пути и посещенные вершины.
 * @param result_title Заголовок результата.
 */
static void print_res_tsm(int count, const TSM_RESULT* res,
                          const char* result_title) {
  char name1[NAME_SIZE + 1] = {0};
  count++;
  int num_line = 2;
  int num_col = 6;
  clear();

  attron(COLOR_PAIR(1) | A_BOLD);
  mvprintw(num_line, (COLS - strlen(result_title)) / 2, "%s", result_title);
  attroff(COLOR_PAIR(1) | A_BOLD);

  attron(COLOR_PAIR(2) | A_BOLD);
  mvprintw(num_line + 4, num_col, "distance: %d", (int)res->distance);
  for (int i = 0; i < count; i++) {
    mvprintw(num_line + 6, num_col + i * 4, "%d", res->vertices[i]);
    if (i < count - 1) printw(" > ");
    // Буквенное представление.
    get_name_vertex(name1, res->vertices[i]);
    mvprintw(num_line + 8, num_col + i * 4, "%s", name1);
    if (i < count - 1) printw(" > ");

    refresh();
    usleep(100000);
  }
  attroff(COLOR_PAIR(2) | A_BOLD);
  mvprintw(LINES - 2, (COLS - 20) / 2, "Press any key to continue...");
  getch();
}
