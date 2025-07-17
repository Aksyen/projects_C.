#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int code_err = OK;

  if (A == NULL || result == NULL ||
      s21_create_matrix(A->columns, A->rows, result) != 0) {
    code_err = INCORRECT_MATRIX;
  }

  if (!code_err && A->rows > 0 && A->columns > 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }

  return code_err;
}
