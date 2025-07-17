#ifndef CLI_H
#define CLI_H

#include <dirent.h>  // Pабота с каталогами (чтение содержимого, поиск файлов).
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>  // Получение информации о файлах (права доступа, размер, тип).
#include <sys/types.h>  // Oпределение типов данных (используется вместе с stat.h и dirent.h).
#include <sys/wait.h>  // Управление дочерними процессами (ожидание завершения, статус).
#include <time.h>
#include <unistd.h>  // POSIX-функции (вызовы fork, exec, sleep, работа с файловыми дескрипторами).

#include "../algorithm/graph_algorithms.h"

#define ESCAPE 27
#define ENTER 10
#define SPACE 32

#define MAX_FILES 100 /* Колличество файлов.  */
#define MIN_TIME 100  /* Минимальное время задержки.  */

#define MODE_BFS 2 /* Поиск BFS.  */
#define MODE_DFS 2 /* Поиск DFS.  */

#define MODE_F 0 /* Файл.  */
#define MODE_D 1 /* Директория.  */

extern int nanosleep(const struct timespec *__requested_time,
                     struct timespec *__remaining);
extern int usleep(size_t);
extern void free_tsm_result(TSM_RESULT *);

void menu_initializer(const char *path);
int key_prompt(const char *prompt);
void show_error(const char *message);
int option_select(const char *prompt, int count_opt, const char **options);
int get_file_path(char path_file[], char mode);
bool confirm_large_graph_processing(int size);

void handle_load_graph(Graph **graph);
void handle_bfs_dfs(const Graph *graph, int mode);
void handle_shortest_path(const Graph *graph);
void handle_all_pairs_shortest_path(const Graph *graph);
void handle_mst(const Graph *graph);
void handle_tsp(const Graph *graph);
void handle_tsp_compare(const Graph *graph);
void handle_export_to_dot(const Graph *graph);

#endif