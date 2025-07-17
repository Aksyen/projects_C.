#include "../s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL || A->matrix == NULL ||
      B->matrix == NULL || A->rows < 1 || A->columns < 1 || B->rows < 1 ||
      B->columns < 1 || A->rows != B->rows || A->columns != B->columns) {
    return INCORRECT_MATRIX;
  }

  int code_err = s21_create_matrix(A->rows, A->columns, result);

  for (int i = 0; code_err == OK && i < A->rows; i++) {
    for (int j = 0; code_err == OK && j < A->columns; j++) {
      double sum = A->matrix[i][j] + B->matrix[i][j];
      if (isinf(sum)) {
        // Освобождаем память, если обнаружено переполнение
        s21_remove_matrix(result);
        // Возвращаем ошибку вычисления
        code_err = CALCULATION_ERROR;
      } else
        result->matrix[i][j] = sum;
    }
  }

  return code_err;
}
