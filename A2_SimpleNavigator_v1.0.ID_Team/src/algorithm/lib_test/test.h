#ifndef TEST_H
#define TEST_H

#include <check.h>

#include "../../graph/graph.h"
#include "../graph_algorithms.h"
#include "../utils.h"

Suite* test_depth_first_search(void);
Suite* test_breadth_first_search(void);
Suite* test_get_shortest_path_between_vertices(void);
Suite* test_get_shortest_paths_between_all_vertices(void);
Suite* test_get_least_spanning_tree(void);
Suite* test_tsp_held_karp(void);
Suite* test_tsp_nearest_neighbor(void);
Suite* test_solve_traveling_salesman_problem(void);

#endif
