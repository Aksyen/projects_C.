#include "cli.h"

int main(int argc, char **argv) {
  (void)argc; /* Подавляем argc для -Wextra -Werror(unused-parameter).  */
  initscr();
  keypad(stdscr, TRUE); /* Включить клавиши со стрелками.  */
  start_color(); /* Включение поддержки цветов.  */
  srand(time(NULL));
  /* Инициализация пользовательских цветовых пар.  */
  // init_pair(1, COLOR_BLACK, COLOR_YELLOW);
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);
  menu_initializer(argv[1]);

  endwin();
}

/**
 * @brief Инициализация главного меню.
 */
void menu_initializer(const char *path) {
  Graph *graph = load_graph_from_file(path);
  const char *prompt = "\nUse arrow keys to choose, enter to select\n\n";
  const char *options[] = {"0. Load graph from file",
                           "1. Breadth-First Search (BFS) Traversal",
                           "2. Depth-First Search (DFS) Traversal",
                           "3. Find Shortest Path (Between Two Vertices)",
                           "4. Find All Pairs Shortest Paths (Floyd-Warshall)",
                           "5. Find Minimum Spanning Tree (MST)",
                           "6. Solve Traveling Salesman Problem (TSP)",
                           "7. Compare TSP Algorithms (Speed Test)",
                           "8. Export gpaph to *.dot",
                           "9. Exit"};

  int count_opt = sizeof(options) / sizeof(*options);
  int current_option = 0;
  /* Программа активна пока не будет выбран последний пункт меню (Exit).  */
  while (current_option != count_opt - 1) {
    current_option = option_select(prompt, count_opt, options);

    if (current_option == 0) handle_load_graph(&graph);
    /* Если файл не загружен доступна только опция загрузки файла.  */
    if (!graph && current_option != count_opt - 1 && current_option != 0) {
      key_prompt("\nTo get started, download the file.");
      continue;
    }
    if (current_option == 1) handle_bfs_dfs(graph, MODE_BFS);
    if (current_option == 2) handle_bfs_dfs(graph, MODE_DFS);
    if (current_option == 3) handle_shortest_path(graph);
    if (current_option == 4) handle_all_pairs_shortest_path(graph);
    if (current_option == 5) handle_mst(graph);
    if (current_option == 6) handle_tsp(graph);
    if (current_option == 7) handle_tsp_compare(graph);
    if (current_option == 8) handle_export_to_dot(graph);

    clear();
  }

  if (graph) free_graph(graph);
}
