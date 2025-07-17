#ifndef _GRAPH_ALGORITHMS_H
#define _GRAPH_ALGORITHMS_H

#include <limits.h>
#include <stdbool.h>

#include "../graph/graph.h"
// #include "utils.h"

#define INF INT_MAX

/**
 * @brief Структура для представления пути TSP.
 *
 * @param vertices Mассив с искомым маршрутом (с порядком обхода вершин).
 * @param distance Длина этого маршрута.
 */
typedef struct tsm_result {
  int* vertices;
  double distance;
} TSM_RESULT;

int* depth_first_search(const Graph* graph, int start_vertex);

int* breadth_first_search(const Graph* graph, int start_vertex);

int get_shortest_path_between_vertices(const Graph* graph, int vertex1,
                                       int vertex2);

int** get_shortest_paths_between_all_vertices(const Graph* graph);

int** get_least_spanning_tree(const Graph* graph);

TSM_RESULT* solve_traveling_salesman_problem(const Graph* graph);

TSM_RESULT* solve_tsp_nearest_neighbor(const Graph* graph);

TSM_RESULT* solve_tsp_held_karp(const Graph* graph);

#endif  // _GRAPH_ALGORITHMS_H