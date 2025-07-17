#ifndef _UTILS_H
#define _UTILS_H

#include "graph_algorithms.h"

TSM_RESULT* create_tsm_result(int size);
void free_tsm_result(TSM_RESULT* result);
void matrix_zero_to_default(int size, int dest[size][size], const int** src);

#endif