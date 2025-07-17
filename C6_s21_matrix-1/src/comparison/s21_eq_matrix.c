#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  // Проверка на NULL указатели
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL) {
    return FAILURE;
  }

  int code_err = SUCCESS;
  if (A->rows != B->rows || A->columns != B->columns) {
    code_err = FAILURE;
  }

  for (int i = 0; code_err && i < A->rows; i++) {
    for (int j = 0; code_err && j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
        code_err = FAILURE;
      }
    }
  }

  return code_err;
}
