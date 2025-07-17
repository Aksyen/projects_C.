#include "graph_algorithms.h"

/**
 * @brief Выделение памяти для TSM_RESULT.
 *
 * @param size Количество вершин графа, размер.
 * @return При успешном выделении памяти указатель на созданный TSM_RESULT,
 * иначе NULL.
 * @note При успешном создании TSM_RESULT после завершении работы с ним, следует
 * освободить память функцией free_tsm_result().
 */
TSM_RESULT *create_tsm_result(int size) {
  if (size < 1) return NULL;

  TSM_RESULT *tsm_result = (TSM_RESULT *)calloc(1, sizeof(TSM_RESULT));
  if (tsm_result == NULL) return NULL;

  tsm_result->vertices = (int *)calloc(size + 1, sizeof(int));
  if (tsm_result->vertices == NULL) {
    free(tsm_result);
    return NULL;
  }
  return tsm_result;
}

/**
 * @brief Освобождение памяти TSM_RESULT.
 * @param result Указатель на структуру TSM_RESULT.
 */
void free_tsm_result(TSM_RESULT *result) {
  if (result) {
    if (result->vertices) {
      free(result->vertices);
    }
    free(result);
  }
}

/**
 * @brief Копирует матрицы с заменой нулевых значений на INF.
 *
 * @param size Количество вершин графа.
 * @param dest Матрица куда переносятся данные.
 * @param src Матрица источник данных.
 */
void matrix_zero_to_default(int size, int dest[size][size], const int **src) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      dest[i][j] = src[i][j] == 0 ? INF : src[i][j];
    }
  }
}
